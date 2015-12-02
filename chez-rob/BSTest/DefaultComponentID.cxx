#ifndef lint
static char id[] = 
"$Id: DefaultComponentID.cxx,v 1.1 2001/07/25 22:48:37 rob Exp $";
#endif

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cca.h>
#include "DefaultComponentID.h"


DefaultComponentID::
~DefaultComponentID() {
  free(fullyQualName);
  free(instanceName);
}

DefaultComponentID::
DefaultComponentID(char* fullyQualName, char* instanceName) {
  this->fullyQualName = strdup(fullyQualName);
  this->instanceName = strdup(instanceName);
}

CFREE char* DefaultComponentID::
toString() {
  return strdup(instanceName);
}
