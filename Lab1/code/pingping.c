#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include "time.h"

int main(int argc, char **argv)
{
  MPI_Init(NULL, NULL);

  #define BILLION 1E3
  struct timespec requestStart, requestEnd;

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

  int token = 0;
  while (1){
    if (world_rank != 0){
        MPI_Recv(&token, 1000, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }else{
        token++;
        clock_gettime(CLOCK_REALTIME, &requestStart);
    }
    MPI_Send(&token, 1000, MPI_BYTE, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

    if (world_rank == 0){
        MPI_Recv(&token, 1000, MPI_BYTE, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        printf("That's a ping pong with integer %d\n", token);
        double accum = (requestEnd.tv_sec - requestStart.tv_sec )
        + ( requestEnd.tv_nsec - requestStart.tv_nsec ) / BILLION;
        printf("Time used for ping pong is %lf\n", accum);
    }
  }
  MPI_Finalize();
}
