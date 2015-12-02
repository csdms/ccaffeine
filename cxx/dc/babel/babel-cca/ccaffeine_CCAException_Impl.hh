// 
// File:          ccaffeine_CCAException_Impl.hh
// Symbol:        ccaffeine.CCAException-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.CCAException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_CCAException_Impl_hh
#define included_ccaffeine_CCAException_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_CCAException_IOR_h
#include "ccaffeine_CCAException_IOR.h"
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
#ifndef included_ccaffeine_CCAException_hh
#include "ccaffeine_CCAException.hh"
#endif
#ifndef included_gov_cca_CCAExceptionType_hh
#include "gov_cca_CCAExceptionType.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CCAException._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.CCAException" (version 0.3)
   */
  class CCAException_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.CCAException._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    CCAException self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._implementation)
    gov::cca::CCAExceptionType e;
    // DO-NOT-DELETE splicer.end(ccaffeine.CCAException._implementation)

  private:
    // private default constructor (required)
    CCAException_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    CCAException_impl( struct ccaffeine_CCAException__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~CCAException_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    ::gov::cca::CCAExceptionType
    getCCAExceptionType() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setCCAExceptionType (
      /*in*/ ::gov::cca::CCAExceptionType et
    )
    throw () 
    ;

  };  // end class CCAException_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.CCAException._misc)

#endif
