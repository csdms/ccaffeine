// 
// File:          TestScriptBabel_Exception_Impl.cxx
// Symbol:        TestScriptBabel.Exception-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "TestScriptBabel_Exception_Impl.hxx"

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
// DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
TestScriptBabel::Exception_impl::Exception_impl() : StubBase(reinterpret_cast< 
  void*>(::TestScriptBabel::Exception::_wrapObj(reinterpret_cast< 
  void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._ctor2)
  // Insert-Code-Here {TestScriptBabel.Exception._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._ctor2)
}

// user defined constructor
void TestScriptBabel::Exception_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._ctor)
  myType = gov::cca::CCAExceptionType_Nonstandard;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._ctor)
}

// user defined destructor
void TestScriptBabel::Exception_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._dtor)
}

// static class initializer
void TestScriptBabel::Exception_impl::_load() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._load)
  // Insert-Code-Here {TestScriptBabel.Exception._load} (class initialization)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  setType[]
 */
void
TestScriptBabel::Exception_impl::setType_impl (
  /* in */::gov::cca::CCAExceptionType t ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception.setType)
  myType = t;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception.setType)
}

/**
 * Method:  getCCAExceptionType[]
 */
::gov::cca::CCAExceptionType
TestScriptBabel::Exception_impl::getCCAExceptionType_impl () 

{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception.getCCAExceptionType)
  return myType;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception.getCCAExceptionType)
}


// DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._misc)

