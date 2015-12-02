#ifndef lint
static char id[]=
"$Id: CmdActionCCADisplay.cxx,v 1.13 2004/01/21 06:21:57 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCADisplay.h"

#include "util/freefree.h"


CmdActionCCADisplay::CmdActionCCADisplay() {
  namelist[0] = "display";
}

CmdActionCCADisplay::~CmdActionCCADisplay() {
}

char *CmdActionCCADisplay::argtype() {
  return "Si";
}

char **CmdActionCCADisplay::names(int &len) {
  len =1;
  return namelist;
}

char *CmdActionCCADisplay::help() {
  return 
    "display palette\n"
    "display pallet\n"
    "       - show what is in the palette currently.\n"
    "display arena\n"
    "       - show what is in the arena currently.\n"
    "display component <component instance name>\n"
    "       - show the ports and class name associated with a component\n"
    "display chain <component instance name>\n"
    "       - show the connections associated with a particular\n"
    "display state\n"
    "       - equivalent to \"display arena\" and then \"display chain\"\n";

}

int CmdActionCCADisplay::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA* cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  char *s = args->getString(0);

  char *sub; // check for various abbreviations against this.

  sub = "pallet";
  if (JString::startsWith(sub,s)) {
    cca->bv->displayPallet();
    return 0;
  }

  sub = "palette";
  if (JString::startsWith(sub,s)) {
    cca->bv->displayPallet();
    return 0;
  }

  sub = "arena";
  if(JString::startsWith(sub,s)) {
    cca->bv->displayInstantiatedComponents();
    return 0;
  }

  sub = "chain";
  if(JString::startsWith(sub,s)) {
    cca->bv->displayChain();
    return 0;
  }

  sub = "component";
  if(JString::startsWith(sub,s)) {
    if (args->size() != 2) {
      cca->bv->pn("need a component instance name argument");
      return 0;
    }
    char *instanceName = args->getString(1);
    cca->bv->displayComponentInfo(instanceName);
    return 0;
  }

    sub = "state";
    if(JString::startsWith(sub, s)) {
      // This will cause components living on the far end to be
      // (re)instantiated in the GUI.
      cca->bv->displayInstantiatedComponents();
      // Instance names of cmpts are the keys:
      ::std::vector< ::std::string  > keys = cca->bm->getInstanceNames();
      for( size_t ni = 0; ni < keys.size(); ni++) { 
	::std::string name = keys[ni];
	std::vector< std::string> prop = cca->bm->getComponentProperties(name);
	cca->bv->displayComponentProperties((char *)name.c_str(), prop);
      }
      cca->bv->displayChain();
      return 0;
    }

  cca->bv->p("display option ");
  cca->bv->p(s);
  cca->bv->pn("unknown");
  return 0;
}

