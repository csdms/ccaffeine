// 
// File:          ccafe2_SimpleProxyTest_Impl.hh
// Symbol:        ccafe2.SimpleProxyTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe2.SimpleProxyTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe2_SimpleProxyTest_Impl_hh
#define included_ccafe2_SimpleProxyTest_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_ccafe2_SimpleProxyTest_IOR_h
#include "ccafe2_SimpleProxyTest_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccafe2_SimpleProxyTest_hh
#include "ccafe2_SimpleProxyTest.hh"
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


// DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._includes)
// Put additional includes or other arbitrary code here...
#include <gov_cca.hh>
#include <gov_cca_ports.hh>
#include <vector>
#include <map>
// DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._includes)

namespace ccafe2 { 

  /**
   * Symbol "ccafe2.SimpleProxyTest" (version 0.1)
   * 
   * When the GoPort is first hit, 
   * use the BuilderService to 
   * - create starter, printer, connect, go starter.
   * On second go hit,
   * - disconnect starter, printer.
   * - create proxy.
   * - connect proxies.
   * - go starter.
   * On subsequent hits, ignore the user.
   * We probably don't even need to know we're
   * dealing with stringconsumerport.
   */
  class SimpleProxyTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    SimpleProxyTest self;

    // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._implementation)
    std::map< std::string, std::string > pnames;
    gov::cca::Services svc;
    gov::cca::ports::BuilderService bs;
	/** not used at the moment */
    int numtests;
	/** numgos is the state our test machine is in. 
		0 == hasn't done anything.
		1 == created components and connected them
		2 == created proxy and reconnected to it.
		3 == disconnected proxy.
		10 == done or cannot continue for some reason.
	*/
    int numgos;
	/** generate appropriate complaints */
    void whine(const std::string & msg);

	int go1() throw ();
	int go2() throw ();
	int go3() throw ();
	int go4() throw ();
	gov::cca::ConnectionID findConnectionID(gov::cca::ComponentID user, const std::string & uport, gov::cca::ComponentID provider, const std::string & pport);
    // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._implementation)

  private:
    // private default constructor (required)
    SimpleProxyTest_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    SimpleProxyTest_impl( struct ccafe2_SimpleProxyTest__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~SimpleProxyTest_impl() { _dtor(); }

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
     * Execute some encapsulated functionality on the component. 
     * Return 0 if ok, -1 if internal error but component may be 
     * used further, and -2 if error so severe that component cannot
     * be further used safely.
     */
    int32_t
    go() throw () 
    ;

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

  };  // end class SimpleProxyTest_impl

} // end namespace ccafe2

// DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._misc)

#endif
