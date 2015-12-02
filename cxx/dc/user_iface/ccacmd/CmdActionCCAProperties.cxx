#ifndef lint
static char id[]=
"$Id: CmdActionCCAProperties.cxx,v 1.9 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCAProperties.h"

#include "util/freefree.h"

CmdActionCCAProperties::CmdActionCCAProperties() {
  namelist[0] = "property";
}

CmdActionCCAProperties::~CmdActionCCAProperties() {
}

char * CmdActionCCAProperties::argtype() {
  return "Isa";
}

char ** CmdActionCCAProperties::names(int &len) {
  len = 1;
  return namelist;
}

char * CmdActionCCAProperties::help() {
  return 
"property <component-instance-name>\n"
"   - show all the properties of a component.\n"
"property <component-instance-name> <key>\n"
"   - show all the named property of a component, if it exists.\n"
"property <component-instance-name> <key> <value>\n"
"   - set the named property of a component.";
}

int CmdActionCCAProperties::doIt(CmdContext *cc, JCPN(Vector) *args) {
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  if (args->size() < 1) {
    cca->bv->pn("need a component instance name.");
    return 0;
  } 

  char * instanceName = args->getString(0);
  if (args->size() == 1) {
// printf("properties of %s\n",instanceName);
    ::std::string stdname = instanceName;
    std::vector< std::string > props = cca->bm->getComponentProperties(stdname);
    cca->bv->displayComponentProperties(instanceName,props);
    return 0;
  }
  char * key = args->getString(1);
  if (args->size() == 2) {
    std::string value = cca->bm->getComponentProperty(instanceName,key);
// printf("property of %s %s\n",instanceName,key);
    cca->bv->displayComponentProperty(instanceName,key,const_cast<char *>(value.c_str()));
    return 0;
  }
  char * value = args->getString(2);
// printf("property of %s setting %s to %s\n",instanceName,key,value);
  int err = 0; 
  cca->bm->setComponentProperty(instanceName,key,value);
  cca->bv->setComponentProperty(instanceName,key,value,err);

  return 0;
}

