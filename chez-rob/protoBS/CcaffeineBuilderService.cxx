#include <cca.h>
#include "jc++/util/jc++util.h"
#include "ccaFrameworkServices.h"
/** For BuilderModel: */
#include "parameters/parametersStar.h"
#include "jc++/jc++.h"
#include "dc/framework/dc_fwkStar.h"
#include "port/portInterfaces.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/Link.h"
#include "dc/user_iface/DefaultBuilderModel.h"

#include "util/freefree.h"
/** Done with BuilderModel. */

#include "CcaffeineAbstractFramework.h"

#include "CcafeCCAException.h"
#include "jc++/util/jc++util.h"
#include "ComponentProxy.h"
// this is just <getopt.h> under linux but we aren't linux always
// so include our own which is from the gnu distribution.
#include <unistd.h>
#include "gnu/getopt/getCCAFEopt.h"
/** For BuilderService... */
#include "BuilderService.h"
#include "DefaultStringList.h"
#include "CcaffeineBuilderService.h"
/** Done with BuilderService. */
#include "DefaultComponentID.h"
#include "CcafeConnection.h"

#if defined(__sun) || defined(__sgi)
#include <strings.h>
#endif // __sun

CcaffeineBuilderService::CcaffeineBuilderService(DefaultBuilderModel* bm) {
    this->bm = bm;
    connections = new jcpp::StringHash();
}
CcaffeineBuilderService::~CcaffeineBuilderService() {
  jcpp::StringEnumeration* e;
  for(e = connections->keys();e->hasMoreElements();) {
    char* key = e->nextElement();
    CcafeConnection* c = 
      dynamic_cast<CcafeConnection*>(connections->remove(key));CHECKDC(c);
    delete c;
  }
  delete e;
}


CDELETE gov::cca::StringList* 
CcaffeineBuilderService::getComponentClasses() 
  throw (gov::cca::CCAException) 
{
  int length;
  char** names = bm->getPallet(length);
  gov::cca::StringList* list = new DefaultStringList();
  for(int i = 0;i < length;i++) {
    list->append(names[i]);
  }
  return list;
}


gov::cca::ComponentID* 
CcaffeineBuilderService::createInstance(char* className, 
					char* requestedInstanceName)
  throw (gov::cca::CCAException) 
{
  char* instanceName;
  if(requestedInstanceName == NULL) {
    instanceName = bm->pullDownFromPallet(className);
  } else {
    instanceName = bm->pullDownFromPallet(className, requestedInstanceName);
  }
  if(instanceName == NULL) {
    throw new CcafeCCAException("CcaffeineBuilderService::createInstance: :-( class name: %s, does not exist!", className);
  }
  Link* l = dynamic_cast<Link*>(bm->getArena()->get(instanceName));
  CHECKDC(l);
  gov::cca::ComponentID* id = l->ci->getComponentID();
  return id;
}



void 
CcaffeineBuilderService::destroyInstance(gov::cca::ComponentID* id) 
  throw (gov::cca::CCAException) 
{
  // This is embarrassing.
  return;
}

gov::cca::ComponentID* 
CcaffeineBuilderService::getComponentID(char* name) 
  throw (gov::cca::CCAException) {
  boolean exists = false;
  gov::cca::StringList* l = getComponentInstanceNames();
  for(int i = 0;i < l->getSize();i++) {
    if(strcmp(l->get(i), name) == 0) {
      exists = true;
      break;
    }
  }
  if(exists) {
    Link* l = dynamic_cast<Link*>(bm->getArena()->get(name));
    gov::cca::ComponentID* id = l->ci->getComponentID();
    return id;
  }
  throw new CcafeCCAException("Component instance: %s does not exist in the arena", name);
}


CDELETE gov::cca::StringList* 
CcaffeineBuilderService::getContainerNames() 
{
  return new DefaultStringList();
}

CDELETE gov::cca::StringList* 
CcaffeineBuilderService::getComponentInstanceNames() 
{
  gov::cca::StringList* list = new DefaultStringList();
  jcpp::StringHash* hash = bm->getArena();
  for(jcpp::StringEnumeration* k = hash->keys();k->hasMoreElements();) {
    char* instance = k->nextElement();
    list->append(instance);
  }
  return list;
}

char* 
CcaffeineBuilderService::componentIDToName(gov::cca::ComponentID* cid) {
  char* ret = rindex(cid->toString(), '.');
  return ++ret;
}

CDELETE gov::cca::StringList* 
CcaffeineBuilderService::getProvidesPortStrings(gov::cca::ComponentID* cid) 
    throw (gov::cca::CCAException) 
{
  char* componentName = componentIDToName(cid);
  jcpp::StringHash* a = bm->getArena();
  Link* l = dynamic_cast<Link*>(a->get(componentName));CHECKDC(l);
  ComponentInfo* ci = l->ci;
  gov::cca::StringList* list = new DefaultStringList();
  SCVector_gov_o_cca_o_PortInfo_p * pi = ci->getProvidesPorts();
  for(int i = 0;i < pi->size();i++) {
    gov::cca::PortInfo* pii = dynamic_cast<gov::cca::PortInfo*>
      (pi->elementAt(i));CHECKDC(pii);
    list->append(pii->getName());
    list->append(pii->getType());

  }
  return list;
}

CDELETE gov::cca::StringList* 
CcaffeineBuilderService::getUsesPortStrings(gov::cca::ComponentID* cid)  
    throw (gov::cca::CCAException)
{
  jcpp::StringHash* a = bm->getArena();
  Link* l = dynamic_cast<Link*>(a->get(componentIDToName(cid)));CHECKDC(l);
  ComponentInfo* ci = l->ci;
  gov::cca::StringList* list = new DefaultStringList();
  SCVector_gov_o_cca_o_PortInfo_p * pi = ci->getUsesPortRegister();
  for(int i = 0;i < pi->size();i++) {
    gov::cca::PortInfo* pii = dynamic_cast<gov::cca::PortInfo*>
      (pi->elementAt(i));CHECKDC(pii);
    list->append(pii->getName());
    list->append(pii->getType());

  }
  return list;
}

gov::cca::StringList*
CcaffeineBuilderService::getConnectionDetails() 
{
  // Whatever.
  return new DefaultStringList();
}

void 
CcaffeineBuilderService::connect(gov::cca::ComponentID* user, 
				 char* usingPortName, 
				 gov::cca::ComponentID* provider, 
				 char* providingPortName, 
				 char* connectionName) 
  throw (gov::cca::CCAException) {
  bm->connect(componentIDToName(provider), 
	      providingPortName,
	      componentIDToName(user), 
	      usingPortName);
  CcafeConnection* c = new CcafeConnection(componentIDToName(provider),
					  providingPortName,
					  componentIDToName(user), 
					  usingPortName);
  connections->put(connectionName, c);
}

void 
CcaffeineBuilderService::disconnect(char* connectionName) 
  throw (gov::cca::CCAException) 
{
}

void 
CcaffeineBuilderService::getConfigurationStrings(gov::cca::ComponentID* cid, 
						 char* portName, 
						 gov::cca::StringList* kvl) 
  throw (gov::cca::CCAException) 
{
  char* config = bm->getConfiguration(componentIDToName(cid), portName);
  kvl->append(config);
  free(config);
}

void 
CcaffeineBuilderService::setConfigurationStrings(gov::cca::ComponentID* cid, 
						 char* portName, 
						 gov::cca::StringList* kvl, 
						 int start, 
						 int count) 
  throw (gov::cca::CCAException) 
{
  int size = kvl->getSize();
  if(size%2) {
    throw new CcafeCCAException("CcaffeineBuilderService::setConfigurationStrings: number of key values in kvl not even number = %d", size );
  }
  for(int i = 0;i < size; i += 2) {
    char* fieldName = kvl->get(i);
    char* value = kvl->get(i+1);
    bm->setConfiguration(componentIDToName(cid), portName, fieldName, value);
    free(fieldName);
    free(value);
  }
}

void 
CcaffeineBuilderService::go(gov::cca::ComponentID* cid, 
   char* portName) 
  throw (gov::cca::CCAException) 
{
  bm->goOne(componentIDToName(cid), portName);
}
