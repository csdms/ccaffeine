#ifdef _CCAMPI
#ifndef DefaultMPIBorrow_h_seen
#define DefaultMPIBorrow_h_seen
#include "util/noSeekMPI.h"
#include <mpi.h>
#include "dc/export/config.hh"
class DefaultMPIBorrow
#if (defined(HAVE_NEO) || defined(HAVE_CLASSIC))
: 
#endif
#ifdef HAVE_CLASSIC
public virtual classic::gov::cca::MPIBorrow
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
  /// this is a hack. do the opq adapter and make it go away. ouch.
#ifdef HAVE_CLASSIC
, // need a , only if classic preceding
#endif // HAVE_CLASSIC
public virtual neo::cca::Port
, public virtual neo::cca::ports::MPIBorrow
#endif // HAVE_NEO

{

private:

	/** next available tag. */
	int maxTag;

	/** last issued key */
	int maxKey;
	
	// ur-communicator 
  	int64_t fortranMPIComm; 
public:

	/** construct using a shared communicator for all borrow operations.
	 * @param fComm is in fortran-compatible format.
	 */
  DefaultMPIBorrow(int64_t fComm);

  virtual ~DefaultMPIBorrow();

	/** Get a communicator and a set of available tags on it.
	 * FIXME need to keep a key:tag lookup array to be fully safe.
	 * FIXME need to keep a key comm lookup, if we manage more than one comm...
	 */
  virtual MPI_Comm borrowComm(int, int*, int&);

	/** Return a communicator and release the tags on it. */
  virtual void returnComm(MPI_Comm, int, int*, int);

};
#endif //DefaultMPIBorrow_h_seen
#endif // _CCAMPI
