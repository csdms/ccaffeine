// 
// File:          ccaffeine_TypeMismatchException_Impl.hxx
// Symbol:        ccaffeine.TypeMismatchException-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.TypeMismatchException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_TypeMismatchException_Impl_hxx
#define included_ccaffeine_TypeMismatchException_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_TypeMismatchException_IOR_h
#include "ccaffeine_TypeMismatchException_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccaffeine_TypeMismatchException_hxx
#include "ccaffeine_TypeMismatchException.hxx"
#endif
#ifndef included_gov_cca_CCAExceptionType_hxx
#include "gov_cca_CCAExceptionType.hxx"
#endif
#ifndef included_gov_cca_Type_hxx
#include "gov_cca_Type.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._hincludes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._hincludes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.TypeMismatchException" (version 0.3)
   * 
   * Component writers can throw this instead of CCAException
   * if they feel the urge.
   */
  class TypeMismatchException_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    TypeMismatchException self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._implementation)
    gov::cca::Type rType;
    gov::cca::Type aType;
    // Put additional implementation details here...
    // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._implementation)

  private:
    // private default constructor (required)
    TypeMismatchException_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    TypeMismatchException_impl( struct ccaffeine_TypeMismatchException__object 
      * s ) : self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~TypeMismatchException_impl() { _dtor(); }

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
    ::gov::cca::Type
    getRequestedType() throw () 
    ;
    /**
     * user defined non-static method.
     */
    ::gov::cca::Type
    getActualType() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    initializeTypes (
      /*in*/ ::gov::cca::Type requestedType,
      /*in*/ ::gov::cca::Type actualType
    )
    throw () 
    ;

  };  // end class TypeMismatchException_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._hmisc)

#endif
