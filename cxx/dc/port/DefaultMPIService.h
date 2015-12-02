#ifdef _CCAMPI
#ifndef DefaultMPIService_h_seen
#define DefaultMPIService_h_seen
#include "util/noSeekMPI.h"
#include <mpi.h>
#include "dc/export/config.hh"
class DefaultMPIService 
#if (defined(HAVE_CLASSIC)||defined(HAVE_NEO))
: 
#endif
#ifdef HAVE_CLASSIC
public virtual classic::gov::cca::MPIService 
#endif //HAVE_CLASSIC
#ifdef HAVE_NEO
  /// this is a hack. do the opq adapter and make it go away. ouch.
#ifdef HAVE_CLASSIC
,
#endif // HAVE_CLASSIC
public virtual neo::cca::Port
, public virtual neo::cca::ports::MPIService
#endif // HAVE_NEO
{
private:

  static const int cap = 10; // small enough for debugging demos.

  bool inuse[cap];
  int64_t fortranMPIComm; // ur-communicator of which all are dups.

  MPI_Comm comm[cap];

public:

	/** construct using a shared communicator for all borrow operations.
	 * @param fComm is in fortran-compatible format.
	 */
  DefaultMPIService(int64_t fComm);

  virtual ~DefaultMPIService();

  virtual MPI_Comm getComm();

  virtual void releaseComm(MPI_Comm m);

};
#endif //DefaultMPIService_h_seen
#endif // _CCAMPI
