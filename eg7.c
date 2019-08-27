// Multiple senders 1 receiver
//
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{

  int BUFFER = atoi(argv[1]);
  int option = atoi (argv[2]);
  int arr[BUFFER];
  int myrank, size;
  MPI_Status status;
  double start_time;
  char *buf;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  for (int i=0;i<BUFFER; i++)
    arr[i] = rand() % (myrank+11); 

  int bufsize = BUFFER*5;

  start_time = MPI_Wtime ();
  if (myrank < size-1) 
  {
    if (option == 1)
     MPI_Send(arr, BUFFER, MPI_INT, size-1, myrank, MPI_COMM_WORLD);
    else if (option == 2) {
     buf = (char *) malloc(bufsize);
     MPI_Buffer_attach( buf, bufsize);
     MPI_Bsend(arr, BUFFER, MPI_INT, size-1, myrank, MPI_COMM_WORLD);
    }
    else if (option == 3)
     MPI_Ssend(arr, BUFFER, MPI_INT, size-1, myrank, MPI_COMM_WORLD);
  }
  else 
  {
    int count, recvarr[size][BUFFER];
    for (int i=0; i<size-1; i++)
      MPI_Recv(recvarr[i], BUFFER, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  }

  if (myrank == size-1) printf ("Rank %d: time= %lf\n", myrank, MPI_Wtime () - start_time);

  if (option == 2)
     MPI_Buffer_detach( &buf, &bufsize );

  MPI_Finalize();
  return 0;
}
