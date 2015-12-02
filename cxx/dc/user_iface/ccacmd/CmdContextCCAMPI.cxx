
#ifndef lint
static char id[]=
"$Id: CmdContextCCAMPI.cxx,v 1.16 2005/01/11 01:21:20 baallan Exp $";
#endif

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "dc/framework/dc_fwkPublic.h"

#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"
#include "dc/user_iface/ccacmd/CmdContextCCAMPI.h"
#include "stovepipe/stp.h"

#ifdef HAVE_LIBREADLINE
#include <stdio.h>
#include <unistd.h>
#ifdef HAVE_READLINE_READLINE_H
#include <readline/readline.h>
#else
#ifdef HAVE_READLINE_H
#include <readline.h>
#else
extern "C" char *readline(const char *);
#endif
#endif
#ifdef HAVE_READLINE_HISTORY
#ifdef HAVE_READLINE_HISTORY_H
#include <readline/history.h>
#else
#ifdef HAVE_HISTORY_H
#include <history.h>
#else
extern "C" void add_history(const char *);
#endif
#endif
#endif
#endif



#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "util/IO.h"
#include "util/freefree.h"

// instantiation of interpreters has specific details.
CmdContextCCAMPI::CmdContextCCAMPI(CmdLineBuilderView *bv_, DefaultBuilderModel* bm, bool batch_) : CmdContextCCA(bv_, bm) {
	batch = batch_;
	IO::en("CmdContextCCAMPI batch = %d",batch?1:0);
}

// Similar to above, uses a given input FILE argument, the FILE is
// expected to be line-buffered.
CmdContextCCAMPI::CmdContextCCAMPI(FILE* in_, CmdLineBuilderView *bv_, DefaultBuilderModel* bm, bool batch_) : CmdContextCCA(in_,bv_, bm) {
	batch = batch_;
}

CmdContextCCAMPI::~CmdContextCCAMPI() {
}

CFREE char *CmdContextCCAMPI::_readLine(int &readerr) {
  readerr=0;
  char *buf;
  buf = (char *)malloc(2049);
  assert(buf!=0);

  buf[0]='\0';
  buf[1]='\0';
  buf[2048] = '\0';
  // try opening the rc file once only.
  if (rcUnknown) {
    int rcExists = initRC();
    rcUnknown = 0;
    if (!rcExists) {
      IO::en("\nCmdContextCCAMPI::initRC: No rc file found. Pallet may be empty.");
    } else {
      IO::en("\nCmdContextCCAMPI::initRC: Found %s.", rcFileName);
    }
  } 
  // get a line from rc, please.
  int rcOk = 0;
  if (rc != 0) {
    rcOk = rcLine(buf,2048);
  } 
  // ran out of rc. back to reading the normal input.
  if (!rcOk) {
    if (batch) {
      // punt if we're not interactive
      if (IO::getId() != -1) {
         // it's -1 if we're mpisize 1, per inits in main().
         IO::pn("End of rc file in parallel np > 1 run. Exiting.");
         IO::en("End of rc file in parallel np > 1 run. Exiting.");
         return 0; 
         // return null string to signal end of program
         // because we're in non-interactive np > 1 scenario.
      }
    }
#ifdef HAVE_LIBREADLINE
    if (isatty(fileno(in))) {
      free(buf);
      buf = readline("cca>");
#ifdef HAVE_READLINE_HISTORY
      trim_blanks(buf);
      if (buf && buf[0]) { // don't add blank lines
	add_history(buf);
	return buf;		// avoid retrimming
      }
#endif
    }
    else {
#endif
      if (!fgets(buf,2048,in)) { // NULL return value means EOF or error
	free(buf);
	buf = 0;
      }
#ifdef HAVE_LIBREADLINE
    }
#endif
  }

  trim_blanks(buf);
  return buf;
}


 /** 
    In our version of readLine, we have overloaded to handle an rc file.
    We look for lines in files env(CCAFE_RC_FILE), env(HOME)/.ccaferc, and
    a compiled in path $(CCAFE_INSTALL_ROOT)/cxx/dc/user_iface/CcaffeineRC
    to return before we start parsing the regular input obtained from bv.
    The advisability of this on a global file system is not investigated here.
  */
int CmdContextCCAMPI::initRC() {
  const char * optionValue; // --ccafe-rc
  char *homedir; // ~/.ccaferc
  char *envrc; // CCAFE_RC_FILE env var or CCAFE_RC_FILE=arg option w/mpi
  char *defaultFile = _RCPATH; // _RCPATH given from makefile
  int prevError = 0;
  homedir = getenv("HOME");
  if (homedir !=  0) { homedir = STRDUP(homedir); }
  // in parallel with global fs, make this different on every node.
  envrc = getenv("CCAFE_RC_FILE"); 
  errno = 0;
  int myerr = 0;

  // --ccafe-rc option
  optionValue = stp_get("ccafe-rc");
  if (optionValue != 0  && rcFileName == 0) {
    // Rob's kludge for overcoming MPI chg-to-exec-dir: basically MPI
    // does a basename(argv[0]) to find the relative path to the
    // executable.  It then chdir()'s to that directory (!).  This
    // messes up the path for the user who may have provided command
    // line switches based on the CWD of the originating shell.  This
    // will assume that MPI has done so if the ccafe-pwd switch has
    // been used or implanted directly by the main program.
    const char* cwd = stp_getn("ccafe", "pwd");
    // BUG: Put real chdir() here
    // this only tests for the existence on a "RC" file.
    char* rcFilePath = NULL;
    if(
       (strncmp("/", optionValue, 1) != 0) && // does not begin with a `/'
       ((cwd != NULL) && (strlen(cwd) != 0)) // the option is valid.
      )
    {
      int siz = 4+strlen(cwd)+strlen(optionValue);
      rcFilePath = (char*)malloc(siz);
      memset(rcFilePath, 0, siz); // zero length string now
      rcFilePath = strcat(rcFilePath, cwd);
      rcFilePath = strcat(rcFilePath, "/");
      rcFilePath = strcat(rcFilePath, optionValue);
    } else {
      rcFilePath = STRDUP(optionValue);
    }
    // End Rob's kludge for overcoming MPI
    rc = fopen(rcFilePath,"r");
    myerr = errno;
    if (rc == 0 || badMagic(rc,rcFilePath)) {
      if (myerr != ENOENT && myerr != 0) {
        IO::en("CmdContextCCA::initRC: Error reading %s: %s(%d)",
               rcFilePath,strerror(errno),errno);
      }
      if (myerr == ENOENT ) {
        IO::en("CmdContextCCA::initRC: FileNotFound %s from --ccafe-rc.",
               rcFilePath);
      }
      free(rcFilePath);
      rcFilePath = 0;
      rc = 0;
      prevError=1;
    } else {
      rcFileName = rcFilePath;
    }
    myerr = 0;
  }

  // env or CCAFE_RC_FILE= option
  if (envrc != 0  && rcFileName == 0) {
    rc = fopen(envrc,"r");
    myerr = errno;
    if (rc == 0 || badMagic(rc,envrc)) {

      if (myerr != ENOENT && myerr != 0) {
        IO::en("CmdContextCCAMPI::initRC: Error reading %s: %s(%d)",
               envrc,strerror(myerr),myerr);
      }
      if (myerr == ENOENT ) {
        IO::en("CmdContextCCAMPI::initRC: FileNotFound %s from CCAFE_RC_FILE.",
               envrc);
      }
      rc = 0;
      prevError=1;
      myerr = 0;
    } else {
      if (prevError) {
        IO::en("CmdContextCCAMPI::initRC: Instead found bootstrap script %s from CCAFE_RC_FILE.",
               envrc);
      }
      rcFileName = STRDUP(envrc);
    }
  }

  // users .ccaferc
  if (homedir != 0  && rcFileName == 0) {
    char *homerc;
    int homercLen = strlen(homedir) + strlen(CCAFE_RC_NAME) 
                    + strlen(PATHSEP_STRING) +1;
    homerc = (char *)malloc(homercLen);
    sprintf(homerc,"%s%s%s",homedir,PATHSEP_STRING,CCAFE_RC_NAME);
    free(homedir);
    rc = fopen(homerc,"r");
    myerr = errno;
    if (rc == 0 || badMagic(rc,homerc)) {
      if (myerr != ENOENT && myerr != 0) {
        IO::en("CmdContextCCAMPI::initRC: Error reading %s: %s(%d)",
               homerc,strerror(myerr),myerr);
        free(homerc);
      }
      rc = 0;
    } else {
      if (prevError) {
        IO::en("CmdContextCCAMPI::initRC: Instead found bootstrap script %s.",
               homerc);
      }
      rcFileName = homerc;
    }
  }

  // backstop in the installed tree.
  if (rcFileName == 0) {
    rc = fopen(defaultFile,"r");
    myerr = errno;
    if (rc == 0 || badMagic(rc,defaultFile)) {
      if (myerr != ENOENT && myerr != 0) {
        IO::en("CmdContextCCAMPI::initRC: Error reading %s: %s(%d)",
               defaultFile,strerror(myerr),myerr);
      }
    } else {
      if (prevError) {
        IO::en("CmdContextCCAMPI::initRC: Instead found systemwide bootstrap script %s.",
               defaultFile);
      }
      rcFileName = STRDUP(defaultFile);
    }
  }


  if (rcFileName == 0) {
    return 0;
  }
  return 1;
  
}

