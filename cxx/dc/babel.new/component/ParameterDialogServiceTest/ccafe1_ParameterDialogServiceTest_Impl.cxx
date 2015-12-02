// 
// File:          ccafe1_ParameterDialogServiceTest_Impl.cc
// Symbol:        ccafe1.ParameterDialogServiceTest-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe1.ParameterDialogServiceTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe1_ParameterDialogServiceTest_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._includes)
// Put additional includes or other arbitrary code here...
#include <iostream>
// DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._includes)

// user defined constructor
void ccafe1::ParameterDialogServiceTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._ctor)
  numtests = 0;
  // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._ctor)
}

// user defined destructor
void ccafe1::ParameterDialogServiceTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._dtor)
  svc = 0;
  // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._dtor)
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
ccafe1::ParameterDialogServiceTest_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest.go)
  if (svc._is_nil()) {
	  std::cerr <<  "ccafe1::ParameterDialogServiceTest_impl::go: called without Services svc set." << std::endl;
	  return 1;
  }
  char buf[40];
  numtests++;
  sprintf(buf,"%d",numtests);

  gov::cca::TypeMap tm = svc.createTypeMap();
  if (tm._is_nil()) {
    std::cerr <<  "ccafe1::ParameterDialogServiceTest_impl::go: svc.createTypeMap failed." << std::endl;
    return -1;
  }

  pplist.push_back(tm);
  std::string pname = "PP_";
  pname += buf;

  pds = svc.getPort("pds");
  if (pds._is_nil()) {
    std::cerr <<  "ccafe1::ParameterDialogServiceTest_impl::go: called without pds connected." << std::endl;
    return -1;
  }
  pds.createParameterPort(tm, pname);
  ::std::string title = "Test PDS for port ";
  title += pname;
  pds.setBatchTitle(tm, title);
  pds.addRequestBoolean(tm,"noName","var to test if default group gets used","anon group",true);

  pds.setGroupName(tm,"Named Set1");
  pds.addRequestInt(tm,"iVar","a ranged test integer","int test", 5, 0 ,10);
  pds.addRequestLong(tm,"jVar","a deranged test long","long test", -50, 0 , -100);

  pds.setGroupName(tm,"Named Set2");
  pds.addRequestDouble(tm,"dVar","a ranged test double","double test", -50, 0 , -100);
  pds.addRequestFloat(tm,"fVar","a ranged test float","float test", 50, -1000 , 1000);

  pds.setGroupName(tm,"Named Set3");
  
  pds.addRequestString(tm,"sVar","a free test string","string any test", "some value");

  pds.addRequestString(tm,"sList","a choice test string","string list test", "some value");
  pds.addRequestStringChoice(tm,"sList","choice 1");
  pds.addRequestStringChoice(tm,"sList","choice 3");
  pds.addRequestStringChoice(tm,"sList","choice 2");

  pds.publishParameterPort(tm, svc);

  svc.releasePort("pds");
  pds = 0;
  return 0;

  // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest.go)
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
ccafe1::ParameterDialogServiceTest_impl::setServices (
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest.setServices)

  try {
    IO_dn1("ccafe1::ParameterDialogServiceTest_impl::setServices entry");
    if (svc._not_nil() && services._is_nil() ) {
      IO_dn1("ccafe1::ParameterDialogServiceTest_impl::setServices shutdown");
      pds = svc.getPort("pds");
      if ( pds._not_nil()) {
        for (size_t i = 0; i < pplist.size(); i++)
        {
          ::gov::cca::TypeMap tm = pplist[i];
          pds.unpublishParameterPort(tm, svc);
        }
        svc.releasePort("pds");
      }
      svc.unregisterUsesPort("pds");
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
      svc.registerUsesPort(std::string("pds"), 
			   std::string("ccaffeine.ports.ParameterDialogService"), tm);

    } else {

      IO_dn1(":-( Services Object on init call is nil passed to "
	     "ccafe1::ParameterDialogServiceTest_impl::setServices");
    }
  
  } catch(std::exception& e) {
    IO_dn2("exception caught: %s", e.what());
  }


  // DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest.setServices)
}


// DO-NOT-DELETE splicer.begin(ccafe1.ParameterDialogServiceTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe1.ParameterDialogServiceTest._misc)

