// 
// File:          ccaffeine_CcafeConnectionID_Impl.hh
// Symbol:        ccaffeine.CcafeConnectionID-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:14 PDT
// Generated:     20020510 17:32:21 PDT
// Description:   Server-side implementation for ccaffeine.CcafeConnectionID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_CcafeConnectionID_Impl_hh
#define included_ccaffeine_CcafeConnectionID_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_CcafeConnectionID_IOR_h
#include "ccaffeine_CcafeConnectionID_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_ccaffeine_CcafeConnectionID_hh
#include "ccaffeine_CcafeConnectionID.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_ComponentID_hh
#include "gov_cca_ComponentID.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._includes)

#include "ccaffeine_CcafeComponentID.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.CcafeConnectionID" (version 0.0.0)
   * 
   * This interface describes a CCA connection between components.
   * A connection is made at the users direction
   * when one component provides a Port that another component
   * advertises for and uses.  The components are referred to by their
   * opaque ComponentID references and the Ports are referred to
   * by their string instance names.
   */
  class CcafeConnectionID_impl {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    CcafeConnectionID self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._implementation)

    ccaffeine::CcafeComponentID provider;
    std::string providerName;
    ccaffeine::CcafeComponentID user;
    std::string userName;

    // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._implementation)

  private:
    // private default constructor (required)
    CcafeConnectionID_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    CcafeConnectionID_impl( struct ccaffeine_CcafeConnectionID__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~CcafeConnectionID_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Get the providing component (callee) ID.
     * @return the ComponentID of the component that has 
     * provided the Port for this connection. 
     * @throws a CCAException if the underlying connection is no longer valid.
     */
    gov::cca::ComponentID
    getProvider() throw ( 
      gov::cca::CCAException
    );

    /**
     * Get the port name in the providing component of this connection.
     * @return the instance name of the provided Port.
     * @throws CCAException if the underlying connection is no longer valid.
     */
    std::string
    getProviderPortName() throw ( 
      gov::cca::CCAException
    );

    /**
     * Get the using component (caller) ID.
     * @return the ComponentID of the component that is using the provided Port.
     * @throws a CCAException if the underlying connection is no longer valid.
     */
    gov::cca::ComponentID
    getUser() throw ( 
      gov::cca::CCAException
    );

    /**
     * Get the port name in the using component of this connection.
     * @return the instance name of the Port registered for use in 
     * this connection.
     * @throws CCAException if the underlying connection is no longer valid.
     */
    std::string
    getUserPortName() throw ( 
      gov::cca::CCAException
    );

    /**
     * init one of these 
     */
    void
    initialize (
      /*in*/ gov::cca::ComponentID provider,
      /*in*/ std::string providerName,
      /*in*/ gov::cca::ComponentID user,
      /*in*/ std::string username
    )
    throw () 
    ;

  };  // end class CcafeConnectionID_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._misc)

#endif
