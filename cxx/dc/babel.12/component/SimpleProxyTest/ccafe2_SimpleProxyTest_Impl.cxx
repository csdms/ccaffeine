// 
// File:          ccafe2_SimpleProxyTest_Impl.cc
// Symbol:        ccafe2.SimpleProxyTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe2.SimpleProxyTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe2_SimpleProxyTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._includes)
#include <iostream>
#include <cstdio>
#include "ccaffeine_ports_BuilderService.hxx"
void
ccafe2::SimpleProxyTest_impl::whine(const std::string &c)
{
	std::cerr<< "ERR: ccafe2::SimpleProxyTest: " << c << std::endl;
}

//#include "ccaffeine_ports_ServiceProvider.hh"
//#include "ccaffeine_ports_ServiceRegistry.hh"
// DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._includes)

// user-defined constructor.
void ccafe2::SimpleProxyTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._ctor)
  // add construction details here
  numtests = 0;
  numgos = 0;
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._ctor)
}

// user-defined destructor.
void ccafe2::SimpleProxyTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._dtor)
}

// static class initializer.
void ccafe2::SimpleProxyTest_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._load)
  // Insert-Code-Here {ccafe2.SimpleProxyTest._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
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
ccafe2::SimpleProxyTest_impl::setServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest.setServices)
	svc = services;
	gov::cca::TypeMap tm;
	gov::cca::ports::GoPort gp = *this;
	svc.addProvidesPort(gp,"go","gov.cca.ports.GoPort",tm);
	gov::cca::ComponentRelease cr = *this;
	svc.registerForRelease(cr);
	svc.registerUsesPort("bs","gov.cca.ports.BuilderService",tm);
	gov::cca::Port p = svc.getPort("bs");
	if (p._is_nil()) {
		numgos = 10; // never do anything else.
		whine("no BuilderService connected in setServices");
	}
	bs = ::babel_cast<gov::cca::ports::BuilderService> (p); // CAST
	if (bs._is_nil()) {
		numgos = 10; // never do anything else.
		whine("invalid BuilderService connected in go.");
	}
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest.setServices)
}

/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccafe2::SimpleProxyTest_impl::go ()
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest.go)
// all this logic can be managed in ways other than by
// numgos. using numgos for first testing.
	switch (numgos) {
	case 0:
		return go1();
	case 1:
		return go2();
	case 2:
		return go3();
	case 3:
		return go4();
	default:
		return 0; // not reached
	}
		
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest.go)
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
ccafe2::SimpleProxyTest_impl::releaseServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest.releaseServices)
  // insert implementation here
	// svc.unregisterUsesPort("sr");
	svc.releasePort("bs");
	svc.unregisterUsesPort("bs");
	svc.removeProvidesPort("go");
  // DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest.releaseServices)
}


// DO-NOT-DELETE splicer.begin(ccafe2.SimpleProxyTest._misc)
/*
		0 == hasn't done anything.
		1 == created components and connected them
		2 == created proxy and reconnected to it.
		3 == disconnected proxy.
*/
int32_t
ccafe2::SimpleProxyTest_impl::go1()
throw () 
{
	// 1 == created components and connected them
	if (numgos == 0) {
		numgos++;
		gov::cca::TypeMap tm;
		gov::cca::ComponentID sc1 = 
			bs.createInstance("sc1","ccafe1.StarterComponent",tm);
		gov::cca::ComponentID p2 = 
			bs.createInstance("p2","ccafe0.PrinterComponent",tm);
		gov::cca::ConnectionID sc1_output_p2_string =
			bs.connect(sc1,"output",p2,"string");
	}
	return 0;
}
int32_t
ccafe2::SimpleProxyTest_impl::go2()
throw () 
{
	// 2 == created proxy and reconnected to it.
	if (numgos == 1) {
		numgos++;
		gov::cca::TypeMap tm;
// for this bit, close your eyes. This is the bit not covered in cca standards.
		ccaffeine::ports::BuilderService cpbs = 
                   ::babel_cast<ccaffeine::ports::BuilderService> (bs); //CAST
		// if needed, cpbs.appendRepositoryPath(nameofdotccafile);
		cpbs.loadComponentClass("ccafe0.SCPProxy", true, false);
// ok now look again.
		gov::cca::ComponentID proxy = 
			bs.createInstance("scpProxy1","ccafe0.SCPProxy",tm);
		gov::cca::ComponentID sc1 = bs.getComponentID("sc1");
		gov::cca::ComponentID p2 = bs.getComponentID("p2");

		gov::cca::ConnectionID old = 
			findConnectionID(sc1,"output",p2,"string");
		if (old._is_nil()) { return -1; /* what the heck? */ }
		bs.disconnect(old,0.0);

		gov::cca::ConnectionID sc1_output_scpProxy1_input =
			bs.connect(sc1,"output",proxy,"input");
		gov::cca::ConnectionID scpProxy1_output_p2_input =
			bs.connect(proxy,"output",p2,"string");
	}
	return 0;
}

int32_t
ccafe2::SimpleProxyTest_impl::go3()
throw () 
{
	 // 3 == disconnected proxy.
	if (numgos == 2) {
		numgos++;
		gov::cca::TypeMap tm;
		gov::cca::ComponentID sc1 = bs.getComponentID("sc1");
		gov::cca::ComponentID p2 = bs.getComponentID("p2");
		gov::cca::ComponentID proxy = bs.getComponentID("scpProxy1");

		gov::cca::ConnectionID old1 = 
			findConnectionID(sc1, "output", proxy, "input");
		gov::cca::ConnectionID old2 =
			findConnectionID(proxy, "output", p2, "string");

		if (old1._is_nil() || old2._is_nil()) { return -1; /* what the heck? */ }
		bs.disconnect(old1,0.0);
		bs.disconnect(old2,0.0);
		gov::cca::ConnectionID sc1_output_p2_string =
			bs.connect(sc1,"output",p2,"string");
	}
	return 0;
}

int32_t
ccafe2::SimpleProxyTest_impl::go4()
throw () 
{
	 // 4 == reconnected proxy.
	if (numgos == 3) {
		numgos--;
		gov::cca::TypeMap tm;
		gov::cca::ComponentID proxy = bs.getComponentID("scpProxy1");
		gov::cca::ComponentID sc1 = bs.getComponentID("sc1");
		gov::cca::ComponentID p2 = bs.getComponentID("p2");

		gov::cca::ConnectionID old = 
			findConnectionID(sc1,"output",p2,"string");
		if (old._is_nil()) { return -1; /* what the heck? */ }
		bs.disconnect(old,0.0);

		gov::cca::ConnectionID sc1_output_scpProxy1_input =
			bs.connect(sc1,"output",proxy,"input");
		gov::cca::ConnectionID scpProxy1_output_p2_input =
			bs.connect(proxy,"output",p2,"string");
	}
	return 0;
}

gov::cca::ConnectionID 
ccafe2::SimpleProxyTest_impl::findConnectionID(gov::cca::ComponentID user, const std::string & uport, gov::cca::ComponentID provider, const std::string & pport)
{
	::sidl::array< ::gov::cca::ComponentID> pair = 
		::sidl::array< ::gov::cca::ComponentID >::create1d(2);
	pair.set(0,user);
	pair.set(1,provider);
	::sidl::array< ::gov::cca::ConnectionID> possibles =
		bs.getConnectionIDs(pair);
	for (int i = possibles.lower(0); i <= possibles.upper(0); i++) 
	{
		::gov::cca::ConnectionID connid = possibles[i];
		std::string upname = connid.getUserPortName();
		std::string ppname = connid.getProviderPortName();
		if ( upname == uport && ppname == pport ) {
			return connid;
		}
	}
	::gov::cca::ConnectionID noconn;
	return noconn;
	
}
// DO-NOT-DELETE splicer.end(ccafe2.SimpleProxyTest._misc)

