#ifndef lint
static char id[] = 
"$Id: DefaultBuilderService.cxx,v 1.5 2001/08/02 19:30:33 rob Exp $";
#endif

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cca.h>
#include "DefaultComponentID.h"
#include "CCAException.h"
#include "BuilderServiceTest.h"
#include "DefaultBuilderService.h"

using gov::cca::ComponentID;

DefaultBuilderService::
DefaultBuilderService(){}

DefaultBuilderService::
~DefaultBuilderService(){}


gov::cca::ComponentID* DefaultBuilderService::
createLocalInstance(char* fullyQualName, char* instanceName) 
  throw (gov::cca::CCAException) {
      
  this->fullyQualName = strdup(fullyQualName);
  this->instanceName = strdup(instanceName);

  //  fprintf(stdout, "Pretend instance created: instanceName = %s, from Component name = %s", fullyQualName, instanceName);

  return new DefaultComponentID(fullyQualName, instanceName);
}
