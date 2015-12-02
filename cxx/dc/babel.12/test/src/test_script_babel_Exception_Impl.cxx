// 
// File:          test_script_babel_Exception_Impl.cxx
// Symbol:        test.script.babel.Exception-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for test.script.babel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "test_script_babel_Exception_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAExceptionType_hxx
#include "gov_cca_CCAExceptionType.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_io_Deserializer_hxx
#include "sidl_io_Deserializer.hxx"
#endif
#ifndef included_sidl_io_Serializer_hxx
#include "sidl_io_Serializer.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
#line 33 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
// DO-NOT-DELETE splicer.begin(test.script.babel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test.script.babel.Exception._includes)
#line 38 "src/test_script_babel_Exception_Impl.cxx"

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
test::script::babel::Exception_impl::Exception_impl() : 
  StubBase(reinterpret_cast< 
  void*>(::test::script::babel::Exception::_wrapObj(this)),false) ,
  _wrapped(true){ 
#line 42 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception._ctor2)
  // Insert-Code-Here {test.script.babel.Exception._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception._ctor2)
#line 49 "src/test_script_babel_Exception_Impl.cxx"
}

// user defined constructor
void test::script::babel::Exception_impl::_ctor() {
#line 49 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception._ctor)
  myType = gov::cca::CCAExceptionType_Nonstandard;
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception._ctor)
#line 58 "src/test_script_babel_Exception_Impl.cxx"
}

// user defined destructor
void test::script::babel::Exception_impl::_dtor() {
#line 56 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception._dtor)
#line 67 "src/test_script_babel_Exception_Impl.cxx"
}

// static class initializer
void test::script::babel::Exception_impl::_load() {
#line 63 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception._load)
  // Insert-Code-Here {test_script_babel.Exception._load} (class initialization)
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception._load)
#line 76 "src/test_script_babel_Exception_Impl.cxx"
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  setType[]
 */
void
test::script::babel::Exception_impl::setType_impl (
  /* in */::gov::cca::CCAExceptionType t ) 
{
#line 78 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception.setType)
  myType = t;
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception.setType)
#line 93 "src/test_script_babel_Exception_Impl.cxx"
}

/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
test::script::babel::Exception_impl::getCCAExceptionType_impl () 

{
#line 90 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.Exception.getCCAExceptionType)
  return myType;
  // DO-NOT-DELETE splicer.end(test.script.babel.Exception.getCCAExceptionType)
#line 107 "src/test_script_babel_Exception_Impl.cxx"
}


#line 96 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/test/src/test_script_babel_Exception_Impl.cxx"
// DO-NOT-DELETE splicer.begin(test.script.babel.Exception._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(test.script.babel.Exception._misc)
#line 115 "src/test_script_babel_Exception_Impl.cxx"

