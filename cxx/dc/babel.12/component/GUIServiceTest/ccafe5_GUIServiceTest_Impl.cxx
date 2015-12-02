// 
// File:          ccafe5_GUIServiceTest_Impl.cc
// Symbol:        ccafe5.GUIServiceTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe5.GUIServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe5_GUIServiceTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._includes)
#include <iostream>
#include "dc/babel.12/babel-cca/server/ccaffeine_ports_GUIService.hxx"
// DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._includes)

// user defined constructor
void ccafe5::GUIServiceTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._ctor)
}

// user defined destructor
void ccafe5::GUIServiceTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._dtor)
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
ccafe5::GUIServiceTest_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest.go)

  gov::cca::Port outPrt = svc.getPort("GUIService"); // = operator does a cast ...
  gov::cca::ComponentID cid = svc.getComponentID();
  std::string name = cid.getInstanceName();
  std::cout << "!! babel GUIServiceTest.go called on instance" << name << std::endl;
  if(outPrt._not_nil()) {
	  ::ccaffeine::ports::GUIService gs = ::babel_cast< ::ccaffeine::ports::GUIService >(outPrt);
	  if (gs._not_nil()) {
		  gs.load("gov.sandia.ccaffeine.dc.user_iface.gui.CcaffeineGUITestWidget firstArg secondArg");
	  }
    svc.releasePort("GUIService");
  } else {
	  std::cout << "!! babel GUIServiceTest.go: on instance " << name << 
		  " port GUIService is not connected apparently." << std::endl;
  }
  std::cout << "!! babel GUIServiceTest.go done." << std::endl;
  return 0;
  // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest.go)
}

/**
 * Obtain Services handle, through which the 
 * component communicates with the framework. 
 * This is the one method that every CCA Component
 * must implement. The component will be called
 * with a nil/null Services pointer when it is
 * to shut it(*this) down.
 */
void
ccafe5::GUIServiceTest_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest.setServices)

  try {
    IO_dn1("ccafe5::GUIServiceTest_impl::setServices entry");
    svc = services;
    if(svc._not_nil()) {

  
      gov::cca::TypeMap tm = svc.createTypeMap();
      gov::cca::ports::GoPort gp = (*this);
      svc.addProvidesPort(gp, std::string("go"), 
			  std::string("gov.cca.ports.GoPort"), tm);
      svc.registerUsesPort(std::string("GUIService"), 
			   std::string("ccaffeine.ports.GUIService"), tm);
    } else {
      IO_dn1(":-( Services Object is nil passed to "
	     "ccafe5::GUIServiceTest_impl::setServices");
    }
  
  } catch(std::exception& e) {
    IO_dn2("exception caught: %s", e.what());
  }

  // DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe5.GUIServiceTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe5.GUIServiceTest._misc)

