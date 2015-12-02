// 
// File:          ccafe2_ServiceRegistryTest_Impl.hh
// Symbol:        ccafe2.ServiceRegistryTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe2.ServiceRegistryTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe2_ServiceRegistryTest_Impl_hh
#define included_ccafe2_ServiceRegistryTest_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe2_ServiceRegistryTest_IOR_h
#include "ccafe2_ServiceRegistryTest_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_SIDL_ClassInfo_hh
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccafe2_ServiceRegistryTest_hh
#include "ccafe2_ServiceRegistryTest.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._hincludes)
// Put additional includes or other arbitrary code here...
#include <gov_cca.hxx>
#include <gov_cca_ports.hxx>
#include <vector>
#include <map>
// DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._hincludes)

namespace ccafe2 { 

  /**
   * Symbol "ccafe2.ServiceRegistryTest" (version 0.1)
   * 
   * Use serviceRegistry, then when the GoPort is hit, use the 
   * ServiceRegistry to remove the singleton service and
   * add a multiple service.
   */
  class ServiceRegistryTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ServiceRegistryTest self;

    // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._implementation)
    std::map< std::string, std::string > pnames;
    gov::cca::Services svc;
    int numtests;
    int numgos;
    void whine(const std::string & msg);
    // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._implementation)

  private:
    // private default constructor (required)
    ServiceRegistryTest_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ServiceRegistryTest_impl( struct ccafe2_ServiceRegistryTest__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ServiceRegistryTest_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    void
    releaseServices (
      /*in*/ ::gov::cca::Services Svc
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Receive a string from another component.   
     */
    void
    setString (
      /*in*/ const ::std::string& s
    )
    throw () 
    ;


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
     * @param Svc the component instance's handle on the framework world.
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
      /*in*/ ::gov::cca::Services services
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Create the Port for the Service, informing the framework through
     * "addProvidesPort()" on the originating component.
     * @return the name of the port created.
     */
    ::std::string
    createService (
      /*in*/ const ::std::string& portType
    )
    throw () 
    ;


    /**
     * Informs the originating component that the instance of the
     * provided service is no longer needed. The ServiceProvider
     * can now safely removePort on the named port.
     */
    void
    destroyService (
      /*in*/ const ::std::string& portName
    )
    throw () 
    ;

  };  // end class ServiceRegistryTest_impl

} // end namespace ccafe2

// DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._hmisc)

#endif
