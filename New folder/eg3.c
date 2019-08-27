
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define numElements 1000000

int main( int argc, char *argv[])
{
  int arr[numElements] = {0};
  int myrank, size;
  MPI_Status status;
  int count, recvarr[numElements];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if (myrank == 0)    /* code for process zero */
  {
    MPI_Send(arr, numElements, MPI_INT, 1, 99, MPI_COMM_WORLD);
    MPI_Recv(recvarr, numElements, MPI_INT, 1, 99, MPI_COMM_WORLD, &status);
    printf ("Rank 0 done\n");
  }
  else if (myrank == 1)  /* code for process one */
  {
    MPI_Send(arr, numElements, MPI_INT, 0, 99, MPI_COMM_WORLD);
    MPI_Recv(recvarr, numElements, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
    printf ("Rank 1 done\n");
  }

  MPI_Finalize();
  return 0;
}
