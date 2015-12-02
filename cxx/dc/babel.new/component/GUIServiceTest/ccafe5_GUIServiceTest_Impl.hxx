// 
// File:          ccafe5_GUIServiceTest_Impl.hxx
// Symbol:        ccafe5.GUIServiceTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe5.GUIServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe5_GUIServiceTest_Impl_hxx
#define included_ccafe5_GUIServiceTest_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccafe5_GUIServiceTest_IOR_h
#include "ccafe5_GUIServiceTest_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_ccafe5_GUIServiceTest_hxx
#include "ccafe5_GUIServiceTest.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._includes)

#include "dc/babel.new/babel-cca/server/ccaffeine_TypeMap.hxx"
#include "gov_cca_ports_GoPort.hxx"
#include "util/IO.h"

// we hate doing this FIXME
#include "gov_cca.hxx"

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
    GUIServiceTest (*this);

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
      (*this)(s,true) { _ctor(); }

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
     * to shut it(*this) down.
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
