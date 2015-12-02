// 
// File:          ccaffeine_CcafeTypeMismatchException_Impl.hh
// Symbol:        ccaffeine.CcafeTypeMismatchException-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:14 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for ccaffeine.CcafeTypeMismatchException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_CcafeTypeMismatchException_Impl_hh
#define included_ccaffeine_CcafeTypeMismatchException_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_CcafeTypeMismatchException_IOR_h
#include "ccaffeine_CcafeTypeMismatchException_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_ccaffeine_CcafeTypeMismatchException_hh
#include "ccaffeine_CcafeTypeMismatchException.hh"
#endif
#ifndef included_gov_cca_CCAExceptionType_hh
#include "gov_cca_CCAExceptionType.hh"
#endif
#ifndef included_gov_cca_Type_hh
#include "gov_cca_Type.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.CcafeTypeMismatchException" (version 0.0.0)
   */
  class CcafeTypeMismatchException_impl {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    CcafeTypeMismatchException self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._implementation)
    
    gov::cca::Type__enum requested;
    gov::cca::Type__enum actual;


    // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._implementation)

  private:
    // private default constructor (required)
    CcafeTypeMismatchException_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    CcafeTypeMismatchException_impl( struct 
      ccaffeine_CcafeTypeMismatchException__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~CcafeTypeMismatchException_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * @return the enumerated Type of the value actually found. 
     */
    gov::cca::Type__enum
    getActualType() throw () 
    ;

    /**
     * @return the enumerated value Type sought. 
     */
    gov::cca::Type__enum
    getRequestedType() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ gov::cca::Type__enum requested,
      /*in*/ gov::cca::Type__enum actual
    )
    throw () 
    ;

  };  // end class CcafeTypeMismatchException_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._misc)

#endif
