// 
// File:          ccaffeine_CcafeConnectionID_Impl.cc
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
#include "ccaffeine_CcafeConnectionID_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._includes)

// user defined constructor
void ccaffeine::CcafeConnectionID_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._ctor)
}

// user defined destructor
void ccaffeine::CcafeConnectionID_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get the providing component (callee) ID.
 * @return the ComponentID of the component that has 
 * provided the Port for this connection. 
 * @throws a CCAException if the underlying connection is no longer valid.
 */
gov::cca::ComponentID
ccaffeine::CcafeConnectionID_impl::getProvider () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID.getProvider)

  return provider;


  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID.getProvider)
}

// referred to by:
//    gov.cca.CCAException

/**
 * Get the port name in the providing component of this connection.
 * @return the instance name of the provided Port.
 * @throws CCAException if the underlying connection is no longer valid.
 */
std::string
ccaffeine::CcafeConnectionID_impl::getProviderPortName () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID.getProviderPortName)

  return providerName;


  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID.getProviderPortName)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get the using component (caller) ID.
 * @return the ComponentID of the component that is using the provided Port.
 * @throws a CCAException if the underlying connection is no longer valid.
 */
gov::cca::ComponentID
ccaffeine::CcafeConnectionID_impl::getUser () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID.getUser)

  return user;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID.getUser)
}

// referred to by:
//    gov.cca.CCAException

/**
 * Get the port name in the using component of this connection.
 * @return the instance name of the Port registered for use in 
 * this connection.
 * @throws CCAException if the underlying connection is no longer valid.
 */
std::string
ccaffeine::CcafeConnectionID_impl::getUserPortName () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID.getUserPortName)

  return userName;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID.getUserPortName)
}

// referred to by:
//    gov.cca.ComponentID

/**
 * init one of these 
 */
void
ccaffeine::CcafeConnectionID_impl::initialize (
  /*in*/ gov::cca::ComponentID provider,
  /*in*/ std::string providerName,
  /*in*/ gov::cca::ComponentID user,
  /*in*/ std::string username ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID.initialize)

  this->provider = provider;
  this->user = user;
  this->providerName = providerName;
  this->userName = userName;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID.initialize)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeConnectionID._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeConnectionID._misc)

