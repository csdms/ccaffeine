// 
// File:          ccafe4_ConnectionEventServiceTest_Impl.cc
// Symbol:        ccafe4.ConnectionEventServiceTest-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe4.ConnectionEventServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe4_ConnectionEventServiceTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._includes)

#include <iostream>

// DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._includes)

// user-defined constructor.
void ccafe4::ConnectionEventServiceTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._ctor)
  
  numtests = 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._ctor)
}

// user-defined destructor.
void ccafe4::ConnectionEventServiceTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._dtor)
  
  svc = 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._dtor)
}

// static class initializer.
void ccafe4::ConnectionEventServiceTest_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._load)
  // Insert-Code-Here {ccafe4.ConnectionEventServiceTest._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccafe4::ConnectionEventServiceTest_impl::go ()
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest.go)
  
  gov::cca::TypeMap tm = svc.createTypeMap();
  if (tm._is_nil()) {
    std::cerr <<  "ccafe4::ConnectionEventServiceTest_impl::go: svc.createTypeMap failed." << std::endl;
    return -1;
  }

	// get ces. 
	// subscribe. 
	// get builderservice
	// connect self output to input.
	// print something on output.
	// disconnect self output to input


  ces = svc.getPort("ces");
  if (ces._is_nil()) {
    std::cerr <<  "ccafe4::ConnectionEventServiceTest_impl::go: called without ces connected." << std::endl;
    return -1;
  }
  std::cout << "CESTEST:  got port ces" << std::endl;
	// subscribe. 

  svc.releasePort("ces");
  std::cout << "CESTEST:  released ces." << std::endl;
  ces = 0;
  std::cout << "CESTEST:  assigned ces 0." << std::endl;

	// connect self output to input.
	// print something on output.
	// disconnect self output to input
  return 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest.go)
}

/**
 * Starts up a component presence in the calling framework.
 * @param services the component instance's handle on the framework world.
 * Contracts concerning Svc and setServices:
 * 
 * The component interaction with the CCA framework
 * and Ports begins on the call to setServices by the framework.
 * 
 * This function is called exactly once for each instance created
 * by the framework.
 * 
 * The argument Svc will never be nil/null.
 * 
 * Those uses ports which are automatically connected by the framework
 * (so-called service-ports) may be obtained via getPort during
 * setServices.
 */
void
ccafe4::ConnectionEventServiceTest_impl::setServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest.setServices)

    svc = services;

    gov::cca::TypeMap tm = svc.createTypeMap();
    gov::cca::ports::GoPort gp = self;
    svc.addProvidesPort(gp, std::string("go"), 
	  std::string("gov.cca.ports.GoPort"), tm);

    svc.registerUsesPort(std::string("ces"), 
	   std::string("gov.cca.ports.ConnectionEventService"), tm);
    svc.registerUsesPort(std::string("bs"), 
	   std::string("gov.cca.ports.BuilderService"), tm);
	// need the loader interface here too eventually.


  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest.setServices)
}

/**
 * Shuts down a component presence in the calling framework.
 * @param Svc the component instance's handle on the framework world.
 * Contracts concerning Svc and setServices:
 * 
 * This function is called exactly once for each callback registered
 * through Services.
 * 
 * The argument Svc will never be nil/null.
 * The argument Svc will always be the same as that received in
 * setServices.
 * 
 * During this call the component should release any interfaces
 * acquired by getPort().
 * 
 * During this call the component should reset to nil any stored
 * reference to Svc.
 * 
 * After this call, the component instance will be removed from the
 * framework. If the component instance was created by the
 * framework, it will be destroyed, not recycled, The behavior of
 * any port references obtained from this component instance and
 * stored elsewhere becomes undefined.
 * 
 * Notes for the component implementor:
 * 1) The component writer may perform blocking activities
 * within releaseServices, such as waiting for remote computations
 * to shutdown.
 * 2) It is good practice during releaseServices for the component
 * writer to remove or unregister all the ports it defined.
 */
void
ccafe4::ConnectionEventServiceTest_impl::releaseServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest.releaseServices)
    if (svc._not_nil() && services._is_nil() ) {
      IO_dn1("ccafe4::ConnectionEventServiceTest_impl::setServices shutdown");
      ces = svc.getPort("ces");
      if ( ces._not_nil()) {
	// unsubscribes here?
        svc.releasePort("ces"); 
      }
      svc.unregisterUsesPort("bs");
      svc.unregisterUsesPort("ces");
      svc.removeProvidesPort("go");
      svc = 0; 
      return;
    }
  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest.releaseServices)
}

/**
 * Called on all listeners when a connection is made or broken. 
 */
void
ccafe4::ConnectionEventServiceTest_impl::connectionActivity (
  /* in */ ::gov::cca::ports::ConnectionEvent ce ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest.connectionActivity)
	gov::cca::TypeMap tm = ce.getPortInfo();
	gov::cca::ports::EventType cet = ce.getEventType();
	std::string portName = tm.getString("cca.portName","noportname");
	std::string portType = tm.getString("cca.portType","noporttype");
	std::cout << "ccafe4::ConnectionEventServiceTest_impl::connectionActivity called on port " <<
		portName << " of type " << portType << std::endl;
	std::cout << "with event type " << cet << std::endl;

  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest.connectionActivity)
}

/**
 * Receive a string from another component.   
 */
void
ccafe4::ConnectionEventServiceTest_impl::setString (
  /* in */ const ::std::string& s ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest.setString)
	std::cout << "ccafe4::ConnectionEventServiceTest_impl::setString called with " << s << std::endl;
  // DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest.setString)
}


// DO-NOT-DELETE splicer.begin(ccafe4.ConnectionEventServiceTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe4.ConnectionEventServiceTest._misc)

