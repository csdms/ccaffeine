
#ifndef lint
static char id[]=
"$Id: CmdActionCCAConnect.cxx,v 1.12 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCAConnect.h"

#include "util/IO.h"
#include "util/freefree.h"

CmdActionCCAConnect::CmdActionCCAConnect() {
  namelist[0] = "connect";
}

CmdActionCCAConnect::~CmdActionCCAConnect() {
}

int CmdActionCCAConnect::doIt(CmdContext *cc, JCPN(Vector) *args) {

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
  err =  cca->bm->connect(fromInstance, providesInstance,
                   toInstance, usesInstance);
  if (err) {
    cca->bv->displayConnectionFailed("cca->bm->connect failed");
    return 0;
  }
  cca->bv->connect(fromInstance, providesInstance,
                   toInstance, usesInstance);
  return 0;
}

char * CmdActionCCAConnect::help() {
  return 
  "<using instance> <used Port name> <providing instance> <provided Port name>\n"
  "          - make a connection between two instantiated components \n"
  "            residing in the arena.";
}

char *CmdActionCCAConnect::argtype() {
  return "ISIS";
}

char **CmdActionCCAConnect::names(int &len) {
  len = 1;
  return namelist;
}

