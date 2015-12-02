#include <cca.h>
#include "ports/TimeProducerPort.h"
#include "port/portInterfaces.h"
#include "Timer.h"
#include <cstring>

#ifndef lint
namespace {
char idFile[]= 
"$Id: Timer.cxx,v 1.16 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI
#endif

#include <time.h>

void Timer::setServices(classic::gov::cca::Services *svc){
  if(!svc) {
    return;
  }
  myCore = svc;
  myCore->addProvidesPort(dynamic_cast<classic::gov::cca::TimeProducerPort*>(this),
    myCore->createPortInfo("time_port", "TimeProducerPort", 0));
}

/*CFREE*/ char* Timer::getTime() {
  time_t t = ::time(&t);
  char* tmp = ::ctime(&t);
  char* d = strdup(tmp);
  return d;
}
