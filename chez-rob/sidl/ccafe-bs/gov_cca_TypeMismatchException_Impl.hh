// 
// File:          gov_cca_TypeMismatchException_Impl.hh
// Symbol:        gov.cca.TypeMismatchException-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020415 11:31:48 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for gov.cca.TypeMismatchException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_gov_cca_TypeMismatchException_Impl_hh
#define included_gov_cca_TypeMismatchException_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_gov_cca_TypeMismatchException_IOR_h
#include "gov_cca_TypeMismatchException_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_gov_cca_CCAExceptionType_hh
#include "gov_cca_CCAExceptionType.hh"
#endif
#ifndef included_gov_cca_Type_hh
#include "gov_cca_Type.hh"
#endif
#ifndef included_gov_cca_TypeMismatchException_hh
#include "gov_cca_TypeMismatchException.hh"
#endif


// DO-NOT-DELETE splicer.begin(gov.cca.TypeMismatchException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(gov.cca.TypeMismatchException._includes)

namespace gov { 
  namespace cca { 

    /**
     * Symbol "gov.cca.TypeMismatchException" (version 0.0.0)
     * 
     * The CCA typemismatch definition.
     * Not to be confused with a PortType mismatch or class mismatch.
     */
    class TypeMismatchException_impl {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      TypeMismatchException self;

      // DO-NOT-DELETE splicer.begin(gov.cca.TypeMismatchException._implementation)
      // Put additional implementation details here...
      // DO-NOT-DELETE splicer.end(gov.cca.TypeMismatchException._implementation)

    private:
      // private default constructor (required)
      TypeMismatchException_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      TypeMismatchException_impl( struct gov_cca_TypeMismatchException__object 
        * s ) : self(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~TypeMismatchException_impl() { _dtor(); }

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
    };  // end class TypeMismatchException_impl

  } // end namespace cca
} // end namespace gov

// DO-NOT-DELETE splicer.begin(gov.cca.TypeMismatchException._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(gov.cca.TypeMismatchException._misc)

#endif
