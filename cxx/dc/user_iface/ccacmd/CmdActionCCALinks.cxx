#ifndef lint
static char id[]=
"$Id: CmdActionCCALinks.cxx,v 1.9 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCALinks.h"

#include "util/freefree.h"

CmdActionCCALinks::CmdActionCCALinks() {
  namelist[0] = "links";
  namelist[1] = "chain";
}

CmdActionCCALinks::~CmdActionCCALinks() {
}

char * CmdActionCCALinks::argtype() {
  return "";
}

char ** CmdActionCCALinks::names(int &len) {
  len = 2;
  return namelist;
}

char * CmdActionCCALinks::help() {
  return "show what connections are in the arena currently.";
}

int CmdActionCCALinks::doIt(CmdContext *cc, JCPN(Vector) *args) {
  (void)args;
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);
  cca->bv->displayChain();
  return 0;
}

