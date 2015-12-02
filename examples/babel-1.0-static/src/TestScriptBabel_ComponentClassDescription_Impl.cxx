// 
// File:          TestScriptBabel_ComponentClassDescription_Impl.cxx
// Symbol:        TestScriptBabel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "TestScriptBabel_ComponentClassDescription_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_RuntimeException_hxx
#include "sidl_RuntimeException.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._includes)

#define WHINE(s) \
gov::cca::CCAException gex; \
 TestScriptBabel::Exception ex = TestScriptBabel::Exception::_create(); \
 ex.setNote(s); \
 gex = ex; \
 throw gex


// DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
TestScriptBabel::ComponentClassDescription_impl::ComponentClassDescription_impl(
  ) : StubBase(reinterpret_cast< 
  void*>(::TestScriptBabel::ComponentClassDescription::_wrapObj(
  reinterpret_cast< void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._ctor2)
  // Insert-Code-Here {TestScriptBabel.ComponentClassDescription._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._ctor2)
}

// user defined constructor
void TestScriptBabel::ComponentClassDescription_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._ctor)
}

// user defined destructor
void TestScriptBabel::ComponentClassDescription_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._dtor)
}

// static class initializer
void TestScriptBabel::ComponentClassDescription_impl::_load() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._load)
  // Insert-Code-Here {TestScriptBabel.ComponentClassDescription._load} (class initialization)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
TestScriptBabel::ComponentClassDescription_impl::initialize_impl (
  /* in */const ::std::string& className,
  /* in */const ::std::string& classAlias ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription.initialize)
  cName = className;
  cAlias = classAlias;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription.initialize)
}

/**
 *  
 * Returns the class name provided in 
 * <code>BuilderService.createInstance()</code>
 * or in
 * <code>AbstractFramework.getServices()</code>.
 * <p>
 * Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
 */
::std::string
TestScriptBabel::ComponentClassDescription_impl::getComponentClassName_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription.getComponentClassName)
  return cName;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription.getComponentClassName)
}


// DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._misc)

