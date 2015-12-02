// 
// File:          ccaffeine_CcafeComponentID_Impl.cc
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
#include "ccaffeine_CcafeComponentID_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._includes)

// user defined constructor
void ccaffeine::CcafeComponentID_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._ctor)
}

// user defined destructor
void ccaffeine::CcafeComponentID_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
// referred to by:
//    gov.cca.CCAException

/**
 * Returns the instance name provided in 
 * BuilderService.createInstance()
 * or in
 * AbstractFramework.getServices().
 * @throws CCAException if ComponentID is invalid.
 */
std::string
ccaffeine::CcafeComponentID_impl::getInstanceName () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID.getInstanceName)

  return instanceName;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID.getInstanceName)
}

// referred to by:
//    gov.cca.CCAException

/**
 * Returns a framework specific serialization of the ComponentID.
 * @throws CCAException if ComponentID is invalid.
 */
std::string
ccaffeine::CcafeComponentID_impl::getSerialization () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID.getSerialization)

  return instanceName;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID.getSerialization)
}


/**
 * initialize one of these. 
 */
void
ccaffeine::CcafeComponentID_impl::initialize (
  /*in*/ std::string instanceName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID.initialize)

  this->instanceName = instanceName;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID.initialize)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeComponentID._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeComponentID._misc)

