// 
// File:          ccafe0_PrinterComponent_Impl.hh
// Symbol:        ccafe0.PrinterComponent-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe0.PrinterComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe0_PrinterComponent_Impl_hh
#define included_ccafe0_PrinterComponent_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe0_PrinterComponent_IOR_h
#include "ccafe0_PrinterComponent_IOR.h"
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
#ifndef included_ccafe0_PrinterComponent_hh
#include "ccafe0_PrinterComponent.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._includes)

#include <stdio.h>
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "dc/babel/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hh"
#include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._includes)

namespace ccafe0 { 

  /**
   * Symbol "ccafe0.PrinterComponent" (version 0.0)
   * 
   * When a string is set on this component, it prints it out. 
   */
  class PrinterComponent_impl
  // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    PrinterComponent self;

    // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._implementation)

    gov::cca::Services svc;

    // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._implementation)

  private:
    // private default constructor (required)
    PrinterComponent_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    PrinterComponent_impl( struct ccafe0_PrinterComponent__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~PrinterComponent_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


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

  };  // end class PrinterComponent_impl

} // end namespace ccafe0

// DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._misc)

#endif
