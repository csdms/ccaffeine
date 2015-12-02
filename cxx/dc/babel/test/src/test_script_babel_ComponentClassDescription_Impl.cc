// 
// File:          test_script_babel_ComponentClassDescription_Impl.cc
// Symbol:        test_script_babel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for test_script_babel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "test_script_babel_ComponentClassDescription_Impl.hh"

// DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._includes)

#define WHINE(s) \
gov::cca::CCAException gex; \
 test_script_babel::Exception ex = test_script_babel::Exception::_create(); \
 ex.setNote(s); \
 gex = ex; \
 throw gex


// DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._includes)

// user-defined constructor.
void test_script_babel::ComponentClassDescription_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._ctor)
}

// user-defined destructor.
void test_script_babel::ComponentClassDescription_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._dtor)
}

// static class initializer.
void test_script_babel::ComponentClassDescription_impl::_load() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._load)
  // Insert-Code-Here {test_script_babel.ComponentClassDescription._load} (class initialization)
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * Method:  initialize[]
 */
void
test_script_babel::ComponentClassDescription_impl::initialize (
  /* in */ const ::std::string& className,
  /* in */ const ::std::string& classAlias ) 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription.initialize)
  cName = className;
  cAlias = classAlias;
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription.initialize)
}

/**
 *  Returns the class name provided in 
 *   <code>BuilderService.createInstance()</code>
 *   or in
 *   <code>AbstractFramework.getServices()</code>.
 *  <p>
 *  Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
 */
::std::string
test_script_babel::ComponentClassDescription_impl::getComponentClassName ()
throw ( 
  ::gov::cca::CCAException, 
  ::sidl::RuntimeException
)
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription.getComponentClassName)
  return cName;
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription.getComponentClassName)
}


// DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._misc)

