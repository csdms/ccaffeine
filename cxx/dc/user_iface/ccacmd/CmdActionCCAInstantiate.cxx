#ifndef lint
static char id[]=
"$Id: CmdActionCCAInstantiate.cxx,v 1.12 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCAInstantiate.h"

#include "util/freefree.h"

CmdActionCCAInstantiate::CmdActionCCAInstantiate() {
  namelist[0] = "pulldown";
  namelist[1] = "instantiate";
  namelist[2] = "create";
}

CmdActionCCAInstantiate::~CmdActionCCAInstantiate() {
}


char * CmdActionCCAInstantiate::argtype() {
  return "Cs";
}


char **CmdActionCCAInstantiate::names(int & len) {
  len = 3;
  return namelist;
}


char * CmdActionCCAInstantiate::help() {
  return "create an arena instance from a class.";
}


int CmdActionCCAInstantiate::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  char *clazz;
  std::string iname;

  if(args->size() == 1) {
    clazz = args->getString(0);
    if (!clazz) {return 0; }
    std::string sclass = clazz;
    iname = cca->bm->pullDownFromPallet(sclass);
    if (iname.size() == 0) {
      cca->bv->error("instantiation unsuccessful");
      return 0;  
    }
    cca->bv->pullDownComponent(sclass.c_str(), iname.c_str());
    return 0;  
  }
  if (args->size() == 2) { 
    clazz = args->getString(0);
    if (!clazz) {return 0; }
    std::string sclass = clazz;
    char *instance = args->getString(1);
    if (!instance) {return 0; }
    std::string jname = instance;
    iname = cca->bm->pullDownFromPallet(clazz, jname);
    if (iname.size() == 0) {
      cca->bv->error("instantiation unsuccessful");
      return 0; 
    }
    cca->bv->pullDownComponent(sclass.c_str(), iname.c_str());
    return 0;  
  }
  cca->bv->error("instantiation called incorrectly.");
  
  return 0;  
}

