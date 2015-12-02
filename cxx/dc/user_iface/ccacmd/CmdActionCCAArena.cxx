#ifndef lint
static char id[]=
"$Id: CmdActionCCAArena.cxx,v 1.11 2004/01/21 06:21:57 baallan Exp $";
#endif

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
//#include <cca.h>
//#include <stdPorts.h>

#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"

#include "dc/framework/dc_fwkPublic.h"

#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"

#include "dc/user_iface/ccacmd/CmdActionCCAArena.h"

#include "util/freefree.h"

CmdActionCCAArena::CmdActionCCAArena() {
  namelist[0] = "arena";
  namelist[1] = "instances";
}

CmdActionCCAArena::~CmdActionCCAArena() {
}

char * CmdActionCCAArena::argtype() {
  return "";
}

char ** CmdActionCCAArena::names(int &len) {
  len = 2;
  return namelist;
}

char * CmdActionCCAArena::help() {
  return "show what instances are in the arena currently.";
}

int CmdActionCCAArena::doIt(CmdContext *cc, JCPN(Vector) *args) {
  (void)args;
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);
  cca->bv->displayInstantiatedComponents();
  return 0;
}

