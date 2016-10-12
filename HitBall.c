/*  Inital Demonstration mpi program for cs455.  */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <string.h>

#define true   1
#define false  0

#define MAXIBUF 100
#define PLAYS     3
#define MSGS      5
#define MAX      20

/* Initial HitBall program in c.
   To Compile: mpicc -g HitBall.c -o HitBall  
   To Execute: mpirun -np 4 HitBall
*/

/* Start of Main Program */

int main(int argc, char *argv[])
{  
    char more = true;
    int  myRank, size, msg, player, i;
    char *done = "Done";
    char *msgs[MSGS] = {"Grounder", "Fly", "Line drive", "Pop up", "Bunt"};
    char *play[PLAYS] = {"caught", "dropped", "bobbled"};
    char ibuf[MAXIBUF];
    MPI_Status status;
	
    srand( (unsigned)time( NULL ) );
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size<2) MPI_Abort(MPI_COMM_WORLD, 1);

/* Instructions executed by the master processor. */
    if (myRank==0)
    { 
		/* Hit the balls to the slaves */
		for (i=0; i<MAX; i++) 
		{  
			player = 1 + rand() % (size - 1);
			msg    = rand() % MSGS ;
			MPI_Send(msgs[msg], strlen(msgs[msg])+1, MPI_CHAR, player, 0, MPI_COMM_WORLD);
		}

		/* Tell the slaves that we're going home */
		for (player=1; player<size; player++)
		{
			MPI_Send(done, strlen(done)+1, MPI_CHAR, player, 1, MPI_COMM_WORLD);
		}
	}
	else

	/* Instructions executed by slave processors. */
	{ 
		while (more)
		{  
			MPI_Recv(ibuf, MAXIBUF, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG
					 , MPI_COMM_WORLD, &status);
			if (status.MPI_TAG == 1) more = false;
			else
			{
				i = rand()%PLAYS;
				printf("%u to %u: %s\n", status.MPI_SOURCE, myRank, play[i]);
			}
		}
	}

    /* Shut things down - All processors execute these instructions */
    printf("%u Went Home\n", myRank);
    MPI_Finalize();
    return 0;
}
