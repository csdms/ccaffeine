// 
// File:          ccafe0_PrinterComponent_Impl.cc
// Symbol:        ccafe0.PrinterComponent-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe0.PrinterComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe0_PrinterComponent_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._includes)

// user defined constructor
void ccafe0::PrinterComponent_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._ctor)

  IO_dn1("PrinterComponent is now constructed\n");
 

  // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._ctor)
}

// user defined destructor
void ccafe0::PrinterComponent_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Receive a string from another component.   
 */
void
ccafe0::PrinterComponent_impl::setString (
  /*in*/ const ::std::string& s ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent.setString)

  fprintf(stdout, "%s\n", s.c_str());

  // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent.setString)
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
ccafe0::PrinterComponent_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent.setServices)

  fprintf(stderr, "%s: setServices called\n", __FILE__);
  svc = services;
  if(svc._not_nil()) {
    IO_dn1("Services not nil");
    // here we define tm. it should be left as is (nil) or
    // initialized from svc.createTypeMap. It should
    // NOT be initialized from ccaffeine::TypeMap.
    gov::cca::TypeMap tm;
    ccafe3::StringConsumerPort sc = self;
    gov::cca::Port p = sc;
    svc.addProvidesPort(p, 
		    std::string("string"), 
		    std::string("ccafe3.StringConsumerPort"), 
			tm);
  }

  // DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe0.PrinterComponent._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe0.PrinterComponent._misc)

