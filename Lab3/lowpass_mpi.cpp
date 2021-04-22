#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <png++/png.hpp>
#include "stdio.h"
#include "string.h"
#include <string>
#include <sstream>
#include <chrono>
#include <omp.h>
#include "mpi.h"

using namespace std;

typedef vector<double> Array;
typedef vector<Array> Matrix;
typedef vector<Matrix> Image;

Matrix getGaussian(int height, int width, double sigma)
{
    Matrix kernel(height, Array(width));
    double sum=0.0;
    int i,j;

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
            sum += kernel[i][j];
        }
    }

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

Matrix getLowPass(int height, int width)
{
    Matrix kernel(height, Array(width));
    int i,j;
    int sum = 0;

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] = (double) 1;
            sum++;
        }
    }

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

Image loadImage(const char *filename)
{
    png::image<png::rgb_pixel> image(filename);
    Image imageMatrix(3, Matrix(image.get_height(), Array(image.get_width())));

    int h,w;
    for (h=0 ; h<image.get_height() ; h++) {
        for (w=0 ; w<image.get_width() ; w++) {
            imageMatrix[0][h][w] = image[h][w].red;
            imageMatrix[1][h][w] = image[h][w].green;
            imageMatrix[2][h][w] = image[h][w].blue;
        }
    }

    return imageMatrix;
}

void saveImage(Image &image, string filename)
{
    assert(image.size()==3);

    int height = image[0].size();
    int width = image[0][0].size();
    int x,y;

    png::image<png::rgb_pixel> imageFile(width, height);

    for (y=0 ; y<height ; y++) {
        for (x=0 ; x<width ; x++) {
            imageFile[y][x].red = image[0][y][x];
            imageFile[y][x].green = image[1][y][x];
            imageFile[y][x].blue = image[2][y][x];
        }
    }
    imageFile.write(filename);
}

Image applyFilter(Image &image, Matrix &filter){
    assert(image.size()==3 && filter.size()!=0);

    int height = image[0].size();
    int width = image[0][0].size();
    int filterHeight = filter.size();
    int filterWidth = filter[0].size();
    int newImageHeight = height-filterHeight+1;
    int newImageWidth = width-filterWidth+1;
    int d, i, j, h, w;

    Image newImage(3, Matrix(newImageHeight, Array(newImageWidth)));
    
    for (i=0; i<newImageHeight; i++) {
        for (j=0; j<newImageWidth; j++) {
            for (d=0 ; d<3 ; d++) {
                for (h=i ; h<i+filterHeight ; h++) {
                    for (w=j ; w<j+filterWidth ; w++) {
                        newImage[d][i][j] += filter[h-i][w-j]*image[d][h][w];
                    }
                }
            }
        }
    }
    return newImage;
}

Image applyFilter(Image &image, Matrix &filter, int times)
{
    Image newImage = image;
    for(int i=0 ; i<times ; i++) {
        newImage = applyFilter(newImage, filter);
    }
    return newImage;
}

int main(int agrc, char *argv[])
{
    int rank, size, tag, rc, newImageHeightNode, userWidth, finalHeight, firstHeight, comp;

    rc = MPI_Init(&agrc, &argv);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    tag = 1;

    Image image;
    Matrix filter;

    if(rank == 0) { //MASTER NODE
        auto t1 = std::chrono::high_resolution_clock::now();
        cout << "Loading image..." << endl;
        Image image = loadImage(argv[1]);
        Matrix filter = getLowPass(11,11);

        firstHeight = 0;
        newImageHeightNode = image[0].size()/(size-1);
        userWidth = image[0][0].size();

        for (int n = 1; n < size; n ++) {
            if (newImageHeightNode*n + filter[0].size() > image[0].size()){
                finalHeight = newImageHeightNode * n;
            }else{
                finalHeight = (newImageHeightNode * n + filter[0].size()); 
            }
            for (int j = 0; j <3; j ++) {
                for (int i = firstHeight; i < finalHeight; i ++) {
                    rc = MPI_Send (&image [j][i][0], userWidth, MPI_DOUBLE, n, tag , MPI_COMM_WORLD); 
                }
            } 
            firstHeight += newImageHeightNode; 
        }
        auto t1_1 = std::chrono::high_resolution_clock::now();

        rc = MPI_Bcast(&userWidth, 1, MPI_INT, 0, MPI_COMM_WORLD); 
        rc = MPI_Bcast(&newImageHeightNode, 1, MPI_INT, 0, MPI_COMM_WORLD);

        finalHeight = 0;
        firstHeight = 0;

        rc = MPI_Recv(&comp, 1, MPI_INT, (size-1), 6, MPI_COMM_WORLD, &status);
        Image resImage (3, Matrix((newImageHeightNode*(size-1) - comp), Array (userWidth)));

        for (int n = 1; n < size; n++){
            if (n == size-1){
                finalHeight = resImage[0].size();
            }else{
                finalHeight = newImageHeightNode * n;
            }
            for (int d = 0; d < 3; d++){
                for (int i = firstHeight; i < finalHeight; i++){
                    rc = MPI_Recv(&resImage[d][i][0], userWidth, MPI_DOUBLE, n, 2, MPI_COMM_WORLD, &status);
                }
            }
            firstHeight += (newImageHeightNode);
        }

        auto t2_1 = std::chrono::high_resolution_clock::now();
        auto duration_1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2_1 - t1_1).count();
        std::cout << "Tiempo de c�mputo: " << (float) (duration_1 / 1000.0) << " sec" << std::endl;

        cout << "Saving image..." << endl;

        // Generamos el nombre del fichero 
        stringstream ss;
        ss << argv[2];
        string str = ss.str();
        string ficheroGuardar = str;
    
        saveImage(resImage, ficheroGuardar);
        cout << "Done!" << endl;


        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "Tiempo de ejecucion: " << (float) (duration / 1000.0) << " sec" << std::endl;
    }

    if (rank != 0){
        rc = MPI_Bcast(&userWidth, 1, MPI_INT, 0, MPI_COMM_WORLD); 
        rc = MPI_Bcast(&newImageHeightNode, 1, MPI_INT, 0, MPI_COMM_WORLD);
        //Matrix filter = getGaussian(10, 10, 50.0);
        printf("Process %d is applying filter...\n", rank);
        Matrix filter = getLowPass(11,11);
        int tempHeight;

        if (rank == size-1){
            tempHeight = newImageHeightNode;
        }else{
            tempHeight = newImageHeightNode + filter[0].size();
        }

        Image newImage (3, Matrix (tempHeight, Array (userWidth)));

        // We receive the Image 
        for (int j = 0; j <3; j ++) {
            for (int i = 0; i < newImage [0].size (); i++) {
                rc = MPI_Recv (&newImage[j][i][0], userWidth, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
            }
        }
        Image tempImage = applyFilter(newImage, filter);
        
        if (tempImage[0].size() < newImageHeightNode){
            tempHeight = tempImage[0].size();
        }else{
            tempHeight = newImageHeightNode;
        }

        printf("Process %d is done and will pass this back...\n", rank);
        for (int j = 0; j < 3; j ++) {
            for (int i = 0; i < tempHeight; i ++) {
                rc = MPI_Send (&tempImage[j][i][0], userWidth, MPI_DOUBLE, 0, 2 , MPI_COMM_WORLD); 
            }
        }
        if (rank == size-1){
            comp = newImageHeightNode-tempImage[0].size();
            rc = MPI_Send(&comp, 1, MPI_INT, 0, 6, MPI_COMM_WORLD);
        }
    }
    rc = MPI_Finalize();
}