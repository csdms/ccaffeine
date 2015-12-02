// 
// File:          ccafe6_TestMPI_Impl.hh
// Symbol:        ccafe6.TestMPI-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe6.TestMPI
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe6_TestMPI_Impl_hh
#define included_ccafe6_TestMPI_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_ccafe6_TestMPI_IOR_h
#include "ccafe6_TestMPI_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccafe6_TestMPI_hh
#include "ccafe6_TestMPI.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._hincludes)

#include "util/IO.h"
#include "dc/babel.12/babel-cca/server/ccaffeine_ports_MPIService.hxx"
#include "dc/babel.12/babel-cca/server/ccaffeine_ports_MPIBorrow.hxx"
#include "dc/babel.12/babel-cca/server/ccaffeine_CCAException.hxx"
#include "gov_cca_ports.hxx"

// DO-NOT-DELETE splicer.end(ccafe6.TestMPI._hincludes)

namespace ccafe6 { 

  /**
   * Symbol "ccafe6.TestMPI" (version 0.0)
   * 
   * Test mpiborrow and mpiservice.
   */
  class TestMPI_impl
  // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._inherits)
  // Insert-Code-Here {ccafe6.TestMPI._inherits} (optional inheritance here)
  // DO-NOT-DELETE splicer.end(ccafe6.TestMPI._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    TestMPI self;

    // DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._implementation)
    // Insert-Code-Here {ccafe6.TestMPI._implementation} (additional details)
    gov::cca::Services svc;
    // DO-NOT-DELETE splicer.end(ccafe6.TestMPI._implementation)

  private:
    // private default constructor (required)
    TestMPI_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    TestMPI_impl( struct ccafe6_TestMPI__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~TestMPI_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:


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
    setServices (
      /* in */ ::gov::cca::Services services
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    releaseServices (
      /* in */ ::gov::cca::Services Svc
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Execute some encapsulated functionality on the component. 
     * Return 0 if ok, -1 if internal error but component may be 
     * used further, and -2 if error so severe that component cannot
     * be further used safely.
     */
    int32_t
    go() throw () 
    ;
  };  // end class TestMPI_impl

} // end namespace ccafe6

// DO-NOT-DELETE splicer.begin(ccafe6.TestMPI._hmisc)
// Insert-Code-Here {ccafe6.TestMPI._hmisc} (miscellaneous things)
// DO-NOT-DELETE splicer.end(ccafe6.TestMPI._hmisc)

#endif
