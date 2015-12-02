// 
// File:          ccaffeine_ConnectionID_Impl.hxx
// Symbol:        ccaffeine.ConnectionID-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ConnectionID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ConnectionID_Impl_hxx
#define included_ccaffeine_ConnectionID_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ConnectionID_IOR_h
#include "ccaffeine_ConnectionID_IOR.h"
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
#ifndef included_ccaffeine_ConnectionID_hxx
#include "ccaffeine_ConnectionID.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_ComponentID_hxx
#include "gov_cca_ComponentID.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._hincludes)
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include <AllCCA.hh>
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "ccaffeine_TypeMap.hxx"
#include "ccaffeine_ComponentID.hxx"
#include "ccaffeine_CCAException.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._hincludes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.ConnectionID" (version 0.3)
   * 
   * This is a wrapper class. It cannot be successfully
   * constructed directly from component or client code.
   * Only the ccaffeine framework
   * internals know how to initialize this object.
   */
  class ConnectionID_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ConnectionID self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._implementation)
    ::ccafeopq::ConnectionID_shared oconnid;
    int serial;
    static int nextNum() { genSerial++; return genSerial; }
    static int genSerial;
  public:
    static ::ccaffeine::ConnectionID babelWrap( ::ccafeopq::ConnectionID_shared kernel);
    static sidl::array< ::gov::cca::ConnectionID >
	       convertToSidlArray( ::std::vector< ::ccafeopq::ConnectionID_shared > &val );

    // Put additional implementation details here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._implementation)

  private:
    // private default constructor (required)
    ConnectionID_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ConnectionID_impl( struct ccaffeine_ConnectionID__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ConnectionID_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* opaque_ConnectionID_addr
    )
    throw () 
    ;


    /**
     *  Get the providing component (callee) ID.
     *  @return ComponentID of the component that has 
     *          provided the Port for this connection. 
     *  @throws CCAException if the underlying connection 
     *            is no longer valid.
     */
    ::gov::cca::ComponentID
    getProvider() throw ( 
      ::gov::cca::CCAException
    );

    /**
     *  Get the using component (caller) ID.
     *  @return ComponentID of the component that is using the provided Port.
     *  @throws CCAException if the underlying connection is no longer valid.
     */
    ::gov::cca::ComponentID
    getUser() throw ( 
      ::gov::cca::CCAException
    );

    /**
     *  Get the port name in the providing component of this connection.
     *  @return the instance name of the provided Port.
     *  @throws CCAException if the underlying connection is no longer valid.
     */
    ::std::string
    getProviderPortName() throw ( 
      ::gov::cca::CCAException
    );

    /**
     *  Get the port name in the using component of this connection.
     *  Return the instance name of the Port registered for use in 
     *  this connection.
     *  @throws CCAException if the underlying connection is no longer valid.
     */
    ::std::string
    getUserPortName() throw ( 
      ::gov::cca::CCAException
    );
  };  // end class ConnectionID_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._hmisc)

#endif
