#ifndef lint
static char id[]=
"$Id: CmdActionCCAPortProperties.cxx,v 1.5 2004/01/21 06:21:57 baallan Exp $";
#endif

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"

#include "dc/framework/dc_fwkPublic.h"

#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"

#include "dc/user_iface/ccacmd/CmdActionCCAPortProperties.h"

#include "util/freefree.h"

CmdActionCCAPortProperties::CmdActionCCAPortProperties() {
  namelist[0] = "port-property";
}

CmdActionCCAPortProperties::~CmdActionCCAPortProperties() {
}

char * CmdActionCCAPortProperties::argtype() {
  return "ISssa";
}

char ** CmdActionCCAPortProperties::names(int &len) {
  len = 1;
  return namelist;
}

char * CmdActionCCAPortProperties::help() {
  return 
"port-property <component-instance-name> <port-name>\n"
"   - show all the properties of a port on a component.\n"
"port-property <component-instance-name> <port-name> <key>\n"
"   - show all the named property of a component port, if it exists.\n"
"port-property <component-instance-name> <port-name> <key> <type> <value>\n"
"   - set the named property of a component port.";
}

int CmdActionCCAPortProperties::doIt(CmdContext *cc, JCPN(Vector) *args) {
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  if (args->size() < 2) {
    cca->bv->pn("need a component instance name and a port name.");
    return 0;
  } 

  const std::string instanceName = args->getString(0);
  const std::string portName = args->getString(1);
  if (args->size() == 2) {
    ::ccafeopq::TypeMap_shared props = cca->bm->getPortProperties(instanceName, portName);
    if (!props) {
      cca->bv->pn("need a valid component instance name and a valid port name.");
      return 0;
    }
    cca->bv->displayPortProperties(instanceName,portName,props,"");
    return 0;
  }
  const std::string key = args->getString(2);
  if (args->size() == 3) {
    ::ccafeopq::TypeMap_shared props = cca->bm->getPortProperties(instanceName, portName);
    if (!props) {
      cca->bv->pn("need a valid component instance name and a valid port name.");
      return 0;
    }
    cca->bv->displayPortProperties(instanceName, portName, props,key);
    return 0;
  }
  std::string valueType = args->getString(3);
  if (args->size() == 4) {
    cca->bv->pn("to set port property, need component-name port-name value-type and value.");
    return 0;
  }
  std::string value = args->getString(4);
  int err = cca->bm->setPortProperty(instanceName,portName,key,valueType,value);
  cca->bv->setPortProperty(instanceName,portName,key,valueType,value,err);

  return 0;
}

