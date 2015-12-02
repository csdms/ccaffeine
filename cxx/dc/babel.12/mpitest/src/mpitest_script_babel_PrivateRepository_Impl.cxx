// 
// File:          mpitest_script_babel_PrivateRepository_Impl.cxx
// Symbol:        mpitest.script.babel.PrivateRepository-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for mpitest.script.babel.PrivateRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_PrivateRepository_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Component_hxx
#include "gov_cca_Component.hxx"
#endif
#ifndef included_gov_cca_ComponentClassDescription_hxx
#include "gov_cca_ComponentClassDescription.hxx"
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
#line 36 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._includes)
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "mpitest_script_babel.hxx"
#include "mpitest_script_babel.PrivateRepository._includes.guts.hh" // INC
// DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._includes)
#line 43 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
mpitest::script::babel::PrivateRepository_impl::PrivateRepository_impl() : 
  StubBase(reinterpret_cast< 
  void*>(::mpitest::script::babel::PrivateRepository::_wrapObj(this)),false) ,
  _wrapped(true){ 
#line 47 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._ctor2)
  // Insert-Code-Here {mpitest.script.babel.PrivateRepository._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._ctor2)
#line 54 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

// user defined constructor
void mpitest::script::babel::PrivateRepository_impl::_ctor() {
#line 54 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._ctor)
// #include "mpitest_script_babel.PrivateRepository._ctor.guts.hh" // INC
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._ctor)
#line 63 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

// user defined destructor
void mpitest::script::babel::PrivateRepository_impl::_dtor() {
#line 61 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._dtor)
#line 72 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

// static class initializer
void mpitest::script::babel::PrivateRepository_impl::_load() {
#line 68 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._load)
  // Insert-Code-Here {mpitest.script.babel.PrivateRepository._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._load)
#line 81 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  addDescription[]
 */
void
mpitest::script::babel::PrivateRepository_impl::addDescription_impl (
  /* in */const ::std::string& className,
  /* in */const ::std::string& classAlias ) 
{
#line 84 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository.addDescription)
	mpitest::script::babel::ComponentClassDescription cccd;
	cccd = mpitest::script::babel::ComponentClassDescription::_create();
	cccd.initialize(className, classAlias);
	gov::cca::ComponentClassDescription gcccd = cccd;
	descriptions.push_back(gcccd);
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository.addDescription)
#line 103 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

/**
 * Method:  initialize[]
 */
void
mpitest::script::babel::PrivateRepository_impl::initialize_impl (
  /* in */const ::std::string& className,
  /* in */const ::std::string& classAlias )
{
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository.initialize)
 #include "mpitest_script_babel.PrivateRepository._ctor.guts.hh" // INC
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository.initialize)
}

/**
 *  
 * Collect the currently obtainable class name strings from
 * factories known to the builder and the from the
 * already instantiated components.
 * @return The list of class description, which may be empty, that are
 * known a priori to contain valid values for the className
 * argument of createInstance. 
 * @throws CCAException in the event of error.
 */
::sidl::array< ::gov::cca::ComponentClassDescription>
mpitest::script::babel::PrivateRepository_impl::getAvailableComponentClasses_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
#line 110 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository.getAvailableComponentClasses)
	// this code is the same regardless of the components named
	// in the input bld file.

	size_t nd = descriptions.size();
	::sidl::array< ::gov::cca::ComponentClassDescription> descArray  =
	::sidl::array< ::gov::cca::ComponentClassDescription>::create1d(nd);
	for (size_t i = 0; i < nd; i++) {
		descArray.set(i, descriptions[i]);
	}
	return descArray;

  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository.getAvailableComponentClasses)
#line 137 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

/**
 *  the component instance returned is nil if the name is unknown
 * to the factory. The component is raw: it has been constructed
 * but not initialized via setServices.
 */
::gov::cca::Component
mpitest::script::babel::PrivateRepository_impl::createComponentInstance_impl (
  /* in */const ::std::string& className ) 
{
#line 134 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository.createComponentInstance)
#include "mpitest_script_babel.PrivateRepository.createComponentInstance.guts.hh" //INC
  gov::cca::Component dummy;
  return dummy;
  // the wrangler that handles all factories is supposed to 
  // deal with the nil and maybe convert it to an exception.
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository.createComponentInstance)
#line 157 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}

/**
 *  reclaim any resources the factory may have associated with
 * the port it is using. This will occur after the
 * normal component shutdown  (ala componentrelease) is finished. 
 */
void
mpitest::script::babel::PrivateRepository_impl::destroyComponentInstance_impl (
  /* in */const ::std::string& className,
  /* in */::gov::cca::Component c ) 
{
#line 153 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository.destroyComponentInstance)
  // do nothing
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository.destroyComponentInstance)
#line 174 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"
}


#line 159 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_PrivateRepository_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.PrivateRepository._misc)
#if 0
  ::gov::cca::TypeMap props;
  return self.createComponentInstance(className, props);
#endif
// DO-NOT-DELETE splicer.end(mpitest.script.babel.PrivateRepository._misc)
#line 185 "src/mpitest_script_babel_PrivateRepository_Impl.cxx"

