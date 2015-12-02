// 
// File:          ccaffeine_CcafeComponentID_Impl.hh
// Symbol:        ccaffeine.CcafeComponentID-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:14 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for ccaffeine.CcafeComponentID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_CcafeComponentID_Impl_hh
#define included_ccaffeine_CcafeComponentID_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_CcafeComponentID_IOR_h
#include "ccaffeine_CcafeComponentID_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_ccaffeine_CcafeComponentID_hh
#include "ccaffeine_CcafeComponentID.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.CcafeComponentID" (version 0.0.0)
   * 
   * An opaque reference to a Component. 
   */
  class CcafeComponentID_impl {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    CcafeComponentID self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._implementation)

    std::string instanceName;

    // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._implementation)

  private:
    // private default constructor (required)
    CcafeComponentID_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    CcafeComponentID_impl( struct ccaffeine_CcafeComponentID__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~CcafeComponentID_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Returns the instance name provided in 
     * BuilderService.createInstance()
     * or in
     * AbstractFramework.getServices().
     * @throws CCAException if ComponentID is invalid.
     */
    std::string
    getInstanceName() throw ( 
      gov::cca::CCAException
    );

    /**
     * Returns a framework specific serialization of the ComponentID.
     * @throws CCAException if ComponentID is invalid.
     */
    std::string
    getSerialization() throw ( 
      gov::cca::CCAException
    );

    /**
     * initialize one of these. 
     */
    void
    initialize (
      /*in*/ std::string instanceName
    )
    throw () 
    ;

  };  // end class CcafeComponentID_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._misc)

#endif
