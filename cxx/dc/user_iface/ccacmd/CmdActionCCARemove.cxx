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

#include "CmdActionCCARemove.h"

#include "util/freefree.h"
#include "util/IO.h"

#ifndef lint
static char id[]=
"$Id: CmdActionCCARemove.cxx,v 1.16 2005/01/11 01:21:20 baallan Exp $";
#endif

CmdActionCCARemove::CmdActionCCARemove() {
  namelist[0] = "remove";
}

CmdActionCCARemove::~CmdActionCCARemove() { }


char* CmdActionCCARemove::argtype() {
  return "i";
}


char** CmdActionCCARemove::names(int& name_len) {
  name_len = 1;
  return namelist;
}


char* CmdActionCCARemove::help() {
  return "remove <component instance name>";

}


int CmdActionCCARemove::doIt(CmdContext* cc, JCPN(Vector)* args) {

  CmdContextCCA* cca = dynamic_cast<CmdContextCCA*>(cc); CHECKDC(cca);

  char* instanceName = args->getString(0);

  IO_dn2("about to remove %s", instanceName);
  cca->bm->removeInstantiatedComponent(instanceName);
  cca->bv->p("remove "); //Colin changed this so gui can take it as a command
  cca->bv->pn(instanceName);
  return 0;
}



