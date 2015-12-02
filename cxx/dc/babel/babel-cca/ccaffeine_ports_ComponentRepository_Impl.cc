// 
// File:          ccaffeine_ports_ComponentRepository_Impl.cc
// Symbol:        ccaffeine.ports.ComponentRepository-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ComponentRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ComponentRepository_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._includes)

// user defined constructor
void ccaffeine::ports::ComponentRepository_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._ctor)
}

// user defined destructor
void ccaffeine::ports::ComponentRepository_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
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
ccaffeine::ports::ComponentRepository_impl::getAvailableComponentClasses () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository.getAvailableComponentClasses)
  // insert implementation here
  ::sidl::array< ::gov::cca::ComponentClassDescription> x;
  return x; // we don't have a way to query babel and answer this yet.
	// FIXME getAvailableComponentClasses
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository.getAvailableComponentClasses)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._misc)

