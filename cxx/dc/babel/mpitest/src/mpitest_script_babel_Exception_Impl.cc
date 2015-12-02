// 
// File:          mpitest_script_babel_Exception_Impl.cc
// Symbol:        mpitest_script_babel.Exception-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for mpitest_script_babel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_Exception_Impl.hh"

// DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._includes)

// user-defined constructor.
void mpitest_script_babel::Exception_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._ctor)
  myType = gov::cca::CCAExceptionType_Nonstandard;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._ctor)
}

// user-defined destructor.
void mpitest_script_babel::Exception_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._dtor)
}

// static class initializer.
void mpitest_script_babel::Exception_impl::_load() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._load)
  // Insert-Code-Here {mpitest_script_babel.Exception._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * Method:  setType[]
 */
void
mpitest_script_babel::Exception_impl::setType (
  /* in */ ::gov::cca::CCAExceptionType t ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception.setType)
  myType = t;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception.setType)
}

/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
mpitest_script_babel::Exception_impl::getCCAExceptionType ()
throw () 

{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception.getCCAExceptionType)
  return myType;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception.getCCAExceptionType)
}


// DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._misc)

