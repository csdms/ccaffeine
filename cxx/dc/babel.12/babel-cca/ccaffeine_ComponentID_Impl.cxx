// 
// File:          ccaffeine_ComponentID_Impl.cc
// Symbol:        ccaffeine.ComponentID-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ComponentID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ComponentID_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._includes)
// Put additional includes or other arbitrary code here...

int ccaffeine::ComponentID_impl::genSerial = 0;

// DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._includes)

// user defined constructor
void ccaffeine::ComponentID_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._ctor)
  //oid = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ComponentID_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._ctor)
}

// user defined destructor
void ccaffeine::ComponentID_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._dtor)
  // add destruction details here
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ComponentID_impl _dtor %d", serial);
  serial = -serial;
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ComponentID_impl::initialize (
  /*in*/ void* opaque_ComponentID_addr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID.initialize)
  ::ccafeopq::ComponentID_shared *coid = 0;
  coid = static_cast< ::ccafeopq::ComponentID_shared * >(opaque_ComponentID_addr);
  oid = *coid;
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ComponentID_impl init %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID.initialize)
}

/**
 * Returns the instance name provided in 
 * <code>BuilderService.createInstance()</code>
 * or in 
 * <code>AbstractFramework.getServices()</code>.
 * @throws CCAException if <code>ComponentID</code> is invalid
 */
::std::string
ccaffeine::ComponentID_impl::getInstanceName () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID.getInstanceName)

  return oid->getInstanceName();

  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID.getInstanceName)
}

/**
 * Returns a framework specific serialization of the ComponentID.
 * @throws CCAException if <code>ComponentID</code> is
 * invalid.
 */
::std::string
ccaffeine::ComponentID_impl::getSerialization () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID.getSerialization)

  return oid->getSerialization();

  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID.getSerialization)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._misc)
// Put miscellaneous code here
::ccaffeine::ComponentID 
ccaffeine::ComponentID_impl::babelWrap( ::ccafeopq::ComponentID_shared kernel)
{
  ::ccaffeine::ComponentID cid = ::ccaffeine::ComponentID::_create();
  ::ccafeopq::ComponentID_shared * oid_addr;
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

sidl::array< ::gov::cca::ComponentID >
ccaffeine::ComponentID_impl::convertToSidlArray( 
		::std::vector< ::ccafeopq::ComponentID_shared > &val )
{
  size_t len = val.size();
  sidl::array< ::gov::cca::ComponentID > myarray = 
	  sidl::array< ::gov::cca::ComponentID >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    ::gov::cca::ComponentID ncid = babelWrap(val[i]);
    ASET(ncid);
  }
  return myarray;
}


// DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._misc)

