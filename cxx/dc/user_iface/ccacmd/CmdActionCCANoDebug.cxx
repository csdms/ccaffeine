
#include "util/freefree.h"

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

#include "dc/user_iface/ccacmd/CmdActionCCANoDebug.h"

#include "util/IO.h"
#include "util/freefree.h"

#ifndef lint
static char id[]=
"$Id: CmdActionCCANoDebug.cxx,v 1.6 2004/01/21 06:21:57 baallan Exp $";
#endif

CmdActionCCANoDebug::CmdActionCCANoDebug() {
  namelist[0] = "nodebug";
  namelist[1] = "quiet";
}

CmdActionCCANoDebug::~CmdActionCCANoDebug() {
}

char *CmdActionCCANoDebug::argtype() {
  return "";
}

char **CmdActionCCANoDebug::names(int & name_length) {
  name_length = 2;
  return namelist;
}

char *CmdActionCCANoDebug::help() {
  return "turns off debugging print statements.";
}

int CmdActionCCANoDebug::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  cca->bm->setDebug(false);
  IO::setDebug(false);
  return 0;
}

