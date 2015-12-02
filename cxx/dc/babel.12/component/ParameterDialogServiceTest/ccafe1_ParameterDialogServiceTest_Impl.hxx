// 
// File:          ccafe1_ParameterDialogServiceTest_Impl.hh
// Symbol:        ccafe1.ParameterDialogServiceTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe1.ParameterDialogServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe1_ParameterDialogServiceTest_Impl_hh
#define included_ccafe1_ParameterDialogServiceTest_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe1_ParameterDialogServiceTest_IOR_h
#include "ccafe1_ParameterDialogServiceTest_IOR.h"
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
#ifndef included_ccafe1_ParameterDialogServiceTest_hh
#include "ccafe1_ParameterDialogServiceTest.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._hincludes)
// Put additional includes or other arbitrary code here...
#include "dc/babel.12/babel-cca/server/ccaffeine_ports_ParameterDialogService.hxx"
#include "gov_cca_ports_GoPort.hxx"
#include "util/IO.h"
#include <vector>

// DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._hincludes)

namespace ccafe1 { 

  /**
   * Symbol "ccafe1.ParameterDialogServiceTest" (version 0.1)
   * 
   * When the GoPort is hit, use the ParameterDialogService.  
   */
  class ParameterDialogServiceTest_impl
  // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ParameterDialogServiceTest self;

    // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._implementation)
    
    ccaffeine::ports::ParameterDialogService pds;
    gov::cca::Services svc;
    std::vector< gov::cca::TypeMap > pplist;
    int numtests;
    
    // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._implementation)

  private:
    // private default constructor (required)
    ParameterDialogServiceTest_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ParameterDialogServiceTest_impl( struct 
      ccafe1_ParameterDialogServiceTest__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ParameterDialogServiceTest_impl() { _dtor(); }

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

  };  // end class ParameterDialogServiceTest_impl

} // end namespace ccafe1

// DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._hmisc)

#endif
