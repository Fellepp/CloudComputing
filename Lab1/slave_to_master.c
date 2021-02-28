#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include "time.h"

int main(int argc, char **argv)
{
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);
  int token;

  while (1){
    if (world_rank != 0){
        MPI_Recv(&token, 1000, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }else{
        token = 69;
    }
    MPI_Send(&token, 1000, MPI_BYTE, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

    if (world_rank == 0){
        MPI_Recv(&token, 1000, MPI_BYTE, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("That's a ping pong with integer %d\n", token);
    }
  }
  MPI_Finalize();
}
