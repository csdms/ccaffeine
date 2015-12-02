// 
// File:          ccafe4_ParameterPortFactoryTest_Impl.hh
// Symbol:        ccafe4.ParameterPortFactoryTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe4.ParameterPortFactoryTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe4_ParameterPortFactoryTest_Impl_hh
#define included_ccafe4_ParameterPortFactoryTest_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe4_ParameterPortFactoryTest_IOR_h
#include "ccafe4_ParameterPortFactoryTest_IOR.h"
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
#ifndef included_ccafe4_ParameterPortFactoryTest_hh
#include "ccafe4_ParameterPortFactoryTest.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._includes)

#include "gov_cca_ports_ParameterPortFactory.hh"
#include "gov_cca_ports_ParameterPort.hh"
#include "gov_cca_ports_GoPort.hh"
#include "util/IO.h"
#include <vector>
// arg FIXME
#include "gov_cca.hh"

// DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._includes)

namespace ccafe4 { 

  /**
   * Symbol "ccafe4.ParameterPortFactoryTest" (version 0.1)
   * 
   * When the GoPort is hit, use the ParameterPortFactory.  
   */
  class ParameterPortFactoryTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ParameterPortFactoryTest self;

    // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._implementation)

    gov::cca::ports::ParameterPortFactory ppf;
    gov::cca::ports::ParameterPort pp;
    gov::cca::Services svc;
    std::vector< gov::cca::TypeMap > pplist;
    int numtests;
    
    // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._implementation)

  private:
    // private default constructor (required)
    ParameterPortFactoryTest_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ParameterPortFactoryTest_impl( struct 
      ccafe4_ParameterPortFactoryTest__object * s ) : self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ParameterPortFactoryTest_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

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
     * The component wishing to be told after a parameter is changed
     * implements this function.
     * @param portName the name of the port (typemap) on which the
     * value was set.
     * @param fieldName the name of the value in the typemap.
     */
    void
    updatedParameterValue (
      /*in*/ const ::std::string& portName,
      /*in*/ const ::std::string& fieldName
    )
    throw () 
    ;


    /**
     * Inform the listener that someone is about to fetch their 
     * typemap. The return should be true if the listener
     * has changed the ParameterPort definitions.
     */
    bool
    updateParameterPort (
      /*in*/ const ::std::string& portName
    )
    throw () 
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

  };  // end class ParameterPortFactoryTest_impl

} // end namespace ccafe4

// DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._misc)

#endif
