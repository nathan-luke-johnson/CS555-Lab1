/* Mpi Hello World Program - MpiHello.c */

#include <mpi.h>
#include <stdio.h>

/* To Compile: mpicc -g MpiHello.c -o MpiHello
	  To Execute: mpirun -np 4 MpiHello
*/

int main(int argc, char *argv[])
{   int myRank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size<2) MPI_Abort(MPI_COMM_WORLD, 1);


   if (myRank==0)
   {  printf("Hello World - I'm the master\n");
   }
   else 
   {  printf("Hello World - I'm slave %u\n", myRank);
   }
   MPI_Finalize();
   return 0;
}
