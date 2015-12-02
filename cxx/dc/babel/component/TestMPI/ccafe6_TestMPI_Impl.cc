// 
// File:          ccafe6_TestMPI_Impl.cc
// Symbol:        ccafe6.TestMPI-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe6.TestMPI
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe6_TestMPI_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._includes)
#include "util/noSeekMPI.h"
#include <mpi.h>

namespace {
                                                                                
void whine(std::string s)
{
	IO_dn2("ccafe6::TestMPI: %s",s.c_str());
        ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
        ex.setNote(s);
        throw ex;
}
// fixme-feature traceback
#define WHINE(s) whine(s)
                                                                                
}; // end namespace anon

// DO-NOT-DELETE splicer.end(ccafe6.TestMPI._includes)

// user-defined constructor.
void ccafe6::TestMPI_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._ctor)
  // Insert-Code-Here {ccafe6.TestMPI._ctor} (constructor)
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI._ctor)
}

// user-defined destructor.
void ccafe6::TestMPI_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._dtor)
  // Insert-Code-Here {ccafe6.TestMPI._dtor} (destructor)
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI._dtor)
}

// static class initializer.
void ccafe6::TestMPI_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._load)
  // Insert-Code-Here {ccafe6.TestMPI._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * Starts up a component presence in the calling framework.
 * @param services the component instance's handle on the framework world.
 * Contracts concerning Svc and setServices:
 * 
 * The component interaction with the CCA framework
 * and Ports begins on the call to setServices by the framework.
 * 
 * This function is called exactly once for each instance created
 * by the framework.
 * 
 * The argument Svc will never be nil/null.
 * 
 * Those uses ports which are automatically connected by the framework
 * (so-called service-ports) may be obtained via getPort during
 * setServices.
 */
void
ccafe6::TestMPI_impl::setServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI.setServices)
  // Insert-Code-Here {ccafe6.TestMPI.setServices} (setServices method)
  svc = services;
  gov::cca::TypeMap tm;
  gov::cca::ports::GoPort gp = self;
  svc.registerUsesPort("MPIService","ccaffeine.ports.MPIService",tm);
  svc.registerUsesPort("MPIBorrow","ccaffeine.ports.MPIBorrow",tm);
  svc.addProvidesPort(gp,"go","gov.cca.ports.GoPort",tm);
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI.setServices)
}

/**
 * Shuts down a component presence in the calling framework.
 * @param Svc the component instance's handle on the framework world.
 * Contracts concerning Svc and setServices:
 * 
 * This function is called exactly once for each callback registered
 * through Services.
 * 
 * The argument Svc will never be nil/null.
 * The argument Svc will always be the same as that received in
 * setServices.
 * 
 * During this call the component should release any interfaces
 * acquired by getPort().
 * 
 * During this call the component should reset to nil any stored
 * reference to Svc.
 * 
 * After this call, the component instance will be removed from the
 * framework. If the component instance was created by the
 * framework, it will be destroyed, not recycled, The behavior of
 * any port references obtained from this component instance and
 * stored elsewhere becomes undefined.
 * 
 * Notes for the component implementor:
 * 1) The component writer may perform blocking activities
 * within releaseServices, such as waiting for remote computations
 * to shutdown.
 * 2) It is good practice during releaseServices for the component
 * writer to remove or unregister all the ports it defined.
 */
void
ccafe6::TestMPI_impl::releaseServices (
  /* in */ ::gov::cca::Services Svc ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI.releaseServices)
  svc.unregisterUsesPort("MPIService");
  svc.unregisterUsesPort("MPIBorrow");
  svc.removeProvidesPort("go");
  svc = 0;
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI.releaseServices)
}

/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccafe6::TestMPI_impl::go ()
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI.go)
  // normally we should not check all these things, but
  // this is for a test driver that wants thorough diagnosis.
  try {
   gov::cca::Port sp = svc.getPort("MPIService");
   gov::cca::Port bp = svc.getPort("MPIBorrow");
   if (sp._is_nil()) {
	WHINE(" found no port connected for MPIService");
   }
   if (bp._is_nil()) {
	WHINE(" found no port connected for MPIBorrow");
   }
   ccaffeine::ports::MPIService ms = sp;
   ccaffeine::ports::MPIBorrow mb = bp;
   if (ms._is_nil()) {
	WHINE(" found incorrect port type for MPIService");
   }
   if (mb._is_nil()) {
	WHINE(" found incorrect port type for MPIBorrow");
   }
   ::sidl::array< int32_t > taglist = ::sidl::array< int32_t >::create1d( 1 );
   int32_t key = 0;
   int64_t borrowComm = mb.borrowComm(1, taglist, key);
   if (borrowComm == 0) {
	WHINE(" found 0 for MPIBorrow");
   }
   MPI_Fint fbComm = (MPI_Fint)borrowComm;
   MPI_Comm bComm = MPI_Comm_f2c(fbComm);
   if (bComm == MPI_COMM_NULL) {
	WHINE(" found MPI_COMM_NULL for MPIBorrow");
   }

   int64_t myComm = ms.getComm();
   if (myComm == 0) {
	WHINE(" found 0 for MPIService");
   }
   MPI_Fint fmComm = (MPI_Fint)myComm;
   MPI_Comm fComm = MPI_Comm_f2c(fmComm);
   if (fComm == MPI_COMM_NULL) {
	WHINE(" found MPI_COMM_NULL for MPIService");
   }

   int brank = 0; 
   int frank = 0;
   int errb = MPI_Comm_rank(bComm, &brank);
   int errf = MPI_Comm_rank(fComm, &frank);
   IO_dn2("found borrowed rank = %d\n", brank);
   IO_dn2("found service rank = %d\n", frank);

   ms.releaseComm(myComm);
   mb.returnComm(borrowComm,1,taglist,key);
   svc.releasePort("MPIBorrow");
   svc.releasePort("MPIService");

   IO_en1("TestMPI.go completed ok.");
   return 0;
  } catch ( gov::cca::CCAException ex ) {
   std::string s = ex.getNote();
   IO_en1("ERROR TestMPI.go FAILED.");
   IO_en2("%s",s.c_str());
   return -1;
  }
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI.go)
}


// DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._misc)
// Insert-Code-Here {ccafe6.TestMPI._misc} (miscellaneous code)
// DO-NOT-DELETE splicer.end(ccafe6.TestMPI._misc)

