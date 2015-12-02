#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include <ports/TimeProducerPort.h>
#include "parameters/parametersStar.h"
#include "dc/component/ComplicatedPrinterComponent.h"
#include "util/IO.h"

#ifndef lint
namespace {
char id[] = 
"$Id: ComplicatedPrinterComponent.cxx,v 1.5 2004/12/10 00:39:58 baallan Exp $";
} ENDSEMI
#endif

void ComplicatedPrinterComponent::setServices(classic::gov::cca::Services *cc){
  if(!cc) {
    return;
  }

  core = cc;

  // Contact the PrintfService
  classic::gov::cca::PortInfo* pinfo = cc->createPortInfo("pSvc", "gov.cca.JPrintfService", 0);
  cc->registerUsesPort(pinfo);
  pinfo = 0;
  // IO_dn2("here is the printf port: 0x%x", cc->getPort("pSvc"));
  classic::gov::cca::Port * dp = cc->getPort("pSvc");
  if(dp == 0) {
    pinfo = cc->createPortInfo("DEAD=NoPrintf", "Port", 0);
    cc->addProvidesPort(this, pinfo);
    pinfo = 0;
    printf("!!! No PrintfService available from framework.");
    return;
  }
  pfp = dynamic_cast<classic::gov::cca::JPrintfPort*>(dp);
  if(pfp == 0) {
    pinfo = cc->createPortInfo("DEAD=NoPrintf", "Port", 0);
    cc->addProvidesPort(this, pinfo);
    pinfo = 0;
    printf("!!! No PrintfService available from framework.");
    return;
  }

  classic::gov::cca::Port *scp;
  scp = this;
  pinfo = core->createPortInfo("printer_port", "StringConsumerPort", 0 );
  core->addProvidesPort(scp, pinfo);
  pinfo = 0;
}
   
void ComplicatedPrinterComponent::setString(const char* s){
  pfp->e("Printer says the string is: "); pfp->en(s);
}
