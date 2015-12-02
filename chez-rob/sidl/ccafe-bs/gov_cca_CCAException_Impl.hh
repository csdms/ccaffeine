// 
// File:          gov_cca_CCAException_Impl.hh
// Symbol:        gov.cca.CCAException-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020415 11:31:46 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for gov.cca.CCAException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_gov_cca_CCAException_Impl_hh
#define included_gov_cca_CCAException_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_gov_cca_CCAException_IOR_h
#include "gov_cca_CCAException_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_CCAExceptionType_hh
#include "gov_cca_CCAExceptionType.hh"
#endif


// DO-NOT-DELETE splicer.begin(gov.cca.CCAException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(gov.cca.CCAException._includes)

namespace gov { 
  namespace cca { 

    /**
     * Symbol "gov.cca.CCAException" (version 0.0.0)
     * 
     * The CCA exception type definition.
     */
    class CCAException_impl {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      CCAException self;

      // DO-NOT-DELETE splicer.begin(gov.cca.CCAException._implementation)
      // Put additional implementation details here...
      // DO-NOT-DELETE splicer.end(gov.cca.CCAException._implementation)

    private:
      // private default constructor (required)
      CCAException_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      CCAException_impl( struct gov_cca_CCAException__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~CCAException_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * @return a member of the enumeration in CCAExceptionType. 
       */
      gov::cca::CCAExceptionType__enum
      getType() throw () 
      ;

      /**
       * Set the type of an exception. 
       */
      void
      setType (
        /*in*/ gov::cca::CCAExceptionType__enum type
      )
      throw () 
      ;

    };  // end class CCAException_impl

  } // end namespace cca
} // end namespace gov

// DO-NOT-DELETE splicer.begin(gov.cca.CCAException._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(gov.cca.CCAException._misc)

#endif
