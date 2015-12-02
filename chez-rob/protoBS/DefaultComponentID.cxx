#ifndef lint
static char id[] = 
"$Id: DefaultComponentID.cxx,v 1.4 2001/08/02 19:30:33 rob Exp $";
#endif

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cca.h>
#include "DefaultComponentID.h"


DefaultComponentID::
~DefaultComponentID() {
  free(instanceName);
}

DefaultComponentID::
DefaultComponentID(char* instanceName) {
  this->instanceName = strdup(instanceName);
}

char* DefaultComponentID::
toString() {
  return instanceName;
}
