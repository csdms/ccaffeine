#ifndef lint
static char id[]=
"$Id: CmdActionCCAPath.cxx,v 1.13 2005/11/16 03:21:28 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCAPath.h"

#include "stovepipe/stp.h"
#include "util/freefree.h"

CmdActionCCAPath::CmdActionCCAPath() {
  namelist[0] = "path";
}

CmdActionCCAPath::~CmdActionCCAPath() {
}


char * CmdActionCCAPath::argtype() {
  return "ss";
}


char **CmdActionCCAPath::names(int & len) {
  len = 1;
  return namelist;
}


char * CmdActionCCAPath::help() {
  return "path init\n"
    "       - set framework path from env(CCA_COMPONENT_PATH) and commandline options.\n"
    "    path append <directory>\n"
    "       - add directory to path.\n"
    "    path prepend <directory>\n"
    "       - insert directory before path.\n"
    "    path set\n"
    "       - replace path. format input as env()\n"
    "    path\n"
    "       - show path";
}


int CmdActionCCAPath::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  std::vector< std::string > argv; int argc;
  int i;
  if(args->size() == 0) {
    argv = cca->bm->getRepositoryPath();
    argc = argv.size();
    cca->bv->pn("pathBegin");
    for (i = 0; i < argc; i++) {
      cca->bv->p("pathElement ");
      cca->bv->pn(argv[i].c_str());
    }
    cca->bv->p("pathEnd");
    if (!i) {
      cca->bv->pn("! empty path.");
    }
    return 0;
  }

  if(args->size() == 1) {
    char *sub = args->getString(0);
    if (strcmp(sub,"init")!=0) {
      cca->bv->error("unknown subcommand of path given");
      return 0; 
    }
    char *ccacp;
    ccacp = getenv("CCA_COMPONENT_PATH");
    const char *clpath;
    clpath = stp_getn("ccafe","component-path");
    if (ccacp == 0 && clpath == 0) {
      cca->bv->error("No CCA_COMPONENT_PATH and no commandline path set");
      return 0;  
    }
    std::string totalpath;
    if (ccacp != 0) {
	totalpath = ccacp;
	totalpath += ":";
    }
    if (clpath != 0) {
	totalpath += clpath;
    }
    const char *tpchar = totalpath.c_str(); 
    char **cargv = pathToArgv(tpchar,argc);
    cca->bm->setRepositoryPath(cargv,argc);
    destroyP2A(cargv,argc);
    return 0; 
  }

  char *sub, *rhs;
  if (args->size() == 2) { 
    char **cargv;
    sub = args->getString(0);
    rhs = args->getString(1);
    if (strcmp(sub,"set")==0) {
      cargv = pathToArgv(rhs,argc);
      cca->bm->setRepositoryPath(cargv,argc);
      destroyP2A(cargv,argc);
      return 0;
    }
    if (strcmp(sub,"prepend")==0) {
      argv = cca->bm->getRepositoryPath();
      argc = argv.size();
      char **newArgv = (char **)malloc(sizeof(char *)*(argc+2));
      newArgv[0]=rhs;
      for (i = 0; i < argc; i++) {
        newArgv[i+1] = STRDUP(argv[i].c_str());
      }
      newArgv[argc+1] = 0;
      cca->bm->setRepositoryPath(newArgv,argc+1);
      for (i = 1; i <= argc; i++) {
        free(newArgv[i]);
      }
      free(newArgv);
      return 0;
    }
    if (strcmp(sub,"append")==0) {
      argv = cca->bm->getRepositoryPath();
      argc = argv.size();
      char **newArgv = (char **)malloc(sizeof(char *)*(argc+2));
      for (i = 0; i < argc; i++) {
        newArgv[i] = STRDUP(argv[i].c_str());
      }
      newArgv[argc] = rhs;
      newArgv[argc+1] = 0;
      cca->bm->setRepositoryPath(newArgv,argc+1);
      for (i = 0; i < argc; i++) {
        free(newArgv[i]);
      }
      free(newArgv);
      return 0;
    }
  }
  cca->bv->error("path called incorrectly.");
  
  return 0;  
}

#ifdef __WIN32__
#define SLASH '\\'
#define PATHDIV ';'
#define QPATHDIV ";"
#else /* ! __WIN32__ */
#define SLASH '/'
#define PATHDIV ':'
#define QPATHDIV ":"
#endif

// the next to functions fall in the category of stupid
// pet tricks...

void CmdActionCCAPath::destroyP2A(char **&argv, int argc) {
  free(argv[argc+1]); // we hid the data after the null
  free(argv);
  argv = 0;
}
  
char **CmdActionCCAPath::pathToArgv(const char *path,int &argc) {

  char *ps = STRDUP(path); // copy to modify
  char *head = ps; char *keep = ps;
  
  int i;
  // eat the lhs of env = foo
  while (ps[0] != '\0' && ps[0] != '=') { ps++; }
  if (ps[0] != '=') {
    ps = head; // not the shell env var, but a user input string.
  } else {
    // eat the = and whitespace
    while (ps[0] != '\0' && (ps[0] == '=' || ps[0] == ' ')) {ps++;}
  }
  // path is now the value.
  head = ps;
  int numsep = 0;
  while (ps[0] != '\0') {
    if (ps[0] == PATHDIV) { numsep++; }
    ps++;
  }
  ps = head;
  argc = numsep+1;
  char **argv = (char **)malloc(sizeof(char*)*(argc+2));
  argv[argc] = 0;
  argv[argc+1] = keep; // hide here and free later.
  for (i = 0; i < argc; i++) {
    while (ps[0] != '\0' && ps[0] != PATHDIV) { ps++; }
    if (ps[0] == PATHDIV) {
      argv[i] = head;
      ps[0]= '\0';
      ps++;
      head = ps;
    } else {
      argv[i] = head;
    }
  }
  return argv;
}
