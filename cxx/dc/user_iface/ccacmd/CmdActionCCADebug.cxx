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

#include "dc/user_iface/ccacmd/CmdActionCCADebug.h"

#include "util/IO.h"
#include "util/freefree.h"


#ifndef lint
static char id[]=
"$Id: CmdActionCCADebug.cxx,v 1.6 2004/01/21 06:21:57 baallan Exp $";
#endif

#include "util/freefree.h"

CmdActionCCADebug::CmdActionCCADebug() {
  namelist[0] = "debug";
  namelist[1] = "noisy";
}

CmdActionCCADebug::~CmdActionCCADebug() {
}

char *CmdActionCCADebug::argtype() {
  return "";
}

char **CmdActionCCADebug::names(int & name_length) {
  name_length = 2;
  return namelist;
}

char *CmdActionCCADebug::help() {
  return "turns on debugging print statements. toggles IO::debug.";
}

int CmdActionCCADebug::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  cca->bm->setDebug(true);
  IO::setDebug(true);
  return 0;
}

