#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: CmdActionHelp.cxx,v 1.6 2003/07/07 19:08:36 baallan Exp $";
} ENDSEMI


#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdActionHelp.h"
#include "cmd/CmdParse.h"
#include <stdlib.h> // for abort

#include "util/freefree.h"

void CmdActionHelp::writeCmdNames(CmdContext *cc, CmdAction *c) {
  int i = 0;
  int len;
  char **na;

  na = c->names(len);

  if (cc == NULL || na == NULL) {
      ::abort(); // programmer is an idiot. 
      return;
  }
  // accept NULL terminated or empty string terminated argv
  for (i = 0; i < len; i++) {
    cc->p(na[i]);
    cc->pn((char *)" -- ");
  }
}

void CmdActionHelp::writeArgDesc(CmdContext *cc, char *argtype) {

  int nargs;

  if (argtype==NULL || (nargs = ::strlen(argtype)) == 0) {
    return;
  }

  cc->p((char *)"    arguments: ");

  for (int i = 0; i < nargs; i++) {
    char ch = argtype[i];
    switch (ch) 
    {
      case 'K':
        cc->p((char *)"<long value> ");
        break;
      case 'k':
        cc->p((char *)"[long value] ");
        break;
      case 'D':
        cc->p((char *)"<int value> ");
        break;
      case 'd':
        cc->p((char *)"[int value] ");
        break;
      case 'B':
        cc->p((char *)"<boolean value> ");
        break;
      case 'n':
        cc->p((char *)"[boolean value] ");
        break;
      case 'G':
        cc->p((char *)"<double value> ");
        break;
      case 'g':
        cc->p((char *)"[double value] ");
        break;
      case 'C':
        cc->p((char *)"<class> ");
        break;
      case 'c':
        cc->p((char *)"[class] ");
        break;
      case 'I':
        cc->p((char *)"<instance> ");
        break;
      case 'i':
        cc->p((char *)"[instance] ");
        break;
      case 'S':
        cc->p((char *)"<string token> ");
        break;
      case 's':
        cc->p((char *)"[string token] ");
        break;
      case 'L':
        // cc->p((char *)"@list of CmdActions in the parser@ ");
        break;
      case 'P':
        // cc->p((char *)"@the parser itself@ ");
        break;
      case 'A':
        cc->pn((char *)"[remainder of line as a single string]");
        return;
      case 'a':
        cc->pn((char *)"[remainder of line as a single string]");
        return;
      case '*':
        cc->pn((char *)"[0 or args like previous]");
        return;
      default:
        break;
    }
  }
  cc->pn((char *)"");

}


CmdActionHelp::CmdActionHelp() {
    // these strings are assumed to come from the program/fixed data segment.
  namelist[0]= (char *)"?";
  namelist[1]= (char *)"help";
}

CmdActionHelp::~CmdActionHelp() {
}

int CmdActionHelp::doIt(CmdContext *cc, JCPN(Vector) *args) {

  if (args->size() == 3) {

    CmdParse *p = dynamic_cast<CmdParse *>(args->get(1)); CHECKDC(p);
    char *s = args->getString(2);

    CmdAction *c;
    c = p->getAction(s); // getAction errors are handled internally.

    if (c != null) {
      writeCmdNames(cc, c);
      writeArgDesc(cc, c->argtype());
      cc->p((char *)"    ");
      cc->pn(c->help());
    } 

  } else {

    int j,len;
    JCPN(Vector) *alist = dynamic_cast<JCPN(Vector) *>(args->get(0)); CHECKDC(alist);
    len = alist->size();
    for (j=0; j < len; j++) {
      CmdAction *c = dynamic_cast<CmdAction *>(alist->get(j)); CHECKDC(c);
      writeCmdNames(cc, c);
      writeArgDesc(cc, c->argtype());
      cc->p((char *)"    ");
      cc->pn(c->help());
    }

  }
  return 0;
}

char * CmdActionHelp::help() {
  return (char *)"prints the help of one or all commands";
}

char * CmdActionHelp::argtype() {
  return (char *)"LPs";
}

char **CmdActionHelp::names(int &len) {
  len = 2;
  return namelist;
}
