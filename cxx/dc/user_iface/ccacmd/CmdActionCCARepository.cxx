#ifndef lint
static char id[]=
"$Id: CmdActionCCARepository.cxx,v 1.12 2005/11/16 03:21:28 baallan Exp $";
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

#include "dc/user_iface/ccacmd/CmdActionCCARepository.h"
#include "stovepipe/stp.h"
#include "util/StringTools.hh"

#include "util/freefree.h"

CmdActionCCARepository::CmdActionCCARepository() {
  namelist[0] = "repository";
}

CmdActionCCARepository::~CmdActionCCARepository() {
}


char * CmdActionCCARepository::argtype() {
  return "Ss";
}


char **CmdActionCCARepository::names(int & len) {
  len = 1;
  return namelist;
}


char * CmdActionCCARepository::help() {
  return 
    "repository list\n"
    "       - show components available in the repository.\n"
    "  The following get options cannot be abbreviated:\n"
    "    repository get class\n"
    "       - load component from the repository list (private and immediate linking).\n"
    "    repository get-ports libraryPathName \n"
    "       - load (global and immediate linking) shared lib libraryPathName.\n"
    "    repository get-global class\n"
    "       - load component from the repository list (global and immediate linking).\n"
    "    repository get-lazy class\n"
    "       - load component from the repository list (private and lazy linking).\n"
    "    repository get-lazy-global class\n"
    "       - load component from the repository list (global and lazy linking).\n"
    "Global linking may be appropriate for components that, as a side effect,\n"
    "for example include libblas, liblapack, libppm, and other legacy C/f77 routines.\n"
    "Such components will need to be loaded before any other components that use the\n"
    "global symbols.\n"
    "    repository init\n"
    "   -  load components specified on command line as private now.\n"
    "    repository init-lazy\n"
    "   -  load components specified on command line as private lazy.\n"
    "    repository init-lazy-global\n"
    "   -  load components specified on command line as global lazy.\n"
    "    repository init-global\n"
    "   -  load components specified on command line as global now."
  ;

}


int CmdActionCCARepository::doIt(CmdContext *cc, JCPN(Vector) *args) {

  CmdContextCCA *cca = dynamic_cast<CmdContextCCA *>(cc);  CHECKDC(cca);

  char *sub;
  std::vector< std::string >argv;
  int argc;


  int err;
  bool global;
  bool lazy;
  const char *cname;
  global = lazy = false;
  // list,init* subcommands
  if(args->size() == 1) {
    sub = args->getString(0);
    if (!sub) { return 0; }
    if (sub[0] == 'l' ) {
      argv = cca->bm->getRepositoryClasses();
      argc = argv.size();
      if (argc == 0) {
        cca->bv->pn("Empty repository.");
      }
      for (int i = 0; i < argc; i+=2) {
        cca->bv->p("RepositoryClass ");
        cca->bv->p(argv[i+1].c_str());
        cca->bv->p(" {");
        cca->bv->p(argv[i].c_str());
        cca->bv->pn("}");
      }
      // gui repository update here?
      return 0;  
    }
    if (sub[0] != 'i') { return 0; }
    if (strcmp(sub,"init-global") == 0) { global = true; }
    if (strcmp(sub,"init-lazy") == 0) { lazy = true; }
    if (strcmp(sub,"init-lazy-global") == 0) { lazy = global = true; }
    if (strncmp(sub,"init",4) == 0) {
      const char* cclasslist = stp_getn("ccafe","component-load");
      if (cclasslist==0) { 
        cca->bv->error("no --ccafe-component-load found for repository init.");
        return 0; 
      }
      std::string classlist = cclasslist;
      std::vector< std::string> nlist = StringTools::split(classlist,':');
      std::string sname;
      cca->bv->error("#got:"); cca->bv->error(classlist);
      for (size_t nc =0; nc < nlist.size(); nc++) {
	sname = nlist[nc];
	if (sname == "") { continue; }
	cname = sname.c_str();
        err = cca->bm->loadRepositoryClass(cname, global, lazy); // per user spec
        if (err) {
	  std::string serr = "Unable to load class "; serr += sname;
          cca->bv->error(serr);
        } else {
          cca->bv->p("Loaded ");
          cca->bv->p(cname);
          if (lazy) {
            cca->bv->p(" LAZY ");
          } else {
            cca->bv->p(" NOW ");
          }
          if (global) {
            cca->bv->p(" GLOBAL ");
          } else {
            cca->bv->p(" PRIVATE ");
          }
          cca->bv->pn(".");
        }
      } // end for
        // gui pallet update here?
      return 0;  
    }
  } // end argsize 1
  // get* subcommands
  if (args->size() == 2) { 
    sub = args->getString(0);
    if (!sub) {return 0; }
    if (sub[0] != 'g') { return 0; }
    if (strcmp(sub,"get-global") == 0) { global = true; }
    if (strcmp(sub,"get-lazy") == 0) { lazy = true; }
    if (strcmp(sub,"get-lazy-global") == 0) { lazy = global = true; }
    cname = args->getString(1);
    if (!cname) {return 0; }
    if (strcmp(sub,"get-ports") == 0) {
      err = cca->bm->loadPorts(cname);
      if (err) {
        cca->bv->error("load Ports unsuccessful.");
        return 0; 
      }
      cca->bv->p("PortsLoaded ");
      cca->bv->p(cname);
      return 0; 
    }
    if (strncmp(sub,"get",3) == 0) {
      err = cca->bm->loadRepositoryClass(cname, global, lazy); // per user spec
      if (err) {
        cca->bv->error("load unsuccessful");
        return 0; 
      }
      cca->bv->p("Loaded ");
      cca->bv->p(cname);
      if (lazy) {
        cca->bv->p(" LAZY ");
      } else {
        cca->bv->p(" NOW ");
      }
      if (global) {
        cca->bv->p(" GLOBAL ");
      } else {
        cca->bv->p(" PRIVATE ");
      }
      cca->bv->pn(".");
      // gui pallet update here?
      return 0;  
    }
  }
  cca->bv->error("repository called incorrectly.");
  
  return 0;  
}

