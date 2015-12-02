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

#include "CmdActionCCAPallet.h"

#include "util/freefree.h"

#ifndef lint
static char id[]=
"$Id: CmdActionCCAPallet.cxx,v 1.12 2004/01/21 06:21:57 baallan Exp $";
#endif

CmdActionCCAPallet::CmdActionCCAPallet() {
  namelist[0] = "pallet";
  namelist[1] = "palette";
  namelist[2] = "classes";
}

CmdActionCCAPallet::~CmdActionCCAPallet() {
}

char *CmdActionCCAPallet::argtype() {
  return "";
}

char **CmdActionCCAPallet::names(int& name_length) {
  name_length = 2;
  return namelist;
}

char *CmdActionCCAPallet::help() {
  return "show what component classes are in the palette currently.";
}

int CmdActionCCAPallet::doIt(CmdContext *cc, JCPN(Vector) *args) {
  (void) args;
  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);
  cca->bv->displayPallet();
  return 0;
}
