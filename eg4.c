
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int numElements = atoi (argv[1]);
  int loopcount = 1000;
  int arr[numElements];
  int myrank, size;
  MPI_Status status;
  int count, recvarr[numElements];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if (argc>2) loopcount = atoi (argv[2]);

  double time = MPI_Wtime();

  for (int loop=0; loop<loopcount; loop++) {

  if (myrank == 0)    /* code for process zero */
    MPI_Send(arr, numElements, MPI_BYTE, 1, 99, MPI_COMM_WORLD);
  else if (myrank == 1)  /* code for process one */
    MPI_Recv(recvarr, numElements, MPI_BYTE, 0, 99, MPI_COMM_WORLD, &status);

  }

  printf ("Rank %d done in %lf\n", myrank, MPI_Wtime()-time);

  MPI_Finalize();
  return 0;
}
