// 
// File:          test_script_babel_Exception_Impl.cc
// Symbol:        test_script_babel.Exception-v0.0
// Symbol Type:   class
// Babel Version: 0.10.0
// Description:   Server-side implementation for test_script_babel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.0
// 
#include "test_script_babel_Exception_Impl.hh"

// DO-NOT-DELETE splicer.begin(test_script_babel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test_script_babel.Exception._includes)

// user defined constructor
void test_script_babel::Exception_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.Exception._ctor)
  myType = gov::cca::CCAExceptionType_Nonstandard;
  // DO-NOT-DELETE splicer.end(test_script_babel.Exception._ctor)
}

// user defined destructor
void test_script_babel::Exception_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.Exception._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.Exception._dtor)
}


// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  setType[]
 */
void
test_script_babel::Exception_impl::setType (
  /*in*/ ::gov::cca::CCAExceptionType t ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.Exception.setType)
  myType = t;
  // DO-NOT-DELETE splicer.end(test_script_babel.Exception.setType)
}

/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
test_script_babel::Exception_impl::getCCAExceptionType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(test_script_babel.Exception.getCCAExceptionType)
  return myType;
  // DO-NOT-DELETE splicer.end(test_script_babel.Exception.getCCAExceptionType)
}


// DO-NOT-DELETE splicer.begin(test_script_babel.Exception._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(test_script_babel.Exception._misc)

