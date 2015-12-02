// 
// File:          ccaffeine_ConnectionID_Impl.cc
// Symbol:        ccaffeine.ConnectionID-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ConnectionID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ConnectionID_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._includes)
// Put additional includes or other arbitrary code here...
int ccaffeine::ConnectionID_impl::genSerial = 0;

// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._includes)

// user defined constructor
void ccaffeine::ConnectionID_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._ctor)
  serial = nextNum();
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ConnectionID_impl _ctor %d", serial);
#endif
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._ctor)
}

// user defined destructor
void ccaffeine::ConnectionID_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._dtor)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ConnectionID_impl _dtor %d", serial);
#endif
  serial = -serial;
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ConnectionID_impl::initialize (
  /*in*/ void* opaque_ConnectionID_addr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID.initialize)
#ifdef CCAFE_AUDIT
  IO_dn2("ConnectionID_impl init %d", serial);
#endif
  if (opaque_ConnectionID_addr == 0) {
#ifdef CCAFE_AUDIT
    IO_dn2("ConnectionID_impl init %d called with null", serial);
#endif
    return;
  }
  ::ccafeopq::ConnectionID_shared *oconnid_addr = 0;
  oconnid_addr =
    static_cast< ::ccafeopq::ConnectionID_shared * >(opaque_ConnectionID_addr);
  oconnid = *oconnid_addr;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID.initialize)
}

/**
 *  Get the providing component (callee) ID.
 *  @return ComponentID of the component that has 
 *          provided the Port for this connection. 
 *  @throws CCAException if the underlying connection 
 *            is no longer valid.
 */
::gov::cca::ComponentID
ccaffeine::ConnectionID_impl::getProvider () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID.getProvider)
  // insert implementation here
  if (!oconnid) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage("oconnid uninitialized");
    ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, "getProvider");
    ::gov::cca::CCAException gex = ex; // cast
    throw gex;
  }
  ::ccaffeine::ComponentID cid = ::ccaffeine::ComponentID::_create();
  ::ccafeopq::ComponentID_shared oid;
  ::ccafeopq::ComponentID_shared * oid_addr;
  oid = oconnid->getProvider();
  oid_addr = &oid;
  void * v = static_cast<void *>(oid_addr);
  cid.initialize(v);
  return cid;
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID.getProvider)
}

/**
 *  Get the using component (caller) ID.
 *  @return ComponentID of the component that is using the provided Port.
 *  @throws CCAException if the underlying connection is no longer valid.
 */
::gov::cca::ComponentID
ccaffeine::ConnectionID_impl::getUser () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID.getUser)
  // insert implementation here
  if (!oconnid) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage("oconnid uninitialized");
    ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, "getUser");
    ::gov::cca::CCAException gex = ex; // cast
    throw gex;
  }
  ::ccaffeine::ComponentID cid = ::ccaffeine::ComponentID::_create();
  ::ccafeopq::ComponentID_shared oid;
  ::ccafeopq::ComponentID_shared * oid_addr;
  oid = oconnid->getUser();
  oid_addr = &oid;
  void * v = static_cast<void *>(oid_addr);
  cid.initialize(v);
  return cid;
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID.getUser)
}

/**
 *  Get the port name in the providing component of this connection.
 *  @return the instance name of the provided Port.
 *  @throws CCAException if the underlying connection is no longer valid.
 */
::std::string
ccaffeine::ConnectionID_impl::getProviderPortName () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID.getProviderPortName)
  if (!oconnid) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage("oconnid uninitialized");
    ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, "getProviderPortName");
    ::gov::cca::CCAException gex = ex; // cast
    throw gex;
  }
  return oconnid->getProviderPortName();
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID.getProviderPortName)
}

/**
 *  Get the port name in the using component of this connection.
 *  Return the instance name of the Port registered for use in 
 *  this connection.
 *  @throws CCAException if the underlying connection is no longer valid.
 */
::std::string
ccaffeine::ConnectionID_impl::getUserPortName () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID.getUserPortName)
  if (!oconnid) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage("oconnid uninitialized");
    ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, "getUserPortName");
    ::gov::cca::CCAException gex = ex; // cast
    throw gex;
  }
  return oconnid->getUserPortName();
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID.getUserPortName)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionID._misc)
// Put miscellaneous code here
ccaffeine::ConnectionID
ccaffeine::ConnectionID_impl::babelWrap( ::ccafeopq::ConnectionID_shared kernel)
{
  ::ccaffeine::ConnectionID cid = ::ccaffeine::ConnectionID::_create();
  ::ccafeopq::ConnectionID_shared * oid_addr;
  oid_addr = &kernel;
  void * vp;
  vp = static_cast<void *>(oid_addr);
  cid.initialize(vp);
  return cid;
}

#ifdef HAVE_BABEL_PATCH_0_7_0
#define ASET(x) myarray.set( x, i )
#else
    /* 074 and later array api */
#define ASET(x) myarray.set( i , x )
#endif

sidl::array< ::gov::cca::ConnectionID >
ccaffeine::ConnectionID_impl::convertToSidlArray(
	                ::std::vector< ::ccafeopq::ConnectionID_shared > &val )
{
  size_t len = val.size();
  sidl::array< ::gov::cca::ConnectionID > myarray =
    sidl::array< ::gov::cca::ConnectionID >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    ::gov::cca::ConnectionID ncid = babelWrap(val[i]);
    ASET(ncid);
  }
  return myarray;
}
// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionID._misc)

