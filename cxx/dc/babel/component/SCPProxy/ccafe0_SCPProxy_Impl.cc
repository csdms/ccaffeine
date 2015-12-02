// 
// File:          ccafe0_SCPProxy_Impl.cc
// Symbol:        ccafe0.SCPProxy-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe0.SCPProxy
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe0_SCPProxy_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._includes)

// user-defined constructor.
void ccafe0::SCPProxy_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._ctor)

  IO_dn1("SCPProxy is now constructed\n");
 

  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._ctor)
}

// user-defined destructor.
void ccafe0::SCPProxy_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._dtor)
}

// static class initializer.
void ccafe0::SCPProxy_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._load)
  // Insert-Code-Here {ccafe0.SCPProxy._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._load)
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
ccafe0::SCPProxy_impl::setServices (
  /* in */ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy.setServices)

	svc = services;
	// here we define tm. it should be left as is (nil) or
	// initialized from svc.createTypeMap. It should
	// NOT be initialized from ccaffeine::TypeMap.
	gov::cca::TypeMap tm;
	ccafe3::StringConsumerPort sc = self;
	gov::cca::Port p = sc;
	svc.addProvidesPort(p, 
		    std::string("input"), 
		    std::string("ccafe3.StringConsumerPort"), 
			tm);
	svc.registerUsesPort( std::string("output"), 
		    std::string("ccafe3.StringConsumerPort"), 
			tm);

  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy.setServices)
}

/**
 * Receive a string from another component.   
 */
void
ccafe0::SCPProxy_impl::setString (
  /* in */ const ::std::string& s ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy.setString)

    gov::cca::Port p = svc.getPort("output");
    ccafe3::StringConsumerPort sc = p;
	::std::string me = svc.getComponentID().getInstanceName();
    IO_en3( "# proxy %s passing along: %s\n", me.c_str(), s.c_str());
    sc.setString(s);
    svc.releasePort("output");

  // DO-NOT-DELETE splicer.end(ccafe0.SCPProxy.setString)
}


// DO-NOT-DELETE splicer.begin(ccafe0.SCPProxy._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe0.SCPProxy._misc)

