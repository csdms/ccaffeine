// 
// File:          ccaffeine_CCAException_Impl.cc
// Symbol:        ccaffeine.CCAException-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.CCAException
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_CCAException_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CCAException._includes)

// user defined constructor
void ccaffeine::CCAException_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CCAException._ctor)
}

// user defined destructor
void ccaffeine::CCAException_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CCAException._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
ccaffeine::CCAException_impl::getCCAExceptionType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException.getCCAExceptionType)
  return e;
  // DO-NOT-DELETE splicer.end(ccaffeine.CCAException.getCCAExceptionType)
}

/**
 * Method:  setCCAExceptionType[]
 */
void
ccaffeine::CCAException_impl::setCCAExceptionType (
  /*in*/ ::gov::cca::CCAExceptionType et ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CCAException.setCCAExceptionType)
  this->e = et;
  // DO-NOT-DELETE splicer.end(ccaffeine.CCAException.setCCAExceptionType)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CCAException._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CCAException._misc)

