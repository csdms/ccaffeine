
#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include "dc/component/ComplicatedStarterComponent.h"
#include <stdio.h>
#include <cstdlib>

#ifndef lint
namespace {
char id[] =
"$Id: ComplicatedStarterComponent.cxx,v 1.7 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI
#endif
ComplicatedStarterComponent::ComplicatedStarterComponent(){ myCore = 0; }
ComplicatedStarterComponent::~ComplicatedStarterComponent(){ myCore = 0; }

void ComplicatedStarterComponent::setServices(classic::gov::cca::Services *cc) {
  if(!cc) {
    return;
  }
  myCore = cc;

  // Contact the PrintfService
  classic::gov::cca::PortInfo* pinfo = cc->createPortInfo("pSvc", "gov.cca.JPrintfService", 0);
  cc->registerUsesPort(pinfo);
  pinfo = 0;
  classic::gov::cca::Port *dp = cc->getPort("pSvc");
  if(dp == 0) {
    cc->addProvidesPort(this, cc->createPortInfo("DEAD=NoPrintf", "classic::gov::cca::GoPort", 0));
    ::printf("!!! No PrintfService available from framework.");
    return;
  }

  pfp = dynamic_cast<classic::gov::cca::JPrintfPort*>(dp);
  if(pfp == 0) {
    cc->addProvidesPort(this, cc->createPortInfo("DEAD=NoPrintf", "classic::gov::cca::GoPort", 0));
    ::printf("!!! No PrintfService available from framework.");
    return;
  }

  pinfo = myCore->createPortInfo("out0", "StringConsumerPort",0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;
  pinfo = myCore->createPortInfo("go_port", "classic::gov::cca::GoPort",0);
  myCore->addProvidesPort(this, pinfo);
  pinfo = 0;
}

int ComplicatedStarterComponent::go(){

  classic::gov::cca::Port * port= 0;
  port= myCore->getPort("out0");
// hacks BAA to debug...
  if (pfp && port == 0) {
    char tmps[40];
    sprintf(tmps,"%p",out);
    pfp->en("ComplicatedStarterComponent::go(): port out0 not apparently connected!");
    pfp->en("ComplicatedStarterComponent::go(): for grins we'll cast it anyway.");
  }
  classic::gov::cca::StringConsumerPort * out;
  out = dynamic_cast <classic::gov::cca::StringConsumerPort *> (port);
  if(out == 0) {
    if (pfp) {
      pfp->en("ComplicatedStarterComponent::go(): uses port out0 not castable to correct type!");
    }
    return -1;
  }
  classic::gov::cca::ComponentID *mycid = myCore->getComponentID();
  std::string mess = "Foobar! from ";
  char * myname = mycid->toString();
  mess += myname;
  free(myname);
  out->setString(mess.c_str());
  myCore->releasePort("out0");
  delete mycid;
  return 0;
}


