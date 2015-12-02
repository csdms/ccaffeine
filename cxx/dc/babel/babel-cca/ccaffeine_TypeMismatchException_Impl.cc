// 
// File:          ccaffeine_TypeMismatchException_Impl.cc
// Symbol:        ccaffeine.TypeMismatchException-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.TypeMismatchException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_TypeMismatchException_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._includes)

// user defined constructor
void ccaffeine::TypeMismatchException_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._ctor)
}

// user defined destructor
void ccaffeine::TypeMismatchException_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
ccaffeine::TypeMismatchException_impl::getCCAExceptionType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException.getCCAExceptionType)
  return gov::cca::CCAExceptionType_Nonstandard;
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException.getCCAExceptionType)
}

/**
 * Method:  getRequestedType[]
 */
::gov::cca::Type
ccaffeine::TypeMismatchException_impl::getRequestedType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException.getRequestedType)
  // insert implementation here
  return rType;
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException.getRequestedType)
}

/**
 * Method:  getActualType[]
 */
::gov::cca::Type
ccaffeine::TypeMismatchException_impl::getActualType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException.getActualType)
  // insert implementation here
  return aType;
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException.getActualType)
}

/**
 * Method:  initialize[]
 */
void
ccaffeine::TypeMismatchException_impl::initializeTypes(
  /*in*/ ::gov::cca::Type requestedType,
  /*in*/ ::gov::cca::Type actualType ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException.initializeTypes)
	aType = actualType;
	rType = requestedType;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException.initializeTypes)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMismatchException._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMismatchException._misc)

