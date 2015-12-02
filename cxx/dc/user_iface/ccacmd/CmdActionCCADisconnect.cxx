
#ifndef lint
static char id[]=
"$Id: CmdActionCCADisconnect.cxx,v 1.5 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCADisconnect.h"

#include "util/IO.h"
#include "util/freefree.h"

CmdActionCCADisconnect::CmdActionCCADisconnect() {
  namelist[0] = "disconnect";
}

CmdActionCCADisconnect::~CmdActionCCADisconnect() {
}

int CmdActionCCADisconnect::doIt(CmdContext *cc, JCPN(Vector) *args) {

  char *fromInstance;
  char *providesInstance;
  char *toInstance;
  char *usesInstance;
   
  toInstance = args->getString(0);
  usesInstance = args->getString(1);
  fromInstance = args->getString(2);
  providesInstance = args->getString(3);

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);
  int err = 0;
  err =  cca->bm->disconnect(fromInstance, providesInstance,
                   toInstance, usesInstance);
  if (err) {
    cca->bv->displayDisconnectionFailed("cca->bm->disconnect failed");
    return 0;
  }
  cca->bv->disconnect(fromInstance, providesInstance,
                      toInstance, usesInstance);
  return 0;
}

char * CmdActionCCADisconnect::help() {
  return 
  "<using instance> <used Port name> <providing instance> <provided Port name>\n"
  "          - break a connection between two instantiated components \n"
  "            residing in the arena.";
}

char *CmdActionCCADisconnect::argtype() {
  return "ISIS";
}

char **CmdActionCCADisconnect::names(int &len) {
  len = 1;
  return namelist;
}

