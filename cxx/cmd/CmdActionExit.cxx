#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: CmdActionExit.cxx,v 1.6 2003/07/07 19:08:36 baallan Exp $";
} ENDSEMI

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdActionExit.h"
#include "util/IO.h"
#include <stdlib.h> // for abort

#include "util/freefree.h"


CmdActionExit::CmdActionExit() {
	namelist[0] = (char *)"exit";
	namelist[1] = (char *)"x";
	namelist[2] = (char *)"bye";
	namelist[3] = (char *)"quit";
}

CmdActionExit::~CmdActionExit() {
}

int CmdActionExit::doIt(CmdContext *cc, JCPN(Vector) *args) {

  cc->pn((char *)"\nbye!");
  cc->pn((char *)"exit");

  if (args->size() == 1) {
    // originally planned to have s -> int, but got lazy.
    char * s = (char *)(args->get(0));
    char *ep;
    long ec;
    ec = strtol(s, &ep, 10);
    IO::en("User exited command interpreter (%2000s) ...",s);
    if (ep != s) {
      return (int)ec;
    }
  }
  return 1;
}
  
char * CmdActionExit::help() {
  return (char *)"leave the parser and the calling program, with optional return code.";
}

char * CmdActionExit::argtype() {
  return (char *)"s";
}

char ** CmdActionExit::names(int& len) {
  len=4;
  return namelist;
}
