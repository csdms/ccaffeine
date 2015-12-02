// 
// File:          ccafe5_GoComponent_Impl.cc
// Symbol:        ccafe5.GoComponent-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe5.GoComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe5_GoComponent_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe5.GoComponent._includes)
#include <iostream>
// DO-NOT-DELETE splicer.end(ccafe5.GoComponent._includes)

// user defined constructor
void ccafe5::GoComponent_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.GoComponent._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccafe5.GoComponent._ctor)
}

// user defined destructor
void ccafe5::GoComponent_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.GoComponent._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe5.GoComponent._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccafe5::GoComponent_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe5.GoComponent.go)

  gov::cca::Port outPrt = svc.getPort("call_go"); // = operator does a cast ...
  gov::cca::ComponentID cid = svc.getComponentID();
  std::string name = cid.getInstanceName();
  std::cout << "!! babel GoComponent.go called on instance" << name << std::endl;
  if(outPrt._not_nil()) {
	  gov::cca::ports::GoPort gp = ::babel_cast< gov::cca::ports::GoPort >(outPrt);
	  if (gp._not_nil()) {
		  gp.go();
	  }
    svc.releasePort("call_go");
  } else {
	  std::cout << "!! babel GoComponent.go: on instance " << name << 
		  " port call_go is not connected apparently." << std::endl;
  }
  std::cout << "!! babel GoComponent.go done." << std::endl;
  return 0;
  // DO-NOT-DELETE splicer.end(ccafe5.GoComponent.go)
}

/**
 * Obtain Services handle, through which the 
 * component communicates with the framework. 
 * This is the one method that every CCA Component
 * must implement. The component will be called
 * with a nil/null Services pointer when it is
 * to shut itself down.
 */
void
ccafe5::GoComponent_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe5.GoComponent.setServices)

  try {
    IO_dn1("ccafe5::GoComponent_impl::setServices entry");
    svc = services;
    if(svc._not_nil()) {

  
      gov::cca::TypeMap tm = svc.createTypeMap();
      gov::cca::ports::GoPort gp = *this;
      svc.addProvidesPort(gp, std::string("go"), 
			  std::string("gov.cca.ports.GoPort"), tm);
      svc.registerUsesPort(std::string("call_go"), 
			   std::string("gov.cca.ports.GoPort"), tm);
    } else {
      IO_dn1(":-( Services Object is nil passed to "
	     "ccafe5::GoComponent_impl::setServices");
    }
  
  } catch(std::exception& e) {
    IO_dn2("exception caught: %s", e.what());
  }

  // DO-NOT-DELETE splicer.end(ccafe5.GoComponent.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe5.GoComponent._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe5.GoComponent._misc)

