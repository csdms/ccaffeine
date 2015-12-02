

#ifndef lint
static char id[]=
"$Id: CmdActionCCAConfig.cxx,v 1.15 2005/02/01 00:14:32 baallan Exp $";
#endif

#include <assert.h>
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

#include "dc/user_iface/ccacmd/CmdActionCCAConfig.h"

#include "util/freefree.h"
#include <string>

CmdActionCCAConfig::CmdActionCCAConfig() {
  namelist[0] = "configure"; 
  namelist[1] = "parameters";
}

CmdActionCCAConfig::~CmdActionCCAConfig() {
}

char *CmdActionCCAConfig::argtype() {
  return "ISSs*";
}

char ** CmdActionCCAConfig::names(int &nlen) {
  nlen = 2;
  return namelist;
}

char *CmdActionCCAConfig::help() {
  return "query or set the configuration parameters of a component port";
}

int CmdActionCCAConfig::doIt(CmdContext *cc, JCPN(Vector) *args) {
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc); CHECKDC(cca);

  if (args->size() < 3) {
    cca->bv->pn("need a component instance name, port name, and parameter name arguments");
    return 0;
  }

  char *instanceName = (char *)args->getString(0);
  char *portName = (char *)args->getString(1);
  char *fieldName = (char *)args->getString(2);

  if (args->size() < 4) {
    if (strcmp(fieldName,"ALL")==0) {
      CFREE char *configuration;
      configuration = cca->bm->getConfiguration(instanceName,portName);
      if (configuration == 0 || strlen(configuration) == 0) {
/*
        // no configure interface on instance name. punt.
        //cca->bv->pn("need a valid ParameterPort name");
*/
        return 0;
      }
      cca->bv->displayConfiguration(instanceName,portName,configuration);
      free(configuration);
      return 0;
    }
    // else dump named field
    CFREE char *configuration;
    configuration = cca->bm->getConfiguration(instanceName,portName,fieldName);
    if (configuration == 0 || strlen(configuration) == 0) {
      return 0;
    }
    cca->bv->displayConfiguration(instanceName,portName,configuration);
    free(configuration);
    return 0;
  }

  if (strcmp(fieldName,"ALL")==0) {
    cca->bv->pn("'ALL' cannot be used to set a parameter value.");
    return 0;
  }
 

  std::string svalue;
  int iarg = 3;
  int nargs = args->size();
  for ( ; iarg < nargs; iarg++) {
    if (iarg >= 4) { svalue += " "; }
    svalue += args->getString(iarg);
  }
  char *value = 0; value = (char *)(svalue.c_str());
  char *configuration = 
    cca->bm->setConfiguration(instanceName,portName,fieldName,value);
  if (configuration == 0 || strlen(configuration) == 0) {
    // no configure interface on instance name and port. punt.
    return 0;
  }
  cca->bv->setConfiguration(instanceName,portName,fieldName,configuration);
  cca->bv->p("updated parameter ");
  cca->bv->p(instanceName);
  cca->bv->p(" ");
  cca->bv->p(portName);
  cca->bv->p(" ");
  cca->bv->pn(fieldName);
  return 0;
}
