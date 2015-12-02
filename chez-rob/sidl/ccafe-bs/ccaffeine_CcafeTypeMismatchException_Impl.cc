// 
// File:          ccaffeine_CcafeTypeMismatchException_Impl.cc
// Symbol:        ccaffeine.CcafeTypeMismatchException-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:14 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for ccaffeine.CcafeTypeMismatchException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_CcafeTypeMismatchException_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._includes)

// user defined constructor
void ccaffeine::CcafeTypeMismatchException_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._ctor)
}

// user defined destructor
void ccaffeine::CcafeTypeMismatchException_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
// referred to by:
//    gov.cca.Type

/**
 * @return the enumerated Type of the value actually found. 
 */
gov::cca::Type__enum
ccaffeine::CcafeTypeMismatchException_impl::getActualType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException.getActualType)
  return actual;
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException.getActualType)
}

// referred to by:
//    gov.cca.Type

/**
 * @return the enumerated value Type sought. 
 */
gov::cca::Type__enum
ccaffeine::CcafeTypeMismatchException_impl::getRequestedType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException.getRequestedType)
  return requested;
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException.getRequestedType)
}

// referred to by:
//    gov.cca.Type
void
ccaffeine::CcafeTypeMismatchException_impl::initialize (
  /*in*/ gov::cca::Type__enum requested,
  /*in*/ gov::cca::Type__enum actual ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException.initialize)
  this->requested = requested;
  this->actual = actual;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException.initialize)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException._misc)

  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMismatchException.create)
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMismatchException.create)
