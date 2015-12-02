/* Little program to demonstrate getting the names into a rank-ordered
   array on all processors.
	mpicc census.c
	or
	mpiCC census.c
	then
	mpirun -np 3 a.out
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>


#define NAMESIZE (MPI_MAX_PROCESSOR_NAME+1)

int main(int argc, char **argv) {

	int i;		/* iteration */
	int id;		/* pid */
	int myRank;	/* rank in mpi communicator */
	int nProc;	/* size of mpi communicator */
	char ipbuf[NAMESIZE];	/* hostname */
	char ipstring[NAMESIZE];	/* hostname */
	int len;
	int err;
	MPI_Comm comm;

	/*CFREE*/ char *hostArray = NULL;
	/*CFREE*/ char **hostList = NULL;
	/*CFREE*/ int *pidArray = NULL;
	/*CFREE*/ int *receivedChars = NULL;
	/*CFREE*/ int *receiveLocations = NULL;

	MPI_Init(&argc, &argv);

	comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &myRank);
	MPI_Comm_size(comm, &nProc);

	/* Create memory for collective communication and an argv indexed
		by processor number of the names we shall receive.
		The names may not be unique within the array.
		Therefore also create memory for process id array.
		We will exchange fixed length strings rather than creating
		an equivalent MPI_Type_* object.
	*/
	pidArray = (int *)malloc(nProc*sizeof(int)); 
	hostArray = (char *)malloc(nProc*NAMESIZE); /* a bit of mpi braindeadness */
	hostList = (char **)malloc((nProc +1)*sizeof(char *));
	receivedChars = (int *)malloc(nProc*sizeof(int)); 
	receiveLocations = (int *)malloc(nProc*sizeof(int)); 
	
	for (i = 0; i < nProc; i++) {
		hostList[i] = &(hostArray[i*NAMESIZE]);
		receiveLocations[i] = i*NAMESIZE;
		receivedChars[i] = NAMESIZE;
		pidArray[i] = -1; /* -1 is not a reasonable unix process number */
	}
	hostList[nProc] = NULL;

	id = (int)getpid();
	/* get all the pids together */
	err = MPI_Allgather(&id,1,MPI_INT,
				pidArray,1,MPI_INT,
				MPI_COMM_WORLD);
	if (err) {
		printf("rank=%d err=%d\n",myRank,err);
		MPI_Abort(comm,err);
	}

	printf("processor %d (pid=%d): ",myRank,id);
	for (i = 0; i < nProc-1; i++) {
		printf("%d, ",pidArray[i]);
	}
	printf("%d\n",pidArray[nProc-1]);
	
	err = MPI_Get_processor_name(ipbuf, &len);
	strncpy(ipstring,ipbuf,len);
	ipstring[len] = '\0';

	err = MPI_Allgatherv(ipstring, NAMESIZE, MPI_CHAR,
			hostArray, receivedChars , receiveLocations, MPI_CHAR,
			comm);

	if (err) {
		printf("rank=%d err=%d\n",myRank,err);
		MPI_Abort(comm,err);
	}

	printf("processor %d (pid=%d): ",myRank,id);
	for (i = 0; i < nProc; i++) {
		printf("%s(%d),\n",hostList[i],pidArray[i]);
	}

	MPI_Finalize();
	exit(0);
}
#ifdef __cplusplus
};
#endif
