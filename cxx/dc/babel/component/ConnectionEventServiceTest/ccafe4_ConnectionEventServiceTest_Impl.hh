// 
// File:          ccafe4_ConnectionEventServiceTest_Impl.hh
// Symbol:        ccafe4.ConnectionEventServiceTest-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe4.ConnectionEventServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe4_ConnectionEventServiceTest_Impl_hh
#define included_ccafe4_ConnectionEventServiceTest_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_ccafe4_ConnectionEventServiceTest_IOR_h
#include "ccafe4_ConnectionEventServiceTest_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccafe4_ConnectionEventServiceTest_hh
#include "ccafe4_ConnectionEventServiceTest.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif
#ifndef included_gov_cca_ports_ConnectionEvent_hh
#include "gov_cca_ports_ConnectionEvent.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._includes)

#include "gov_cca_ports_ConnectionEventService.hh"
#include "ccafe3_StringConsumerPort.hh"
#include "gov_cca_ports_GoPort.hh"
#include "util/IO.h"
// arg FIXME
#include "gov_cca.hh"

// DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._includes)

namespace ccafe4 { 

  /**
   * Symbol "ccafe4.ConnectionEventServiceTest" (version 0.0)
   * 
   * When the GoPort is hit, test the ConnectionEventService via
   * BuilderService means.  
   */
  class ConnectionEventServiceTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ConnectionEventServiceTest self;

    // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._implementation)

    gov::cca::ports::ConnectionEventService ces;
    ccafe3::StringConsumerPort scp; // our uses stringer port.
    gov::cca::Services svc;
    int numtests;
    
    // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._implementation)

  private:
    // private default constructor (required)
    ConnectionEventServiceTest_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ConnectionEventServiceTest_impl( struct 
      ccafe4_ConnectionEventServiceTest__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ConnectionEventServiceTest_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:


    /**
     * Execute some encapsulated functionality on the component. 
     * Return 0 if ok, -1 if internal error but component may be 
     * used further, and -2 if error so severe that component cannot
     * be further used safely.
     */
    int32_t
    go() throw () 
    ;

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
      /* in */ ::gov::cca::Services services
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Called on all listeners when a connection is made or broken. 
     */
    void
    connectionActivity (
      /* in */ ::gov::cca::ports::ConnectionEvent ce
    )
    throw () 
    ;


    /**
     * Receive a string from another component.   
     */
    void
    setString (
      /* in */ const ::std::string& s
    )
    throw () 
    ;

  };  // end class ConnectionEventServiceTest_impl

} // end namespace ccafe4

// DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._misc)

#endif
