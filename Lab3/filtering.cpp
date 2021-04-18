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
#include "algorithm"

using namespace std;

#define SIZE 3

typedef vector<double> Array;
typedef vector<Array> Matrix;
typedef vector<Matrix> Image;

void matrixSorter(int mat[SIZE][SIZE], int n)
{
    int temp[n * n];
    int k = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        temp[k++] = mat[i][j];

    sort(temp, temp + k);
    
    k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = temp[k++];
}

int medianValue(int mat[SIZE][SIZE], int n)
{
    if (n % 2 != 0){
        return mat[n/2][n/2];
    }
    return mat[(n-2)/2][n-1];
}

void printMat(int mat[SIZE][SIZE], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main(int agrc, char *argv[])
{
    int mat[SIZE][SIZE] = {
        { 5, 4, 7 },
        { 1, 3, 8 },
        { 2, 9, 6 }
    };

    int* out;
    int n = 3;

    cout << "Original Matrix:\n";
    printMat(mat, n);

    matrixSorter(mat, n);

    cout << "\nMatrix After Sorting:\n";
    printMat(mat,n);

    printf("Median in sorted matrix: %d\n", medianValue(mat,n));

    return 0;
}