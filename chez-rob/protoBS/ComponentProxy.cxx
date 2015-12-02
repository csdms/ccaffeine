#include <cca.h>
#include "jc++/util/jc++util.h"
#include "ComponentProxy.h"

ComponentProxy::ComponentProxy() {
  instanceName = NULL;
  svc = NULL;
}

void 
ComponentProxy::setServices(gov::cca::Services* svc) {
  this->svc = svc;
}

/** Get the Services object that has been set on this proxy, or NULL
      if it has not been set yet. */
gov::cca::Services* 
ComponentProxy::getServices() {
  return svc;
}

/** Set the instance name for this ComponentProxy. */
void 
ComponentProxy::setInstanceName(char* instanceName) {
  this->instanceName = strdup(instanceName);
}
  
/** Get the instance name for this ComponentProxy. */
CFREE char* 
ComponentProxy::getInstanceName() {
  return strdup(instanceName);
}
