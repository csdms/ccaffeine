// 
// File:          ccafe_eg_PortTranslatorStarter_Impl.cc
// Symbol:        ccafe_eg.PortTranslatorStarter-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe_eg.PortTranslatorStarter
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe_eg_PortTranslatorStarter_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._includes)

#include "dc/babel/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hh"
#include "gov_cca_ports_GoPort.hh"
#include "util/IO.h"
#include "dc/babel/babel-cca/server/ccaffeine_ports_PortTranslator.hh"
// Classic includes:
#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include "parameters/parametersStar.h"
#include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._includes)

// user defined constructor
void ccafe_eg::PortTranslatorStarter_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._ctor)

  dynTestDone = false;

  // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._ctor)
}

// user defined destructor
void ccafe_eg::PortTranslatorStarter_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._dtor)
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
ccafe_eg::PortTranslatorStarter_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter.go)


   gov::cca::Port outPrt = svc.getPort("babelOut");
  // = operator does a cast ...
  if(outPrt._not_nil()) {
    ccafe3::StringConsumerPort sc = outPrt; 
    sc.setString("Hello Babel World");
    svc.releasePort("babelOut");
  }

  outPrt = svc.getPort("classicOut");
  if(outPrt._not_nil()) {
    ccaffeine::ports::PortTranslator pt = outPrt; // cast
    classic::gov::cca::Port * p = 
      (classic::gov::cca::Port * )pt.getClassicPort();
    if(p == NULL) {
      fprintf(stderr, "Classic port is null, returning");
      return -1;
    }
    classic::gov::cca::StringConsumerPort * scp = 
      dynamic_cast< classic::gov::cca::StringConsumerPort * >(p);
    if(scp == NULL) {
      fprintf(stderr, "Couldn't cast the port to a"
	      " classic::gov::cca::StringConsumerPort\n");
      return -1;
    }
    scp->setString("Hello Classic World");
    svc.releasePort("classicOut");
  }  
  
  return 0;
 

  // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter.go)
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
ccafe_eg::PortTranslatorStarter_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter.setServices)

  svc = services;

  try {
  
    /** Check to see if we are alive or dead. */
    if(services._not_nil()) { 
      gov::cca::TypeMap tm = svc.createTypeMap(); // nil TypeMap
      gov::cca::ports::GoPort gp = self;
      svc.addProvidesPort(gp, std::string("go"), 
			  std::string("gov.cca.ports.GoPort"), tm);

      // We register for a plain old StringConsumerPort, this is a
      // Classic port that will (hopefully) be connected to us.
      svc.registerUsesPort(std::string("classicOut"), 
			   std::string("StringConsumerPort"), tm);

      // We register this guy in the normal way for the Babel religion.
      svc.registerUsesPort(std::string("babelOut"), 
			   std::string("ccafe3.StringConsumerPort"), tm);
      // Now for parameters.  We do the full enchalada here, dynamic
      // parameters included.  Dynamic parameters call back on this
      // class to tell the component that the parameters have changed.
      // This is appropriately harder to accomplish than simple static
      // parameters.  Note that static parameters will *change*
      // dynamically when changed in the GUI, they just won't notify
      // you of the change, at the time the change happens.

      // Here we fish out the Service provided by Ccaffeine to do
      // dynamic parameters.
      svc.registerUsesPort("classicParam", 
			   "gov.cca.ParameterPortFactoryService", tm);

      // Since it is a Service, we can get it right away.
      gov::cca::Port p = svc.getPort("classicParam");

      // Since it is a classic service it comes in a PortTranslator
      // package, which we must cast down from gov::cca::Port, using
      // (sigh) the "=" operator.
      ccaffeine::ports::PortTranslator portX = p; //cast

      // Since I almost never make mistakes, but I hear others do, it
      // is good to check to see that the cast succeeded.
      if(portX._not_nil()) {
	

	// Here we use the getClassicPort() method on PortTranslator
	// that must always be casted blindly to a
	// classic::gov::cca::Port* and absolutely nothing else.
	void *vp4cp;
	vp4cp = portX.getClassicPort();
	if (vp4cp == 0) {
	  fprintf(stderr, "Translator: :-( portX.getClassicPort returned null. ugh!\n");
	  return;
	}
	classic::gov::cca::Port * cp = 
	  static_cast< classic::gov::cca::Port * >(vp4cp);
	if(cp == 0) { // icky.
	  fprintf(stderr, ":-( the static_cast from void to classic port failed!\n");
	  return;
	}

	// Now we do the dynamic_cast down to the specific
	// classic::gov::cca::Port: ConfigurableParameterFactory that
	// will help us do dynamic parameters.
	ConfigurableParameterFactory *cpf = 
	  dynamic_cast<ConfigurableParameterFactory *>(cp);
	if(cpf == 0) { // icky.
	  fprintf(stderr, 
						":-( the dynamic_cast from classic port to ConfigurableParameterFactory failed!\n");
	  return;
	}
	
	// Now we get the parameters set up in another routine.
	pp = setupParameters(cpf);

	// Now we begin the process of adding a classic port to this
	// component: the parameter port that GUI users can click on
	// and configure.

	// First we *must* get it into the type that the
	// PortTranslator is expecting: cast it to a
	// classic::gov::cca::Port*.
	classic::gov::cca::Port * clscp = 
	  dynamic_cast< classic::gov::cca::Port * >(pp);
	if(clscp == NULL) {
	  fprintf(stderr, "Something went wrong with the ParameterPort "
		  "returned from setupParameters\n");
	}

	// Next pass it to PortTranslator by createFromClassic(void*)
	void * vp = static_cast< void * >(clscp);	 
	ccaffeine::ports::PortTranslator provideX = 
	  ccaffeine::ports::PortTranslator::createFromClassic(vp);

	// Add the configure port that we want to provide.
	svc.addProvidesPort(provideX, "configure", "ParameterPort", tm);

	// Let go of the ParameterPortFactoryService we got previously.
	svc.releasePort("classicParam");
	svc.unregisterUsesPort("classicParam");

      }
    }

  } catch(std::exception& e) {
    fprintf(stderr, "Exception caught: %s\n", e.what());
  }

  // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._misc)

/** Handle the dynamic parameter port.  This just shows it can be
    done. */
bool 
ccafe_eg::PortTranslatorStarter_impl::updateParameterPort(ConfigurableParameterPort *opp)  {
  if (!(pp == opp)) {
    return false;
  }
  if (!dynTestDone) {
    pp->addRequest(utest);
    dynTestDone = true;
    return true;
  }
  return false;
}

/** Setup the parameters for the Parameter Port, only a little of this
    is for the dynamic parameters */
ConfigurableParameterPort *
ccafe_eg::PortTranslatorStarter_impl::setupParameters(ConfigurableParameterFactory *cpf){
  ConfigurableParameterPort * pp = cpf->createConfigurableParameterPort();

  // Setup for dynamic parameters
  ParameterGetListener *pgl;
  pgl = dynamic_cast<ParameterGetListener *>(this);
  pp->setUpdater(pgl);
  // End setup for dynamic parameters

  prefix = new StringParameter("prefix",
    "The time stamper suffixes time strings with the zone","Color of Pill to Swallow","Green Pill");
  neo = new BoolParameter("neo","pointless checkbutton test","There is no spoon",false);
  utest = new BoolParameter("utest","this tests the updateParameterPort","update called successfully",TRUE);
  dtest = new DoubleParameter("dtest","pointless double test","double value",42.0,-100.0,100.0);
  anything = new StringParameter("anything","allow any input","free form string","there is no spoon");

  prefix->addChoice("Red Pill");
  prefix->addChoice("Green Pill");
  prefix->addChoice("White Ones Mother Gives You");
  prefix->addChoice("None");

  pp->setBatchTitle("PortTranslatorStarter Configuration");
  pp->setGroupName("The Matrix has You");
  pp->addRequest(prefix);
  pp->addRequest(neo);
  pp->setGroupName("Answer to the Universe");
  pp->addRequest(dtest);
  pp->addRequest(anything);
  return pp;
}

// DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._misc)

