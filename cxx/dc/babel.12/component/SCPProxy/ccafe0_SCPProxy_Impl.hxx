// 
// File:          ccafe0_SCPProxy_Impl.hh
// Symbol:        ccafe0.SCPProxy-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe0.SCPProxy
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe0_SCPProxy_Impl_hh
#define included_ccafe0_SCPProxy_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_ccafe0_SCPProxy_IOR_h
#include "ccafe0_SCPProxy_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccafe0_SCPProxy_hh
#include "ccafe0_SCPProxy.hh"
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


// DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._hincludes)

#include <cstdio>
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "dc/babel.12/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hxx"
#include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._hincludes)

namespace ccafe0 { 

  /**
   * Symbol "ccafe0.SCPProxy" (version 0.0)
   * 
   * When a string is set on this component, it prints it out. 
   */
  class SCPProxy_impl
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    SCPProxy self;

    // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._implementation)

    gov::cca::Services svc;

    // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._implementation)

  private:
    // private default constructor (required)
    SCPProxy_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    SCPProxy_impl( struct ccafe0_SCPProxy__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~SCPProxy_impl() { _dtor(); }

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
     * Receive a string from another component.   
     */
    void
    setString (
      /* in */ const ::std::string& s
    )
    throw () 
    ;

  };  // end class SCPProxy_impl

} // end namespace ccafe0

// DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._hmisc)

#endif
