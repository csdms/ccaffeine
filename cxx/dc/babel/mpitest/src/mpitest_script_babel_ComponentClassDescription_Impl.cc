// 
// File:          mpitest_script_babel_ComponentClassDescription_Impl.cc
// Symbol:        mpitest_script_babel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for mpitest_script_babel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_ComponentClassDescription_Impl.hh"

// DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription._includes)

#define WHINE(s) \
gov::cca::CCAException gex; \
 mpitest_script_babel::Exception ex = mpitest_script_babel::Exception::_create(); \
 ex.setNote(s); \
 gex = ex; \
 throw gex


// DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription._includes)

// user-defined constructor.
void mpitest_script_babel::ComponentClassDescription_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription._ctor)
}

// user-defined destructor.
void mpitest_script_babel::ComponentClassDescription_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription._dtor)
}

// static class initializer.
void mpitest_script_babel::ComponentClassDescription_impl::_load() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription._load)
  // Insert-Code-Here {mpitest_script_babel.ComponentClassDescription._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * Method:  initialize[]
 */
void
mpitest_script_babel::ComponentClassDescription_impl::initialize (
  /* in */ const ::std::string& className,
  /* in */ const ::std::string& classAlias ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription.initialize)
  cName = className;
  cAlias = classAlias;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription.initialize)
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
mpitest_script_babel::ComponentClassDescription_impl::getComponentClassName ()
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription.getComponentClassName)
  return cName;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription.getComponentClassName)
}


// DO-NOT-DELETE splicer.begin(mpitest_script_babel.ComponentClassDescription._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(mpitest_script_babel.ComponentClassDescription._misc)

