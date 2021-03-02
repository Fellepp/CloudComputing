#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
  int rank, size, tag, rc, i;
  MPI_Status status;
  char message[40];

  rc = MPI_Init(&argc, &argv);
  rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
  rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  tag = 100;
	  
  if(rank != 0) {
    char integer_string[5];
    strcpy(message, "Hello, world from node ");
    sprintf(integer_string, "%d", rank);
    strcat(message, integer_string);
    rc = MPI_Send(message, 40, MPI_CHAR, i, tag, MPI_COMM_WORLD);
  } 
  else if (rank == 0) {
    for (i = 1; i < size; i++){
      rc = MPI_Recv(message, 40, MPI_CHAR, i, tag, MPI_COMM_WORLD, &status);
      printf("Message from node %d to node %d! Node %d is printing : %.40s\n", i, rank, rank, message);
    }
  }
  rc = MPI_Finalize();
}


