#include <stdio.h>
#include "dc/export/ccafeopq.hh"
#ifdef HAVE_CLASSIC
#include <cca.h> // only for "cca/PortInfo.h" currently
#include <stdPorts.h>
#endif
#include <iostream>

#include <unistd.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/Cmd.h"
#include "dc/user_iface/BuilderController.h"


#include "dc/framework/dc_fwkPublic.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/BuilderModel.h"

#include "util/IO.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/io/jc++io.h"
#include "jc++/jc++dynamic.h"
#include "parameters/parametersStar.h"
#include "parameters/parametersDynamic.h"

#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/CmdLineBuilderViewForHuman.h"
#include "dc/user_iface/CmdLineBuilderViewForGUI.h"

#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"
#include "dc/user_iface/ccacmd/CmdContextCCAMPI.h"
#include "dc/user_iface/ccacmd/CmdActionCCA.h"


#include "dc/port/CCA_Block.h"
#include "dc/port/BlockPort.h"
#include "dc/port/Caffeine_Port_DynamicLink.h"
#include "dc/user_iface/forceIsisBlasLapackLink.h"

#include "dc/user_iface/CmdLineBuilderController2.h"

#ifdef HAVE_BABEL
#ifdef CXX_HEADER_SUFFIX_HXX
#include "gov_cca.hxx"
#include "gov_cca_ports.hxx"
#include "sidl_BaseException.hxx"
#else
#include "gov_cca.hh"
#include "gov_cca_ports.hh"
#include "sidl_BaseException.hh"
#endif
#include "babel_compat.hh"
#endif

#include "stovepipe/stp.h"

#include "util/freefree.h"
#include <exception>

#ifdef _CCAMPI
#include "util/noSeekMPI.h"
#include <mpi.h>
#ifndef lint
static char id[]=
"$Id: CmdLineBuilderController2.cxx,v 1.46 2006/07/31 23:48:37 baallan Exp $ build with MPI";
#endif
#else
#ifndef lint
static char id[]=
"$Id: CmdLineBuilderController2.cxx,v 1.46 2006/07/31 23:48:37 baallan Exp $ build without MPI";
#endif
#endif

/** A command line controller of the Model-View-Controller pattern for
  the builder.  This reads from input and instructs the BuilderModel
  to perform actions and the BuilderView to printout information. 

  This implementation encapsulates all the globals into a command
  context cc.
 */

void CmdLineBuilderController2::setup() {
  cp->setContextVerbose(false);
  cp->addAction(new CmdActionCCADisplay());
  cp->addAction(new CmdActionCCAInstantiate());
  cp->addAction(new CmdActionCCAConnect());
  cp->addAction(new CmdActionCCADisconnect());
  cp->addAction(new CmdActionCCAConfig());
  cp->addAction(new CmdActionCCAGo());
  cp->addAction(new CmdActionCCAPallet());
  cp->addAction(new CmdActionCCAArena());
  cp->addAction(new CmdActionCCALinks());
  cp->addAction(new CmdActionCCAProperties());
  cp->addAction(new CmdActionCCAPortProperties());
  cp->addAction(new CmdActionCCARemove());
  cp->addAction(new CmdActionCCANuke());
  cp->addAction(new CmdActionCCARepository());
  cp->addAction(new CmdActionCCAPath());
  cp->addAction(new CmdActionCCADebug());
  cp->addAction(new CmdActionCCANoDebug());
  cp->addAction(new CmdActionCCAShell());
}

/** Add an action to the command stream of the controller.  Right
    now the Benware does not support removal. */
void 
CmdLineBuilderController2::addAction(CmdAction* action) {
  // This is where we give praise that this thing is single-threaded.
  cp->addAction(action);
}

namespace {
	void myunexpected()
	{
		::printf("Unexpected exception detected. You Lose.");
		::std::terminate();
	}
	class STC {
		::std::unexpected_handler old;
		public:
		STC( ::std::unexpected_handler f) { old = ::std::set_unexpected(f); }
		~STC() { std::set_unexpected(old); }
	};
};

int CmdLineBuilderController2::parse() {
  STC(myunexpected());
  try {
    dbm -> initScript();
    return cp->parse();
  }
#ifdef HAVE_BABEL
  catch ( ::gov::cca::TypeMismatchException & bte ) {
    ::std::cout << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cout << "TypeMismatchException: " << bte.SIDL_EXCEPTION_getMessage() << ::std::endl;
    ::std::cout << bte.getTrace() << ::std::endl;
    return -2;
  }
  catch ( ::gov::cca::CCAException & bce ) {
    ::std::cout << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cout << "CCAException: " << bce.SIDL_EXCEPTION_getMessage() << ::std::endl;
    ::std::cout << bce.getTrace() << ::std::endl;
    return -2;
  }
  catch ( sidl::BaseException & bse ) {
    ::std::cout << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cout << "sidl::BaseException: " << bse.SIDL_EXCEPTION_getMessage() << ::std::endl;
    ::std::cout << bse.getTrace() << ::std::endl;
    return -2;
  }
#endif
  catch ( ::ccafeopq::Exception &oe)
  {
    ::std::cout << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cout << oe.what() << ::std::endl;
    ::std::cerr << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cerr << oe.what() << ::std::endl;
    return -2;
  }
  catch ( ::std::exception &e)
  {
    ::std::cout << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cout << e.what() << ::std::endl;
    ::std::cerr << "CmdLineBuilderController2 caught fatal error:" << ::std::endl;
    ::std::cerr << e.what() << ::std::endl;
    return -2;
  }
}


CmdLineBuilderController2::CmdLineBuilderController2(CmdLineBuilderView *bv, DefaultBuilderModel* bm) {
  dbm = bm;
  cp = new CmdParse((
#ifdef _CCAMPI
#ifdef _INTERACTIVE
			  new CmdContextCCAMPI(bv, bm, false)
#else
			  new CmdContextCCAMPI(bv, bm, true)
#endif
#else
			  new CmdContextCCA(bv, bm)
#endif
		  ));
  setup();
}

CmdLineBuilderController2::CmdLineBuilderController2(FILE* in, CmdLineBuilderView* bv, DefaultBuilderModel* bm) {
  dbm = bm;
  cp = new CmdParse((
#ifdef _CCAMPI
#ifdef _INTERACTIVE
			  new CmdContextCCAMPI(in, bv, bm, false)
#else
			  new CmdContextCCAMPI(in, bv, bm, true)
#endif
#else
			  new CmdContextCCA(in, bv, bm)
#endif
		  ));
  setup();
}

CmdLineBuilderController2::~CmdLineBuilderController2() {
  CmdContext *cc = cp->getContext();
  delete cp;
  delete cc;
  dbm = 0;
};

int CmdLineBuilderController2::main(int argc, char **argv) {
  int debug = 0;
  int result = 0;
  // stovepipe init has been already called by this time. - Rob

  if(debug) {
    fprintf(stderr, "there are %d arguments\n", argc);
    for(int i = 0;i < argc;i++){
      fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
    }
  }

  const char *s;
  if (
	(s=stp_get("type")) != 0 ||
	(s=stp_get("port")) != 0 ||
	(s=stp_get("name")) != 0 ||
	(s=stp_get("file")) != 0 ||
	(s=stp_get("ccafe-type")) != 0 ||
	(s=stp_get("ccafe-port")) != 0 ||
	(s=stp_get("ccafe-name")) != 0 ||
	(s=stp_get("ccafe-file")) != 0 ||
	(s=stp_get("ccafe-waitForGdbAttach")) != 0 ||
	(s=stp_get("cafe-waitForGdbAttach")) != 0
     ) {
      fprintf(stderr, "#!ERROR: %s called with invalid option %s\n", 
	      argv[0], s );
      fprintf(stderr, "#!ERROR: You probably mean to use ccafe-client.\n");
      return -2;
  }
  
  if( (s = stp_get("help")) != 0) {
    char* usage = "%s "
      "[--ccafe-rc <rc file>]\n"
      "[--help]\n"
      "\n"
"  --ccafe-rc <rc file> \n"
"       Source the given file into ccaffeine. \n"
" \n"
"  --help\n"
"       This message. \n";
    fprintf(stderr, usage, argv[0]);
    exit(0);
  }

  int err;
  IO::en("CLBC2::main starting DefaultBuilderModel with no mpi communicator.");
  CDELETE DefaultBuilderModel* bm = new DefaultBuilderModel(err,0,0,false);
  if(err) {
    IO::en(":-( Could not create DefaultBuilderModel in "
	   "CmdLineBuilderController2::main, bailing ...");
  }
    
  CDELETE CmdLineBuilderView *bv = (CmdLineBuilderView *)
    new CmdLineBuilderViewForHuman();
  bv->setBuilderModel(bm);

  CDELETE CmdLineBuilderController2 *blat = 
    new CmdLineBuilderController2(bv, bm);

  result = blat->parse();

  delete blat;
  delete bv;
  return result;
}

int CmdLineBuilderController2::forceLink() {
  // This should not be optimized away, as a C++ compiler has
  // no business assuming the lack of global side effects.
	// don't actually instantiate the pieces in jc++
  Caffeine_Port_DynamicLink* cpdl = new Caffeine_Port_DynamicLink(0);
  JCPP_DynamicLink *jdl = new JCPP_DynamicLink(0); 
  parameters_DynamicLink *pdl = new parameters_DynamicLink(0);
  delete jdl;
  delete pdl;
  delete cpdl;
  forceIsisBlasLapackLink(0);
  return 0;
}
