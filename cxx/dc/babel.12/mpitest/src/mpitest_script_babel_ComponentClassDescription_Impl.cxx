// 
// File:          mpitest_script_babel_ComponentClassDescription_Impl.cxx
// Symbol:        mpitest.script.babel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for mpitest.script.babel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_ComponentClassDescription_Impl.hxx"

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
#line 30 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._includes)

#define WHINE(s) \
gov::cca::CCAException gex; \
 mpitest::script::babel::Exception ex = mpitest::script::babel::Exception::_create(); \
 ex.setNote(s); \
 gex = ex; \
 throw gex


// DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._includes)
#line 43 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
mpitest::script::babel::ComponentClassDescription_impl::ComponentClassDescription_impl() : StubBase(reinterpret_cast< void*>(::mpitest::script::babel::ComponentClassDescription::_wrapObj(this)),false) , _wrapped(true){ 
#line 44 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._ctor2)
  // Insert-Code-Here {mpitest.script.babel.ComponentClassDescription._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._ctor2)
#line 51 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
}

// user defined constructor
void mpitest::script::babel::ComponentClassDescription_impl::_ctor() {
#line 51 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._ctor)
#line 60 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
}

// user defined destructor
void mpitest::script::babel::ComponentClassDescription_impl::_dtor() {
#line 58 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._dtor)
#line 69 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
}

// static class initializer
void mpitest::script::babel::ComponentClassDescription_impl::_load() {
#line 65 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._load)
  // Insert-Code-Here {mpitest.script.babel.ComponentClassDescription._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._load)
#line 78 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
mpitest::script::babel::ComponentClassDescription_impl::initialize_impl (
  /* in */const ::std::string& className,
  /* in */const ::std::string& classAlias ) 
{
#line 81 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription.initialize)
  cName = className;
  cAlias = classAlias;
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription.initialize)
#line 97 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
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
mpitest::script::babel::ComponentClassDescription_impl::getComponentClassName_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
#line 103 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription.getComponentClassName)
  return cName;
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription.getComponentClassName)
#line 120 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
}


#line 109 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.ComponentClassDescription._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(mpitest.script.babel.ComponentClassDescription._misc)
#line 128 "src/mpitest_script_babel_ComponentClassDescription_Impl.cxx"

