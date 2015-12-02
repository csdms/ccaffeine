#ifndef lint
static char id[]=
"$Id: CmdActionCCAGo.cxx,v 1.15 2004/03/05 02:21:32 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCAGo.h"

#include "util/freefree.h"

CmdActionCCAGo::CmdActionCCAGo() {
  namelist[0] = "go";
  namelist[1] = "run"; 
}

CmdActionCCAGo::~CmdActionCCAGo() { }


char *CmdActionCCAGo::argtype() {
  return "is";
}

char **CmdActionCCAGo::names(int& name_len) {
  name_len = 2;
  return namelist;
}

char *CmdActionCCAGo::help() {
  return "cause the connection framework to run the framed components.";
}

int CmdActionCCAGo::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc); CHECKDC(cca);

  if (args->size() == 2) {
    char *instanceName = (char *)args->getString(0);
    char *portName = (char *)args->getString(1);

    int err =  cca->bm->goOne(instanceName,portName);
    if (err) {
      cca->bv->error("#specific go command failed");
      return 0;
    }
    cca->bv->pn("##specific go command successful");
    return 0;
  }
#if 0 // gone
  // else do the global go
  cca->bv->pn("##trying all \"go\" ports.");
  int err =  cca->bm->go();
  if  (err) {
    cca->bv->error("#CmdActionCCAGo::doIt go command failed");
    return 0;
  }
  cca->bv->pn("go command successful");
#else
  cca->bv->error("#CmdActionCCAGo: go command requires specific component and goport names");
#endif
  return 0;

}
