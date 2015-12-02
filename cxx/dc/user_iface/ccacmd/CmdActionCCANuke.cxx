
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

#include "CmdActionCCANuke.h"

#include "util/IO.h"
#include "util/freefree.h"

#ifndef lint
static char id[]=
"$Id: CmdActionCCANuke.cxx,v 1.12 2005/01/11 01:21:20 baallan Exp $";
#endif

CmdActionCCANuke::CmdActionCCANuke() {
  namelist[0] = "nuke";
}

CmdActionCCANuke::~CmdActionCCANuke() { }


char* CmdActionCCANuke::argtype() {
  return "S";
}


char** CmdActionCCANuke::names(int& name_len) {
  name_len = 1;
  return namelist;
}


char* CmdActionCCANuke::help() {
  return "remove all components in the arena";

}


int CmdActionCCANuke::doIt(CmdContext* cc, JCPN(Vector)* args) {

  CmdContextCCA* cca = dynamic_cast<CmdContextCCA*>(cc); CHECKDC(cca);

  if(args->size() > 1) {
    cca->bv->error("nuke should have only one argument: all");
    return 0;
  }
  char* instanceName = (char*)args->getString(0);
  IO::pn("all = %s", instanceName);
  if(strcmp(instanceName, "all") != 0) {
    cca->bv->error("nuke has to have an argument: all\n nothing removed from arena");
    return 0;
  }

  cca->bm->removeAllInstantiatedComponents();
  cca->bv->pn("Nuked all components");
  return 0;
}



