#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include "time.h"

int main(int argc, char **argv)
{
    int size, rank, tag, rc, token, ring_counter;

    MPI_Init( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank != 0){
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printf("Node %d got token %d from node %d\n", rank, token, rank - 1);
    }else{
        token = 69;
    }
    if (rank == size - 1){
        printf("Node %d sending token %d to node %d\n", rank, token, 0);
        MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }else{
        printf("Node %d sending token %d to node %d\n", rank, token, rank + 1);
        MPI_Send(&token, 1, MPI_INT, (rank + 1), 0, MPI_COMM_WORLD);
    }
    if (rank == 0){
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("That's a full ring, got token %d from node %d\n", token, size - 1);
    }
    MPI_Finalize();
}
