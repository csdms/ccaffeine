#ifndef lint
static char id[] =
  "$Id: GoThreadComponent.cxx,v 1.1 2003/10/18 01:25:09 rob Exp $";
#endif

#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include "dc/component/GoThreadComponent.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
/*
 * In this component we must access the state of the GoThreadComponent
 * to figure out whether the Go is running or not.
 */
GoThreadComponent::GoPort_go::GoPort_go(GoThreadComponent * myGoThreadComponent) {
  this->myGoThreadComponent = myGoThreadComponent;
}

int 
GoThreadComponent::GoPort_go::go() {
  myGoThreadComponent->isRunning = 1;
  // buf at least char[26] long.
  char * buf = (char *)malloc(512*sizeof(char));
  if(buf == NULL) {
    fprintf(stderr, ":-( Couldn't get 512 bytes of memory, " 
	    "what is this machine a Commodore 64?\n");
    perror("GoThreadComponent::GoPort_go::go");
    return -1;
  }
  while(myGoThreadComponent->isRunning) {
    time_t t = time(0);
    char * s = ctime_r(&t,buf);

    classic::gov::cca::Services * svc = myGoThreadComponent->svc;
    classic::gov::cca::Port * port = svc->getPort("Output");
    if(port == 0) { // didn't get the port for some reason ...
      fprintf(stderr, "GoThreadComponent::go: couldn't acquire GoPort\n");
      return -1;
    }
    classic::gov::cca::StringConsumerPort * out;
    out = dynamic_cast <classic::gov::cca::StringConsumerPort *> (port);
    if(out == 0) {
      fprintf(stderr, "GoThreadComponent::go: cast to"
	      " classic::gov::cca::StringConsumerPort *"
	      " failed \n");
      return -1;
    }
    out->setString(s);
    svc->releasePort("Output");
    sleep(1);
  }
  free(buf);
  return 0;
}

/*
 * In this component we must access the state of the GoThreadComponent
 * to figure out whether the Go is running or not.
 */

GoThreadComponent::GoPort_stop::GoPort_stop(GoThreadComponent * myGoThreadComponent) {
  this->myGoThreadComponent = myGoThreadComponent;
}

/*
 * Confusingly, the go button on this port will cause the other
 * GoPort to stop.  Kind of like pushing the "start" button in
 * Windows to shutdown.
 */
int
GoThreadComponent::GoPort_stop::go() {
  myGoThreadComponent->isRunning = 0;
  return 0;
}



GoThreadComponent::GoThreadComponent(){ 
  stop = NULL;
  go = NULL;
  svc = NULL; 
}

GoThreadComponent::~GoThreadComponent(){ 
  if(go) { 
    delete go; 
    go = NULL;
  }
  if(stop) {
    delete stop;
    stop = NULL;
  }
  svc = NULL; 
}

void GoThreadComponent::setServices(classic::gov::cca::Services *cc) {
  if(!cc) {
    return;
  }
  svc = cc;

  classic::gov::cca::PortInfo* pinfo = 0;
    
  pinfo = svc->createPortInfo("Output", "StringConsumerPort", NULL);
  svc->registerUsesPort(pinfo);
  pinfo = 0;

  
  char * prop[4];
  prop[0] = "GoPort_Spawns_Thread";
  prop[1] = "true";
  prop[2] = NULL;
  prop[3] = NULL;    
  pinfo = svc->createPortInfo("Go", "classic::gov::cca::GoPort", prop);
  go = new GoPort_go(this);
  svc->addProvidesPort(go, pinfo);
  pinfo = 0;

  pinfo = svc->createPortInfo("Stop", "classic::gov::cca::GoPort", NULL);
  stop = new GoPort_stop(this);
  svc->addProvidesPort(stop, pinfo);
  pinfo = 0;
}



