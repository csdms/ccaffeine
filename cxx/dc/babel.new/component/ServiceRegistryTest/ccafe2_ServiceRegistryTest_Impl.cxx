// 
// File:          ccafe2_ServiceRegistryTest_Impl.cc
// Symbol:        ccafe2.ServiceRegistryTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe2.ServiceRegistryTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe2_ServiceRegistryTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._includes)
#include <iostream>
#include <cstdio>
#include "ccafe3_StringConsumerPort.hxx"
void
ccafe2::ServiceRegistryTest_impl::whine(const std::string &c)
{
	std::cerr<< "ERR: ccafe2::ServiceRegistryTest: " << c << std::endl;
}

//#include "ccaffeine_ports_ServiceProvider.hh"
//#include "ccaffeine_ports_ServiceRegistry.hh"
// DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._includes)

// user defined constructor
void ccafe2::ServiceRegistryTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._ctor)
  // add construction details here
  numtests = 0;
  numgos = 0;
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._ctor)
}

// user defined destructor
void ccafe2::ServiceRegistryTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._dtor)
}

void
ccafe2::ServiceRegistryTest_impl::releaseServices (
  /*in*/ ::gov::cca::Services Svc ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.releaseServices)
  // insert implementation here
	std::map< std::string, std::string >::const_iterator pi;
	std::vector< std::string> names;
	for (pi = pnames.begin(); pi != pnames.end(); pi++) {
		names.push_back(pi->first);
	}
	for (size_t i = 0, n = names.size(); i < n ; i++ ) {
		std::cerr << "ccafe2::ServiceRegistryTest_impl::releaseServices: port " << names[i] << " still not destroyed." << std::endl;
		destroyService(names[i]);
	}
	svc.unregisterUsesPort("sr");
	svc.removeProvidesPort("go");
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.releaseServices)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Receive a string from another component.   
 */
void
ccafe2::ServiceRegistryTest_impl::setString (
  /*in*/ const ::std::string& s ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.setString)
	std::cout << "ccafe2::ServiceRegistryTest::setString(" << 
		s << ")" << std::endl;
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.setString)
}

/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccafe2::ServiceRegistryTest_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.go)
	// 1 on first entry
	// get BS and create two starters, which will
	// autoconnect to our singleton port
	// then remove service
	// then add multiple server
	// then create two starters
	// which will autoconnect to us.
	// All the if nil checking should go away with
	// exceptions thrown instead.
	if (numgos == 0) {
		numgos++;
		gov::cca::TypeMap tm;
		svc.registerUsesPort("bs","gov.cca.ports.BuilderService",tm);
		gov::cca::Port p = svc.getPort("bs");
		if (p._is_nil()) {
		  whine("no BuilderService connected in go");
		}
		gov::cca::ports::BuilderService bs = 
                   ::babel_cast<gov::cca::ports::BuilderService> (p); // CAST
		if (bs._is_nil()) {
		  whine("invalid BuilderService connected in go.");
		}
		// port output on both of these should get connected
		// to our singleton port. 
		// these will appear on FRAMEWORK rather than on us.
		bs.createInstance("s1","ccafe1.StarterComponent",tm);
		bs.createInstance("s2","ccafe1.StarterComponent",tm);
		p = svc.getPort("sr");
		if (p._is_nil()) {
		  whine("no ServiceRegistry connected in go");
		}
		gov::cca::ports::ServiceRegistry sr = 
                   ::babel_cast<gov::cca::ports::ServiceRegistry> (p); //  CAST
		if (sr._is_nil()) {
		  whine("invalid ServiceRegistry connected in go.");
		}
		// remove singleton
		sr.removeService("ccafe3.StringConsumerPort");
		gov::cca::ports::ServiceProvider pp = *this;
		sr.addService( "ccafe3.StringConsumerPort", pp);
		bs.createInstance("s3", "ccafe1.StarterComponent", tm);
		bs.createInstance("s4", "ccafe1.StarterComponent", tm);
		svc.releasePort("bs");
		svc.releasePort("sr");
	}
	// 2 On second entry disconnect everything
	// and stop all serving of things.
	if (numgos == 1) {
		numgos++;
		gov::cca::Port p = svc.getPort("sr");
		p = svc.getPort("sr");
		if (p._is_nil()) {
		  whine("no ServiceRegistry connected in go 2");
		}
		gov::cca::ports::ServiceRegistry sr = 
                    ::babel_cast<gov::cca::ports::ServiceRegistry> (p); //  CAST
		if (sr._is_nil()) {
		  whine("invalid ServiceRegistry connected in go 2.");
		}
		sr.removeService("ccafe3.StringConsumerPort");
		svc.releasePort("sr");
	}
	return 0;
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.go)
}

/**
 * Starts up a component presence in the calling framework.
 * @param Svc the component instance's handle on the framework world.
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
ccafe2::ServiceRegistryTest_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.setServices)
  svc = services;
  gov::cca::TypeMap tm;
  gov::cca::ports::GoPort gp = *this;
  svc.addProvidesPort(gp,"go","gov.cca.ports.GoPort",tm);
  svc.registerUsesPort("sr","gov.cca.ports.ServiceRegistry",tm);
  gov::cca::Port p = svc.getPort("sr");
  if (p._is_nil()) {
	  whine("no ServiceRegistry connected in setServices");
  }
  gov::cca::ports::ServiceRegistry sr = ::babel_cast< gov::cca::ports::ServiceRegistry >(p); // down cast
  if (sr._is_nil()) {
	  whine("invalid ServiceRegistry connected in setServices.");
  }
  ccafe3::StringConsumerPort sp = *this;
  sr.addSingletonService("ccafe3.StringConsumerPort", sp);
  svc.releasePort("sr");
  gov::cca::ComponentRelease cr = *this;
  svc.registerForRelease(cr);
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.setServices)
}

/**
 * Create the Port for the Service, informing the framework through
 * "addProvidesPort()" on the originating component.
 * @return the name of the port created.
 */
::std::string
ccafe2::ServiceRegistryTest_impl::createService (
  /*in*/ const ::std::string& portType ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.createService)
  numtests++;
  char buf[40]; sprintf(buf,"%d",numtests);
  std::string result = "scp_"; result += buf;
  gov::cca::TypeMap tm;
  ccafe3::StringConsumerPort sp = *this;
  svc.addProvidesPort(sp,result,"ccafe3.StringConsumerPort", tm);
  pnames[result] = result;
  return result;
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.createService)
}

/**
 * Informs the originating component that the instance of the
 * provided service is no longer needed. The ServiceProvider
 * can now safely removePort on the named port.
 */
void
ccafe2::ServiceRegistryTest_impl::destroyService (
  /*in*/ const ::std::string& portName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest.destroyService)
  svc.removeProvidesPort(portName);
  pnames.erase(portName);
  // DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest.destroyService)
}


// DO-NOT-DELETE splicer.begin(ccafe2.ServiceRegistryTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe2.ServiceRegistryTest._misc)

