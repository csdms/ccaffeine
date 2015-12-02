// 
// File:          ccafe5_GUIServiceTest_Impl.hh
// Symbol:        ccafe5.GUIServiceTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe5.GUIServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe5_GUIServiceTest_Impl_hh
#define included_ccafe5_GUIServiceTest_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe5_GUIServiceTest_IOR_h
#include "ccafe5_GUIServiceTest_IOR.h"
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
#ifndef included_ccafe5_GUIServiceTest_hh
#include "ccafe5_GUIServiceTest.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._includes)

#include "dc/babel/babel-cca/server/ccaffeine_TypeMap.hh"
#include "gov_cca_ports_GoPort.hh"
#include "util/IO.h"

// we hate doing this FIXME
#include "gov_cca.hh"

// DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._includes)

namespace ccafe5 { 

  /**
   * Symbol "ccafe5.GUIServiceTest" (version 0.1)
   * 
   * When the GoPort is hit, use the StringConsumerPort to send a
   * string. 
   */
  class GUIServiceTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    GUIServiceTest self;

    // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._implementation)

    gov::cca::Services svc; 

    // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._implementation)

  private:
    // private default constructor (required)
    GUIServiceTest_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    GUIServiceTest_impl( struct ccafe5_GUIServiceTest__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~GUIServiceTest_impl() { _dtor(); }

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

  };  // end class GUIServiceTest_impl

} // end namespace ccafe5

// DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._misc)

#endif
