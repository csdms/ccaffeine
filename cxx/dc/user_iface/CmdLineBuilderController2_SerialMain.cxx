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
#include "AllCCA.hh"
#include "sidl_BaseException.hh"
#endif

#include "stovepipe/stp.h"

#include "util/freefree.h"
#include <exception>

#ifdef _CCAMPI
#include "util/noSeekMPI.h"
#include <mpi.h>
#ifndef lint
static char id[]=
"main() $Id: CmdLineBuilderController2_SerialMain.cxx,v 1.2 2005/08/29 23:43:14 baallan Exp $ build with MPI";
#endif
#else
#ifndef lint
static char id[]=
"main() $Id: CmdLineBuilderController2_SerialMain.cxx,v 1.2 2005/08/29 23:43:14 baallan Exp $ build without MPI";
#endif
#endif

#ifdef _CCAMPI
/** input is argc/v, and an array argc long of empty/uninit
pointers redargv. output is filled redargv that is output
redargc long. 
redargv is the args stripped of non -started x=y values,
so that getopt (no longer in use) is not unhappy.
 */
 // Check args for environment settings and do them globally.
 // Broadcast ala alan and then call putenv CCAFE_RC_FILE.
void preProcessArgs(int argc, char **argv, int & redargc, char ** redargv, int rank) {

#define bcastargc bcsize[0]
#define maxLen bcsize[1]
  int bcsize[2];
  char **bcastarg = (char **)malloc(sizeof(char *)*(argc+1));
  bcastargc = 0;
  maxLen = 0;
	int i;

  if (rank == 0) {
  // MASTER
    redargc = argc;

    for (i = 0; i < argc; i++) {
      redargv[i] = 0;
      bcastarg[i] = 0;
    }
    redargv[0] = argv[0];
    redargc = 1;

    bool bypass = false;
    // we eat up args of X=Y form until we see one starting with -.
    for (i = 1; i < argc; i++) {
      if (bypass) {
        redargv[redargc] = argv[i];
        redargc++;
        continue;
      }
      if (argv[i][0] == '-') {
        bypass = true;
        redargv[redargc] = argv[i];
        redargc++;
        continue;
      }
      int pos = JString::indexOf(argv[i],'=');
      if (pos>0) { // ignore strings without = internally.
        bcastarg[bcastargc] = argv[i];
        bcastargc++;
      } else {
        redargv[redargc] = argv[i];
        redargc++;
      }
    }
    maxLen = 0;
    for (i = 0; i < bcastargc; i++) {
      int len;
      len = ::strlen(bcastarg[i]);
      if (maxLen < len) { maxLen = len; }
    }
    // send the number and max len of arguments.
    MPI_Bcast(bcsize,2,MPI_INT,0,MPI_COMM_WORLD);
    // copy the strings into persistent pointers.
    for (i = 0; i < bcastargc; i++) {
      char *tmp;
      tmp = new char[maxLen+1];
      for (int j = 0; j <= maxLen; j++) {
        tmp[j] = '\0';
      }
      sprintf(tmp,"%s",bcastarg[i]);
      bcastarg[i] = tmp;
      tmp = 0;
    }
    // send the array of envvars.
    for (i = 0; i < bcastargc; i++) {
      MPI_Bcast(bcastarg[i],maxLen,MPI_CHAR,0,MPI_COMM_WORLD);
    }
  } else {
  // SLAVE
    // receive the number and max len of envvars 
    MPI_Bcast(bcsize,2,MPI_INT,0,MPI_COMM_WORLD);
    // make room for the strings
    for (i = 0; i < bcastargc; i++) {
      char *tmp;
      tmp = new char[maxLen+1];
      for (int j = 0; j <= maxLen; j++) {
        tmp[j] = '\0';
      }
      bcastarg[i] = tmp;
      tmp = 0;
    }
    // receive the strings
    for (i = 0; i < bcastargc; i++) {
      MPI_Bcast(bcastarg[i],maxLen+1,MPI_CHAR,0,MPI_COMM_WORLD);
    }
  }
  // Now, we should all have a copy of the env args.
  // The strings must be abandoned to the putenv call as it
  // may keep the pointers in some unixen.
  //IO::en("Bcast env size %d, buf size %d",bcastargc, maxLen);
  for (i = 0; i < bcastargc; i++) {
    int err = 0;
    err  = putenv(bcastarg[i]);
    //IO::en("putenv(%s) returned %d",bcastarg[i], err);
  }
	free(bcastarg);
	bcastarg = 0;
}
#endif // _CCAMPI

int main(int argc, char **argv) {

  IO::initId(getpid());


  char **redArgv = (char**)malloc(sizeof(char *)*argc+1); // hack size.
#ifdef _CCAMPI
  int redArgc =0;
  int rank,size;

  char* buf = (char*) malloc(4096);
  memset(buf, 0, 4096);
  char* cwd = getcwd(buf, 4096);  // POSIX so I hope it does not break SGI

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  if (size == 1) { 
    // shutup in the 1proc case
    IO::initId(-1);
  } else { 
    IO::initId(rank);
  }
  preProcessArgs(argc,argv,redArgc,redArgv,rank);
  stp_init(argc, argv);
  if( (size == 1) && (stp_getn("ccafe", "pwd") == 0) ) { 
    // 1 proc and no --ccafe-pwd option at the command line.
    stp_putn("ccafe", "pwd", cwd);
  }
  free(cwd);
#else // _CCAMPI
  stp_init(argc, argv);
#endif // _CCAMPI
  CmdLineBuilderController2::main(argc, argv);
#ifdef _CCAMPI
  MPI_Finalize();
#endif // _CCAMPI
  free(redArgv);

  return 0;
}
