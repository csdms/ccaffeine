#include <stdio.h>
#include <cca.h>
#include <stdPorts.h>
#include "ports/StringConsumerPort.h"
#include "dc/component/BSTest.h"
#include "dc/export/ccafeopq.hh"

#ifndef lint
namespace {
char id[] =
"$Id: BSTest.cxx,v 1.9 2005/08/12 03:08:42 baallan Exp $";
} ENDSEMI
#endif

using std::string;

BSTest::BSTest(){ myCore = 0; numtests = 0; out = 0; }
BSTest::~BSTest(){ myCore = 0; out = 0; }

void BSTest::setServices(classic::gov::cca::Services *cc) {
	if (myCore != 0 && cc == 0) {
		myCore->unregisterUsesPort("pSvc");
		myCore->unregisterUsesPort("bs");
		myCore->removeProvidesPort("go");
		myCore = 0;
		return;
	}
	if (myCore != 0 && cc != 0)
	{
		return; // fwk is hosed. ignore it.
	}
  myCore = cc;

  // Contact the PrintfService
  classic::gov::cca::PortInfo* pinfo = 0;
  cc->registerUsesPort("pSvc", "gov.cca.JPrintfService");
  pinfo = 0;
  classic::gov::cca::Port* rp = cc->getPort("pSvc");
	if (rp == 0) {
    cc->addProvidesPort(this, cc->createPortInfo("DEAD=NoJPrintf", "classic::gov::cca::GoPort", 0));
    ::printf("!!! No JPrintfService available from framework.");
    return;
  }
  pfp = dynamic_cast<classic::gov::cca::JPrintfPort*>(rp);
  if(pfp == 0) {
    cc->addProvidesPort(this, cc->createPortInfo("DEAD=NoJPrintf-cast", "classic::gov::cca::GoPort", 0));
    ::printf("!!! Pretend JPrintfService available from framework.");
    return;
  }

  pinfo = myCore->createPortInfo("bs", "::classic::hack::BuilderService",0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;
  pinfo = myCore->createPortInfo("starter", "classic::gov::cca::GoPort",0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;
  pinfo = myCore->createPortInfo("go", "classic::gov::cca::GoPort",0);
  myCore->addProvidesPort(this, pinfo);
  pinfo = 0;
}

int BSTest::go()
{
	if (myCore ==0) { return -2; }
  char buf[40];
  sprintf(buf,"%d",numtests);
  numtests++;
  classic::gov::cca::Port * port= 0;
  port= myCore->getPort("bs");
  if (pfp && port == 0) {
    char tmps[40];
    sprintf(tmps,"%p",out);
    pfp->en("BSTest::go(): port bs not apparently connected!");
		return -1;
  }
  ::ccafeopq::BuilderService * bs;
  bs = dynamic_cast < ::ccafeopq::BuilderService *> (port);
  if(bs == 0) {
    if (pfp) {
      pfp->en("BSTest::go(): uses port bs not castable to correct type!");
    }
    return -1;
  }

  classic::gov::cca::ComponentID * mycid = myCore->getComponentID();
  string myname = mycid->toString();

  ::ccafeopq::ComponentID_shared myoid = bs->getComponentID(myname);

  string siname = myname;
  siname += ".StarterComponent.";
  siname += buf;

  string piname = myname;
  piname += ".PrinterComponent.";
  piname += buf;

  ::ccafeopq::TypeMap_shared dummy;
  ::ccafeopq::ComponentID_shared sid;
  sid = bs->createInstance(siname, "ComplicatedStarterComponent",dummy);

  ::ccafeopq::ComponentID_shared pid;
  pid = bs->createInstance(piname, "ComplicatedPrinterComponent",dummy);


  // Rob additions

  std::vector< ccafeopq::ComponentID_shared > cids =
    bs->getComponentsThatUse("StringConsumerPort");
  pfp->e("\n\nBSTest components that use StringConsumerPort: ");
  int siz = cids.size();
  std::string gin;
  for(int i = 0;i < siz;i++) {
    gin = cids[i]->getInstanceName();
    pfp->e(gin.c_str());
    pfp->e(" ");
  }
  cids =
    bs->getComponentsThatProvide("StringConsumerPort");
  pfp->e("\n\nBSTest components that provide StringConsumerPort: ");
  siz = cids.size();
  for(int i = 0;i < siz;i++) {
    gin = cids[i]->getInstanceName();
    pfp->e(gin.c_str());
    pfp->e(" ");
  }
  pfp->en("");
  pfp->en("");
  // End Rob additions



  ::ccafeopq::ConnectionID_shared connid;
  connid = bs->connect(sid,"out0",pid,"printer_port" /*,dummy */);

  ::ccafeopq::ConnectionID_shared conngo;
  conngo = bs->connect(myoid,"starter",sid,"go_port" /*,dummy */);

  ::classic::gov::cca::GoPort *gp = 0;
  ::classic::gov::cca::Port *p = 0;
  pfp->en("Here goes nothing!");
  p = myCore->getPort("starter");
  if (p == 0) {
    pfp->en("ERROR: starter port not connected.");
    return 0;
  }
  gp = dynamic_cast< classic::gov::cca::GoPort *>(p);
  if (gp == 0) {
    pfp->en("ERROR: starter port not castable to classic GoPort.");
  } else {
    gp->go();
  }


  gp->go();

  myCore->releasePort("starter");

  bs->disconnect(conngo,0);

  myCore->releasePort("bs");

  return 0;
}


