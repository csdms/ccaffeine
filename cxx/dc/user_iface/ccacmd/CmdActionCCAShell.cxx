#include <errno.h>
#include <string.h>
#include <stdlib.h>

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


#include "dc/user_iface/ccacmd/CmdActionCCAShell.h"

#ifndef lint
static char id[]=
"$Id: CmdActionCCAShell.cxx,v 1.10 2008/12/11 17:27:05 baallan Exp $";
#endif

#include "util/freefree.h"

#ifdef __alpha
#define DISABLED_FOR_CPLANT 1
#endif

CmdActionCCAShell::CmdActionCCAShell() {
  namelist[0] = "shell";
  namelist[1] = "system";
}

CmdActionCCAShell::~CmdActionCCAShell() {
}

char *CmdActionCCAShell::argtype() {
  return "A";
}

char **CmdActionCCAShell::names(int & name_length) {
  name_length = 2;
  return namelist;
}

char *CmdActionCCAShell::help() {
#ifdef DISABLED_FOR_CPLANT
  return "does nothing on cplant public access demo.";
#else
#ifdef CCAFE_CMDSHELL
  return "executes shell commands (no globbing, though)";
#else
  return "Shell calls now disabled by default. configure --enable-shell if needed.";
#endif
#endif
}

int CmdActionCCAShell::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

#ifndef DISABLED_FOR_CPLANT
  char *command = args->getString(0);
  int err = system(command);
  if (err) {
    cca->bv->error(strerror(errno));
  }
  return 0;
#endif
}

