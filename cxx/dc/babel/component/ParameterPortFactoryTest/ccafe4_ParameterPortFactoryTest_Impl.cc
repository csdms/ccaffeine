// 
// File:          ccafe4_ParameterPortFactoryTest_Impl.cc
// Symbol:        ccafe4.ParameterPortFactoryTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe4.ParameterPortFactoryTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe4_ParameterPortFactoryTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._includes)

#include <iostream>

// DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._includes)

// user defined constructor
void ccafe4::ParameterPortFactoryTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._ctor)
  
  numtests = 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._ctor)
}

// user defined destructor
void ccafe4::ParameterPortFactoryTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._dtor)
  
  svc = 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._dtor)
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
ccafe4::ParameterPortFactoryTest_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest.go)
  
  if (svc._is_nil()) {
	  std::cerr <<  "ccafe4::ParameterPortFactoryTest_impl::go: called without Services svc set." << std::endl;
	  return 1;
  }
  char buf[40];
  numtests++;
  sprintf(buf,"%d",numtests);

  gov::cca::TypeMap tm = svc.createTypeMap();
  if (tm._is_nil()) {
    std::cerr <<  "ccafe4::ParameterPortFactoryTest_impl::go: svc.createTypeMap failed." << std::endl;
    return -1;
  }

  pplist.push_back(tm);
  std::string pname = "PP_";
  pname += buf;

  ppf = svc.getPort("ppf");
  if (ppf._is_nil()) {
    std::cerr <<  "ccafe4::ParameterPortFactoryTest_impl::go: called without ppf connected." << std::endl;
    return -1;
  }
  std::cout << "BPPFTEST:  got port ppf" << std::endl;
  ppf.initParameterData(tm, pname);
  std::cout << "BPPFTEST:  init'd tm." << std::endl;
  ::std::string title = "Test PPF for port ";
  title += pname;
  ppf.setBatchTitle(tm, title);
  std::cout << "BPPFTEST:  title set." << std::endl;
  ppf.addRequestBoolean(tm,"noName","var to test if default group gets used","anon group",true);

  std::cout << "BPPFTEST:  bool defined." << std::endl;
  ppf.setGroupName(tm,"Named Set1");
  ppf.addRequestInt(tm,"iVar","a ranged test integer","int test", 5, 0 ,10);

  std::cout << "BPPFTEST:  set1.ivar defined." << std::endl;
#define FULLTEST 1
#if FULLTEST
  ppf.addRequestLong(tm,"jVar","a deranged test long","long test", -50, 0 , -100);

  std::cout << "BPPFTEST:  defining set2." << std::endl;
  ppf.setGroupName(tm,"Named Set2");
  ppf.addRequestDouble(tm,"dVar","a ranged test double","double test", -50, 0 , -100);
  ppf.addRequestFloat(tm,"fVar","a ranged test float","float test", 50, -1000 , 1000);

  std::cout << "BPPFTEST:  defining set3." << std::endl;
  ppf.setGroupName(tm,"Named Set3");
  
  ppf.addRequestString(tm,"sVar","a free test string","string any test", "some value");

  ppf.addRequestString(tm,"sList","a choice test string","string list test", "some value");
  ppf.addRequestStringChoice(tm,"sList","choice 1");
  ppf.addRequestStringChoice(tm,"sList","choice 3");
  ppf.addRequestStringChoice(tm,"sList","choice 2");
  std::cout << "BPPFTEST:  did data adds" << std::endl;

  std::cout << "BPPFTEST:  defining psl." << std::endl;
  // we might want to respond to changes.
  gov::cca::ports::ParameterSetListener psl = self;
  ppf.registerUpdatedListener(tm, psl);

  std::cout << "BPPFTEST:  defining pgl." << std::endl;
  // we might want to change the params before sharing them
  gov::cca::ports::ParameterGetListener pgl = self;
  ppf.registerUpdater(tm, pgl); 
  std::cout << "BPPFTEST:  did listener adds" << std::endl;
#endif // FULLTEST
  // publish
  ppf.addParameterPort(tm, svc);
  std::cout << "BPPFTEST:  published port" << std::endl;

  svc.releasePort("ppf");
  std::cout << "BPPFTEST:  released ppf." << std::endl;
  ppf = 0;
  std::cout << "BPPFTEST:  assigned ppf 0." << std::endl;

  pp = svc.getPort(pname);
  if (pp._is_nil()) {
    std::cout << "BPPFTEST: getport(" << pname << ") failed." << std::endl;
  }
  std::cout << "BPPFTEST:   got port pp." << std::endl;
  gov::cca::TypeMap ftm = pp.readConfigurationMap();
  std::cout << "BPPFTEST:   read config map from pp." << std::endl;
  std::string svar = ftm.getString("sVar","failed svar fetch");
  std::cout << "BPPFTEST:  sVar = " << svar << std::endl;

  return 0;

  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest.go)
}

/**
 * The component wishing to be told after a parameter is changed
 * implements this function.
 * @param portName the name of the port (typemap) on which the
 * value was set.
 * @param fieldName the name of the value in the typemap.
 */
void
ccafe4::ParameterPortFactoryTest_impl::updatedParameterValue (
  /*in*/ const ::std::string& portName,
  /*in*/ const ::std::string& fieldName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest.updatedParameterValue)
	std::cout << "ccafe4::ParameterPortFactoryTest_impl::updatedParameterValue(" <<
		portName << ", " << fieldName << ") called." << std::endl;
  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest.updatedParameterValue)
}

/**
 * Inform the listener that someone is about to fetch their 
 * typemap. The return should be true if the listener
 * has changed the ParameterPort definitions.
 */
bool
ccafe4::ParameterPortFactoryTest_impl::updateParameterPort (
  /*in*/ const ::std::string& portName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest.updateParameterPort)
  
	std::cout << "ccafe4::ParameterPortFactoryTest_impl::updateParameterPort(" <<
		portName << ") called." << std::endl;
	return false;

  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest.updateParameterPort)
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
ccafe4::ParameterPortFactoryTest_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest.setServices)

  try {
    IO_dn1("ccafe4::ParameterPortFactoryTest_impl::setServices entry");
    if (svc._not_nil() && services._is_nil() ) {
      IO_dn1("ccafe4::ParameterPortFactoryTest_impl::setServices shutdown");
      ppf = svc.getPort("ppf");
      if ( ppf._not_nil()) {
        for (size_t i = 0; i < pplist.size(); i++)
        {
          ::gov::cca::TypeMap tm = pplist[i];
          ppf.removeParameterPort(tm, svc);
        }
        svc.releasePort("ppf");
      }
      svc.unregisterUsesPort("ppf");
      svc.removeProvidesPort("go");
      svc = 0; 
      return;
    }

    if (svc._not_nil() && services._not_nil() ) {
      return; // fwk is hosed. ignore it.
    }

    svc = services;

    if(svc._not_nil()) {
  
      gov::cca::TypeMap tm = svc.createTypeMap();
      gov::cca::ports::GoPort gp = self;
      svc.addProvidesPort(gp, std::string("go"), 
			  std::string("gov.cca.ports.GoPort"), tm);
      svc.registerUsesPort(std::string("ppf"), 
			   std::string("gov.cca.ports.ParameterPortFactory"), tm);

    } else {

      IO_dn1(":-( Services Object on init call is nil passed to "
	     "ccafe4::ParameterPortFactoryTest_impl::setServices");
    }
  
  } catch(std::exception& e) {
    IO_dn2("exception caught: %s", e.what());
  }

  // DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe4.ParameterPortFactoryTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe4.ParameterPortFactoryTest._misc)

