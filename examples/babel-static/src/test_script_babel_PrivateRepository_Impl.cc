// 
// File:          test_script_babel_PrivateRepository_Impl.cc
// Symbol:        test_script_babel.PrivateRepository-v0.0
// Symbol Type:   class
// Babel Version: 0.10.0
// Description:   Server-side implementation for test_script_babel.PrivateRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.0
// 
#include "test_script_babel_PrivateRepository_Impl.hh"

// DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._includes)
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "test_script_babel.hh"
#include "test_script_babel.PrivateRepository._includes.guts.hh" // INC
// DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._includes)

// user defined constructor
void test_script_babel::PrivateRepository_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._ctor)
#include "test_script_babel.PrivateRepository._ctor.guts.hh" // INC
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._ctor)
}

// user defined destructor
void test_script_babel::PrivateRepository_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._dtor)
}


// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  addDescription[]
 */
void
test_script_babel::PrivateRepository_impl::addDescription (
  /*in*/ const ::std::string& className,
  /*in*/ const ::std::string& classAlias ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository.addDescription)
	test_script_babel::ComponentClassDescription cccd;
	cccd = test_script_babel::ComponentClassDescription::_create();
	cccd.initialize(className, classAlias);
	gov::cca::ComponentClassDescription gcccd = cccd;
	descriptions.push_back(gcccd);
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository.addDescription)
}

/**
 *  Collect the currently obtainable class name strings from
 *  factories known to the builder and the from the
 *  already instantiated components.
 *  @return The list of class description, which may be empty, that are
 *   known a priori to contain valid values for the className
 *  argument of createInstance. 
 *  @throws CCAException in the event of error.
 */
::sidl::array< ::gov::cca::ComponentClassDescription>
test_script_babel::PrivateRepository_impl::getAvailableComponentClasses () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository.getAvailableComponentClasses)
	// this code is the same regardless of the components named
	// in the input bld file.

	size_t nd = descriptions.size();
	::sidl::array< ::gov::cca::ComponentClassDescription> descArray  =
	::sidl::array< ::gov::cca::ComponentClassDescription>::create1d(nd);
	for (size_t i = 0; i < nd; i++) {
		descArray.set(i, descriptions[i]);
	}
	return descArray;

  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository.getAvailableComponentClasses)
}

/**
 * the component instance returned is nil if the name is unknown
 * to the factory. The component is raw: it has been constructed
 * but not initialized via setServices.
 */
::gov::cca::Component
test_script_babel::PrivateRepository_impl::createComponentInstance (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository.createComponentInstance)
#include "test_script_babel.PrivateRepository.createComponentInstance.guts.hh" //INC
  gov::cca::Component dummy;
  return dummy;
  // the wrangler that handles all factories is supposed to 
  // deal with the nil and maybe convert it to an exception.
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository.createComponentInstance)
}

/**
 * reclaim any resources the factory may have associated with
 * the port it is using. This will occur after the
 * normal component shutdown  (ala componentrelease) is finished. 
 */
void
test_script_babel::PrivateRepository_impl::destroyComponentInstance (
  /*in*/ const ::std::string& className,
  /*in*/ ::gov::cca::Component c ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository.destroyComponentInstance)
  // do nothing
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository.destroyComponentInstance)
}


// DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._misc)
#if 0
  ::gov::cca::TypeMap props;
  return self.createComponentInstance(className, props);
#endif
// DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._misc)

