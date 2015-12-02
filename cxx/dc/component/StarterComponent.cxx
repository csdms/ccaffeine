
#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include "dc/component/StarterComponent.h"
#include <stdio.h>

#ifndef lint
namespace {
char id[] =
"$Id: StarterComponent.cxx,v 1.17 2003/10/07 08:04:17 baallan Exp $";
} ENDSEMI
#endif

StarterComponent::StarterComponent(){ myCore = 0; }
StarterComponent::~StarterComponent(){ myCore = 0; }

void StarterComponent::setServices(classic::gov::cca::Services *cc) {
  if(!cc) {
    return;
  }
  myCore = cc;

  classic::gov::cca::PortInfo* pinfo = 0;
  pinfo = myCore->createPortInfo("out0", "StringConsumerPort",0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;
  pinfo = myCore->createPortInfo("go_port", "classic::gov::cca::GoPort",0);
  myCore->addProvidesPort(this, pinfo);
  pinfo = 0;
}

int StarterComponent::go(){

  classic::gov::cca::Port * port= 0;
  port= myCore->getPort("out0");

  if(port == 0) { // didn't get the port for some reason ...
    fprintf(stderr, "StarterComponent::go: couldn't acquire GoPort\n");
    return -1;
  }
  classic::gov::cca::StringConsumerPort * out;
  out = dynamic_cast <classic::gov::cca::StringConsumerPort *> (port);
  if(out == 0) {
    fprintf(stderr, "StarterComponent::go: cast to classic::gov::cca::StringConsumerPort *"
	    " failed \n");
    return -1;
    }
    char* str = "Foobar! from StarterComponent.";
    out->setString(str);
    return 0;
}


