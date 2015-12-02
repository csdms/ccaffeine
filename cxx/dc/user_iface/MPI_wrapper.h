/*
// This file can be included multiple times, for those
// who want to play preprocessor games.
// Play too much and mpi will bite you.

*/

struct MPI_wrapper;

#ifdef MPI_wrapper_HAS_CONTENT
#undef MPI_wrapper_HAS_CONTENT
#endif /* MPI_wrapper_HAS_CONTENT */


#ifdef _CCAMPI

#include "util/noSeekMPI.h"
#include <mpi.h>

#define MPI_wrapper_HAS_COMM

struct MPI_wrapper {
  MPI_Comm comm;
/*
 // for mpich 1.1.1/2 --
 // MPI_Fint fcomm;
 // mw->fcomm = MPI_Comm_c2f(mw->comm);
*/
};

#else

/* struct MPI_wrapper explicitly may contain
   anything, so it is not safe to pass outside
   your own code.
 */

#endif /*_CCAMPI*/
