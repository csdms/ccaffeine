#include <iostream>
//#include <cstdio>
#include <cca.h>
#include <stdPorts.h>
#include "GoTest.h"

#ifndef lint
namespace {
char id[] =
"$Id: GoTest.cxx,v 1.1 2004/08/12 18:28:40 baallan Exp $";
} 
#endif

using namespace std;

//////////////////////////////////////////

GoTest::GoTest(){ 
	myCore = 0; 
	cout << "!! Go:  CTOR" << endl;
}

GoTest::~GoTest(){
	myCore = 0;
	cout << "!! Go:  DTOR" << endl;
}

void
GoTest::setServices( classic::gov::cca::Services *cc) 
{
	cout << "!! Go:  SET_SERVICES" << endl;
	if (cc == 0)
	{
		cout << "!! GoTest::setServices(0) called. That means shutdown." << endl;
		return;
	}
	if (myCore != 0) {
		cout << "!! GoTest::setServices() called twice. Bad!" << endl;
		return;
	}

	cout << "!! Tester Go: startup" ;
	const char * myname = cc->getComponentID()->toString();
	cout << "of instance" << myname << endl ;
	myCore = cc;

	myCore->registerUsesPort( "call_go", "classic::gov::cca::GoPort" );
	myCore->addProvidesPort(this, "go", "classic::gov::cca::GoPort" );
	cout << "!! Go:  startup done"  << endl;
}

int 
GoTest::go()
{

  const char * myname = myCore->getComponentID()->toString();
  cout << "!! " << myname << " port 'go' called." << endl;

  classic::gov::cca::GoPort *gp = 0;
  classic::gov::cca::Port *np = 0;
  np = myCore->getPort("call_go");
  if (np != 0) {
    gp = dynamic_cast< ::classic::gov::cca::GoPort *>(np);
    if (gp != 0) {
      cout << "!! " << myname << "Calling go on call_go port." << endl;
      int res = gp->go();
      cout << "!! " << myname << "Called go. received " << res << endl;
    } else {
      cout << "!! NOTE: Clasic Tester Go (" << myname 
	    << ") is not apparently connected properly its call_go port." << endl;
    } 
  
    myCore->releasePort("call_go");
  } else {
    cout << "!! NOTE: Classic Tester Go (" << myname 
	    << ") is not apparently connected on its call_go port." << endl;
  }
  cout << "!! " << myname << " port 'go' finished." << endl;
  return 0;
}

