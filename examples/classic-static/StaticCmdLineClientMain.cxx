#ifdef _CCAMPI
static char id[]=
"main() $Id: StaticCmdLineClientMain.cxx,v 1.1 2004/12/08 22:19:31 baallan Exp $ build with MPI";
#else
static char id[]=
"main() $Id: StaticCmdLineClientMain.cxx,v 1.1 2004/12/08 22:19:31 baallan Exp $ build without MPI";
#endif

#include <unistd.h>
#include <libgen.h>
#include <stdio.h>
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h> 
#include <stdPorts.h>
#endif

#include "stovepipe/stp.h"

#include "dc/framework/dc_fwkPublic.h"

#include "util/IO.h"


#include "dc/user_iface/CmdLineClient.h"
#include "dc/user_iface/ProgramSuffix.h"

#include "ExampleStaticFactory.h"

#include "util/freefree.h"

// for MPI_wrapper_HAS_COMM
#include "dc/user_iface/MPI_wrapper.h"

#include "util/freefree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef MPI_wrapper_HAS_COMM
/* It really rots that we have to consult an env var
 * in some systems, but what else can we do? ugh!
 * If ccafe-single: default mpi no
 * Else : default mpi yes
 * endif
 * Then modify according to flags:
 * env(CCAFE_USE_MPI)
 * if present
 *   if negative, mpi no
 *   if positive, mpi yes
 *   if unknown, whine and leave mpi as was.
 * endif
 * --ccafe-mpi value
 * if present (which pre-mpi_init is dicey to assume)
 *   if negative, mpi no.
 *   if positive, mpi yes.
 *   if unknown, whine and leave mpi as was.
 * endif
 */
static
bool CmdLineClientMain_tryMPI( runtype runType, const char *execName, int argc, char **argv )
{
  int pid = getpid();
  bool tryMPI = true;
  const char *usempi = getenv("CCAFE_USE_MPI");

  // check env
  if (runType == ONE_PROC_INTERACTIVE ) {
    tryMPI = false;
  }
  if (usempi != 0) {
    fprintf(stderr, "(%d) %s: found env(CCAFE_USE_MPI) = %s\n",pid, __FILE__,usempi);
    if (strcmp(usempi,"0") == 0 ||
        strcmp(usempi,"no") == 0 ||
        strcmp(usempi,"false") == 0
      ) {
      tryMPI = false;
    } 
    if (strcmp(usempi,"1") == 0 ||
        strcmp(usempi,"yes") == 0 ||
        strcmp(usempi,"mpi") == 0 ||
        strcmp(usempi,"true") == 0 ||
        strcmp(usempi,"") == 0
      ) {
      tryMPI = true;
    } 
  }
  // now, should cmdline override env?
  // that's a toughie, since argv is bogus on
  // some mpi implementations before mpiinit
  // (except on the head node where argv may be 
  // all the real argv not matching the pre-init
  // remote node argv's.)
  // Print it if we change it here so at least people
  // know what happened.
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i],"--ccafe-mpi") == 0) {
      int somethingSet = 0;
      if (i+1 < argc) {
        const char *mpival = argv[i+1];
        if (argv[i+1][0] == '-') {
          fprintf(stderr, "(%d) %s: --ccafe-mpi switchrequires a yes/no argument.\n",pid, __FILE__);
          continue;
        }
        if (strcmp(mpival,"0") == 0 ||
            strcmp(mpival,"no") == 0 ||
            strcmp(mpival,"false") == 0
           ) {
          tryMPI = false;
          somethingSet = 1;
          fprintf(stderr, "(%d) %s: Found --ccafe-mpi %s\n",pid, __FILE__, mpival);
        } 
        if (strcmp(mpival,"1") == 0 ||
            strcmp(mpival,"yes") == 0 ||
            strcmp(mpival,"true") == 0 ||
            strcmp(mpival,"mpi") == 0
           ) {
          tryMPI = true;
          somethingSet = 1;
          fprintf(stderr, "(%d) %s: Found --ccafe-mpi %s\n",pid, __FILE__, mpival);
        } 
        if (somethingSet == 0) {
          fprintf(stderr, "(%d) %s: Found --ccafe-mpi but '%s' given is invalid.\n",
			  pid, __FILE__, mpival);
        }
      } else {
        fprintf(stderr, "(%d) %s: --ccafe-mpi switchrequires a yes/no argument.\n",
		       pid,	__FILE__);
      } // end if enough args
    } // end if have switch
  } // end for

  return tryMPI;
}

static
void dumpargv(const int pid, char **argv, const int argc)
{
	// set 1 to 0 when unwanted
#if 0 // debug code, not dead code.
	for (int i = 0; i < argc; i++) {
		fprintf(stderr,"(%d) argv[%d] = %s\n",pid,i,argv[i]);
	}
#endif
}

static
void CmdLineClientMain_NotUseMPIMessage()
{
  int pid = getpid();
  fprintf(stderr, "(%d) %s: MPI_Init not called in ccafe-single mode.\n",pid,__FILE__);
  fprintf(stderr, "(%d) %s: Try running with ccafe-single --ccafe-mpi yes , or\n",pid,__FILE__);
  fprintf(stderr, "(%d) %s: try setenv CCAFE_USE_MPI 1 to force MPI_Init.\n",pid,__FILE__);
}

static
void CmdLineClientMain_UseMPIMessage(runtype runType, const char *execName)
{
  int pid = getpid();
  fprintf(stderr, "(%d) %s: execName is %s \n",pid,__FILE__,execName);
  fprintf(stderr, "(%d) %s: runType is ",pid,__FILE__);
  switch (runType) {
  case BATCH:
    fprintf(stderr, "BATCH\n");
    break;
  case CLIENT:
    fprintf(stderr, "CLIENT\n");
    break;
  case ONE_PROC_INTERACTIVE: 
    fprintf(stderr, "ONE_PROC_INTERACTIVE\n");
    break;
  case INTERACTIVE:
    fprintf(stderr, "INTERACTIVE\n");
    break;
  case GUI_INTERACTIVE:
    fprintf(stderr, "GUI_INTERACTIVE\n");
    break;
  case HUMANCLIENT:
    fprintf(stderr, "HUMANCLIENT\n");
    break;
  case SERVER:
    fprintf(stderr, "SERVER\n");
    break;
  default:
    fprintf(stderr, "unknown! (an error!)\n");
    break;
  }
  fprintf(stderr, "(%d) %s: If execName is unexpected, blame your MPI startup script.\n",pid, __FILE__);
  fprintf(stderr, "(%d) %s: If MPI_Init is unwanted, try adding the switch '--ccafe-mpi no' switch,\n",pid, __FILE__);
  fprintf(stderr, "(%d) %s: or try setenv CCAFE_USE_MPI 0 .\n",pid, __FILE__);
}
#endif //  mpi

int main(int argc, char **argv) {
  int size=-1,rank=-1;
  int pid = getpid();

  // this gets modified after mpi is determined.
  IO::initId(pid);

  /* Note:
   * We have to figure out whether we're a client, batch, single
   * before argv is available and before mpiinit is called,
   * because if we call mpiinit without actually being inside
   * an mpirun/mpiexec script, we may hang consuming cpu (for some
   * versions of mpi).
   * We have to do this on a best-effort basis due to the
   * differences in queue systems and mpi launches.
   * The action of the standard MPI_Init function is undefined
   * if the program is NOT launched in an mpi runtime.
   *
   * There may be some cases not handled properly in the first
   * pass at this logic.
   */
  runtype runType = CLIENT;
  char* execName = basename(argv[0]);
  std::string csingle = CCAFE_SINGLE;
  std::string cbatch = CCAFE_BATCH;
  csingle += CCAFE_PS;
  cbatch += CCAFE_PS;
  if( !strcmp(execName, csingle.c_str()) || 
      !strcmp(execName,CCAFE_SINGLE ) ) {
    runType = ONE_PROC_INTERACTIVE;
  }
  if(!strcmp(execName, cbatch.c_str()) || 
     !strcmp(execName, CCAFE_BATCH) ) {
    runType = BATCH;
  }


  CmdLineClient* cl = new CmdLineClient();
#ifdef MPI_wrapper_HAS_COMM
  char* buf = (char*) malloc(4096);
  memset(buf, 0, 4096);
  char* cwd = getcwd(buf, 4096);

  if (! CmdLineClientMain_tryMPI( runType, execName, argc, argv ) ) {
    cl->setUseMPI(false);
    CmdLineClientMain_NotUseMPIMessage();
  } else {
    cl->setUseMPI(true);
    CmdLineClientMain_UseMPIMessage(runType, execName);
    fprintf(stderr, "(%d) %s: MPI_Init being called.\n",pid,__FILE__);
    dumpargv(pid,argv,argc);
    MPI_Init(&argc,&argv);
    fprintf(stderr, "(%d) %s: MPI_Init succeeded.\n",pid,__FILE__);
    dumpargv(pid,argv,argc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
  }
  fprintf(stderr,"(%d) my rank: %d, my pid: %d\n", pid, rank, pid);
#endif




  cl->setRank(rank);
  cl->setSize(size);
  cl->setInitRunType(runType);
#ifdef MPI_wrapper_HAS_COMM
  char name[40];
  sprintf(name,"%d",rank);
  stp_init(argc, argv);
  if(runType != ONE_PROC_INTERACTIVE) {
    ::std::string ename;
    ::std::string fname;
    char *outDir;
    // Stuff learned the hard way: use of argc, argv must be done
    // *after* call to MPI_Init. unless lucky.
    if ( (outDir = (char *) stp_getn("ccafe", "outputdir")) != NULL ) {
      if(strlen(outDir) == 0) { // Option used but no value given
        fprintf(stderr, "(%d) %s: Option \"--ccafe-outputdir\" requires an argument"
         " continuing ...\n",pid, __FILE__);
        outDir = ".";
      }
      fname = outDir;
      ename = outDir;
      fname += "/pOut";
      ename += "/pErr";
      fname += name;
      ename += name;
    } else {
      fname = "pOut";
      ename = "pErr";
      fname += name;
      ename += name;
    }

    const char *remapStdio = 0;
    remapStdio = stp_getn("ccafe", "remap-stdio");
    if ( runType == BATCH && remapStdio == 0) {
	    // in the case of mpi present and
	    // batch mode, we don't know where
	    // stdio/stderr are or dare reopen them,
	    // unless the user tells us to.
      fprintf(stderr,"(%d) MapIOToFile(%s, %s)\n", 
              pid, fname.c_str(), ename.c_str());
      cl->mapIOToFile(fname.c_str(), ename.c_str());
      fprintf(stderr,"(%d) mapIOToFile done\n", pid);
    } else {
	    // we aren't batch or user gave --ccafe-remap-stdio
      fprintf(stderr,"(%d) MapEverythingToFile(%s, %s)\n", 
              pid, fname.c_str(), ename.c_str());
      cl->mapEverythingToFile(fname.c_str(), ename.c_str());
      fprintf(stderr,"(%d) mapEverythingToFile done\n", pid);
    }
  }
  if (size == 1) {
    IO::initId(-1);
    stp_putn("ccafe", "pwd", cwd);
  } else {
    IO::initId(rank);
  }
  IO::en("my rank: %d, my pid: %d", rank, pid);
  IO::pn("my rank: %d, my pid: %d", rank, pid); 
  fprintf(stderr,"my rank: %d, my pid: %d", rank, pid);
  cl->setName(name);
#else
  stp_init(argc, argv);
#endif
  ExampleStaticFactory es;
  cl->main(argc, argv, &es);
#ifdef MPI_wrapper_HAS_COMM
  if (cl->getUseMPI()) {
    fprintf(stderr, "(%d) %s: MPI_Finalize being called.\n", pid, __FILE__);
    MPI_Finalize();
    fprintf(stderr, "(%d) %s: MPI_Finalize succeeded.\n", pid, __FILE__);
		free(buf);
		buf = 0;
  }
#endif
  return 0;
}
