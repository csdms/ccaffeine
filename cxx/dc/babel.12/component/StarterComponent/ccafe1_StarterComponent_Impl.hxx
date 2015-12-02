// 
// File:          ccafe1_StarterComponent_Impl.hh
// Symbol:        ccafe1.StarterComponent-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe1.StarterComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe1_StarterComponent_Impl_hh
#define included_ccafe1_StarterComponent_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe1_StarterComponent_IOR_h
#include "ccafe1_StarterComponent_IOR.h"
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
#ifndef included_ccafe1_StarterComponent_hh
#include "ccafe1_StarterComponent.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe1.StarterComponent._hincludes)

#include "dc/babel.12/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hxx"
#include "dc/babel.12/babel-cca/server/ccaffeine_TypeMap.hxx"
#include "gov_cca_ports_GoPort.hxx"
#include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccafe1.StarterComponent._hincludes)

namespace ccafe1 { 

  /**
   * Symbol "ccafe1.StarterComponent" (version 0.1)
   * 
   * When the GoPort is hit, use the StringConsumerPort to send a
   * string. 
   */
  class StarterComponent_impl
  // DO-NOT-DELETE splicer.begin(ccafe1.StarterComponent._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe1.StarterComponent._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    StarterComponent self;

    // DO-NOT-DELETE splicer.begin(ccafe1.StarterComponent._implementation)

    gov::cca::Services svc; 

    // DO-NOT-DELETE splicer.end(ccafe1.StarterComponent._implementation)

  private:
    // private default constructor (required)
    StarterComponent_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    StarterComponent_impl( struct ccafe1_StarterComponent__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~StarterComponent_impl() { _dtor(); }

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
     * Obtain Services handle, through which the 
     * component communicates with the framework. 
     * This is the one method that every CCA Component
     * must implement. The component will be called
     * with a nil/null Services pointer when it is
     * to shut itself down.
     */
    void
    setServices (
      /*in*/ ::gov::cca::Services services
    )
    throw () 
    ;

  };  // end class StarterComponent_impl

} // end namespace ccafe1

// DO-NOT-DELETE splicer.begin(ccafe1.StarterComponent._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe1.StarterComponent._hmisc)

#endif
