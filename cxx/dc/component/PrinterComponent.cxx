
/** If you are looking for the PrinterComponent that uses the
    JPrintfService then you want to look at
    ComplicatedPrinterComponent.  This one will remain simple so that
    users have a prayer of figuring out what is going on.  Also this
    is used in the tests to see if classic is working and the
    ComplicatedPrinterComponent is prone to failure because it uses
    libstd++ features that are often not found or not present. */

#include <cca.h>
#include <ports/StringConsumerPort.h>
#include "dc/component/PrinterComponent.h"
#include "util/IO.h"
#ifndef lint
namespace {
char id[] =
"$Id: PrinterComponent.cxx,v 1.22 2003/10/18 01:25:09 rob Exp $";
} ENDSEMI
#endif


void PrinterComponent::setServices(classic::gov::cca::Services *cc){
  if(!cc) {
    return;
  }
  core = cc;

  classic::gov::cca::PortInfo* pinfo = 0;
  // IO_dn2("here is the printf port: 0x%x", cc->getPort("pSvc"));
  // obviously it aint there if you don't register.

  classic::gov::cca::Port *scp;
  scp = this;
  pinfo = core->createPortInfo("printer_port", "StringConsumerPort", 0 );
  core->addProvidesPort(scp, pinfo);
  pinfo = 0;
}
   
void PrinterComponent::setString(const char* s){
  printf("Printer says the string is: %s", s); 
  fflush(stdout); // make the buffer actually write the line.
}
