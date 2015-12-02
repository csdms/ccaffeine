// 
// File:          TestScriptBabel_PrivateRepository_Impl.cxx
// Symbol:        TestScriptBabel.PrivateRepository-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.PrivateRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "TestScriptBabel_PrivateRepository_Impl.hxx"

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
// DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._includes)
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "TestScriptBabel.hh"
#include "TestScriptBabel.PrivateRepository._includes.guts.hh" // INC
// DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
TestScriptBabel::PrivateRepository_impl::PrivateRepository_impl() : 
  StubBase(reinterpret_cast< 
  void*>(::TestScriptBabel::PrivateRepository::_wrapObj(reinterpret_cast< 
  void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._ctor2)
  // Insert-Code-Here {TestScriptBabel.PrivateRepository._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._ctor2)
}

// user defined constructor
void TestScriptBabel::PrivateRepository_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._ctor)
#include "TestScriptBabel.PrivateRepository._ctor.guts.hh" // INC
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._ctor)
}

// user defined destructor
void TestScriptBabel::PrivateRepository_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._dtor)
}

// static class initializer
void TestScriptBabel::PrivateRepository_impl::_load() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._load)
  // Insert-Code-Here {TestScriptBabel.PrivateRepository._load} (class initialization)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  addDescription[]
 */
void
TestScriptBabel::PrivateRepository_impl::addDescription_impl (
  /* in */const ::std::string& className,
  /* in */const ::std::string& classAlias ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository.addDescription)
	TestScriptBabel::ComponentClassDescription cccd;
	cccd = TestScriptBabel::ComponentClassDescription::_create();
	cccd.initialize(className, classAlias);
	gov::cca::ComponentClassDescription gcccd = cccd;
	descriptions.push_back(gcccd);
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository.addDescription)
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
TestScriptBabel::PrivateRepository_impl::getAvailableComponentClasses_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository.getAvailableComponentClasses)
	// this code is the same regardless of the components named
	// in the input bld file.

	size_t nd = descriptions.size();
	::sidl::array< ::gov::cca::ComponentClassDescription> descArray  =
	::sidl::array< ::gov::cca::ComponentClassDescription>::create1d(nd);
	for (size_t i = 0; i < nd; i++) {
		descArray.set(i, descriptions[i]);
	}
	return descArray;

  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository.getAvailableComponentClasses)
}

/**
 *  the component instance returned is nil if the name is unknown
 * to the factory. The component is raw: it has been constructed
 * but not initialized via setServices.
 */
::gov::cca::Component
TestScriptBabel::PrivateRepository_impl::createComponentInstance_impl (
  /* in */const ::std::string& className ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository.createComponentInstance)
#include "TestScriptBabel.PrivateRepository.createComponentInstance.guts.hh" //INC
  gov::cca::Component dummy;
  return dummy;
  // the wrangler that handles all factories is supposed to 
  // deal with the nil and maybe convert it to an exception.
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository.createComponentInstance)
}

/**
 *  reclaim any resources the factory may have associated with
 * the port it is using. This will occur after the
 * normal component shutdown  (ala componentrelease) is finished. 
 */
void
TestScriptBabel::PrivateRepository_impl::destroyComponentInstance_impl (
  /* in */const ::std::string& className,
  /* in */::gov::cca::Component c ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository.destroyComponentInstance)
  // do nothing
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository.destroyComponentInstance)
}


// DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._misc)
#if 0
  ::gov::cca::TypeMap props;
  return self.createComponentInstance(className, props);
#endif
// DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._misc)

