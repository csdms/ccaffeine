#ifndef lint
static char id[]=
"$Id: CmdLineClient.cxx,v 1.43 2008/08/05 19:24:24 baallan Exp $";
#endif


#include <unistd.h>
#include <stdio.h>
// For open():
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h> 
#include <stdPorts.h>
#endif 

#include <stdio.h>
#include <stdlib.h>

// this is just <getopt.h> under linux but we aren't linux always
// so include our own which is from the gnu distribution.
#include "gnu/getopt/getCCAFEopt.h" 

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdParse.h"
#include "dc/user_iface/BuilderController.h"


#include "dc/framework/dc_fwkPublic.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/BuilderModel.h"

#include "util/IO.h"

#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/CmdLineBuilderViewForHuman.h"
#include "dc/user_iface/CmdLineBuilderViewForGUI.h"
#include "dc/user_iface/CmdLineBuilderViewMux.h"

#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"
#include "dc/user_iface/ccacmd/CmdActionCCA.h"


#include "dc/user_iface/CmdLineBuilderController2.h"
#include "dc/distributed/ProcessorInfo.h"
#include "dc/distributed/ClientServerSocket.h"

#include "dc/user_iface/CmdLineClient.h"

#include "util/freefree.h"

#include "stovepipe/stp.h"

#include <sys/file.h>
#include <sys/types.h>
#ifdef CCAFE_SOCKETS
#include <sys/socket.h>
#endif // CCAFE_SOCKETS
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

/* A command line controller of the Model-View-Controller pattern for
  the builder.  This reads from input and instructs the BuilderModel
  to perform actions and the BuilderView to printout information. 

  This implementation encapsulates all the globals into a command
  context cc.
 */

/** a bit of opacity to hide jc++ from all comers. */
class MachWrapper
{
public:
  MachWrapper() { machines = 0; }
  ~MachWrapper() { machines = 0; }
  JCPN(Vector) *machines;

  /** Echos the processor file */
  void dumpProcTable(JCPN(ResourceHash)* procs) {
    JCPN(StringEnumeration)* k = procs->keys();
      while(k->hasMoreElements()) {
        char* p = (char*)k->nextElement();
        char* v = (char*)procs->get(p);
        IO::pn("proc: %s, type: %s", p, v);
      }
      delete k;
  }

  /** Find a ProcessorInfo* index into a JCPN(Vector)* keyed by the name field
      in the ProcessorInfo*. */
  int findProcInfoIndex(char *name, 
               /* vec of ProcessorInfo*'s*/ JCPN(Vector)* v ) {
    JCPN(Enumeration)* e = v->elements();
    while(e->hasMoreElements()) {
      ProcessorInfo* el = 
        dynamic_cast<ProcessorInfo*>(e->nextElement()); CHECKDC(el);
      if(strcmp(el->getName(), name) == 0) {
        int eindex =  v->indexOf(el);
        delete e;
        return eindex;
      }
    }
    delete e;
    return -1;
  }

/** Creates a vector of ProcessorInfo*'s parsed from a JCPN(StringHash)
    containing procNames and either "client" or "server" */
/* CDELETE */ JCPN(Vector)* getMachines(JCPN(ResourceHash)* procs) {
    JCPN(Vector)* v = new JCPN(Vector)();
    JCPN(StringEnumeration)* k = procs->keys();
    while(k->hasMoreElements()) {
      char* el = (char*)k->nextElement();
      char* type = (char*)procs->get(el); 
      boolean isServer;
      if(strcmp(type, "client") == 0) {
        isServer = FALSE;
      } else if(strcmp(type, "server") == 0) {
        isServer = TRUE;
      } else {
        IO::en("Got a different type other than \"client\" or \"server\"");
        IO::en("in file.  The type is: %s", type);
        return 0;
      }
      v->addElement(new ProcessorInfo(STRDUP(el), isServer));
    }    
    delete k;
    return v;
  }

};

int CmdLineClient::parse() {
  return controller->parse();
}

void CmdLineClient::mapIOToFile(const char* outName, const char* errName) {
  FILE* fp = 0;

  fp = fopen(outName, "w");
  if ( fp != NULL ) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setOut(fp);
  } else {
    int e1 = errno;
    const char *c1 = strerror(e1);
    fprintf(stderr, "  Unable to open %s (%s)\n",outName, c1);
  }
  fp = NULL;

  fp = fopen(errName, "w");
  if ( fp != NULL ) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setErr(fp);
  } else {
    int e2 = errno;
    const char *c2 = strerror(e2);
    fprintf(stderr, "  Unable to open %s (%s)\n",errName, c2);
  }
  fp = NULL;

}


void CmdLineClient::mapEverythingToTTY() {
  const char * name = "/dev/tty";
  struct stat buf;
	int myerrno;
  if(stat(name, &buf)) {
    perror("Cannot open tty for mapping IO");
    return;
  }
  int fdOut = open(name, O_WRONLY | O_CREAT | O_TRUNC, 
                   S_IRUSR | S_IWUSR | S_IRWXG | S_IROTH);
	myerrno = errno;
	if (fdOut < 0) {
    const char *c1 = strerror(errno);
    fprintf(stderr, "  Unable to open output tty (%s)\n",c1);
	}
  int fdErr = open(name, O_WRONLY | O_CREAT | O_TRUNC,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fdErr < 0) {
    const char *c2 = strerror(errno);
    fprintf(stderr, "  Unable to open error tty (%s)\n",c2);
	}
  close(1);  // close stdout
  close(2);  // close stderr
	int derr;
  derr = dup(fdOut); // make our file stdout
	if (derr < 0) {
    const char *c3 = strerror(errno);
    fprintf(stderr, "  Unable to dup out tty (%s)\n",c3);
	}
  derr = dup(fdErr); // make our file the stderr
	if (derr < 0) {
    const char *c4 = strerror(errno);
    fprintf(stderr, "  Unable to dup err tty (%s)\n",c4);
	}
  FILE* fp = fdopen(fdOut, "w"); //fopen(outName, "w");
  if (fp != NULL) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setOut(fp);
	} else {
    const char *c5 = strerror(errno);
    fprintf(stderr, "  Unable to fdopen out tty (%s)\n",c5);
	}
	fp = NULL;
  fp = fdopen(fdErr, "w"); //fopen(errName, "w");
  if (fp != NULL) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setErr(fp);
	} else {
    const char *c6 = strerror(errno);
    fprintf(stderr, "  Unable to fdopen out tty (%s)\n",c6);
	}
}


void CmdLineClient::mapEverythingToFile(const char* outName, const char* errName) {
  int pid = getpid();
  int e1;
  int e2;
  int fdOut = open(outName, O_WRONLY | O_CREAT | O_TRUNC, 
                   S_IRUSR | S_IWUSR | S_IRWXG | S_IROTH);
  e1 = errno;
  int fdErr = open(errName, O_WRONLY | O_CREAT | O_TRUNC,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  e2 = errno;
  if (fdOut == -1) {
    const char *c1 = strerror(e1);
    fprintf(stderr, "(%d)  Unable to open %s (%s)\n",pid,outName, c1);
  }
  if (fdErr == -1) {
    const char *c2 = strerror(e2);
    fprintf(stderr, "(%d)  Unable to open %s (%s)\n",pid,errName, c2);
  }
  close(1);  // close stdout
  close(2);  // close stderr
  int outdval = dup(fdOut); // make our file stdout
  int e3 = errno;
  int errdval = dup(fdErr); // make our file the stderr
  int e4 = errno;
  if (outdval == -1) {
    const char *c3 = strerror(e3);
    fprintf(stderr, "(%d)  Unable to dup %s (%s)\n",pid,outName, c3);
  }
  if (errdval == -1) {
    const char *c4 = strerror(e4);
    fprintf(stderr, "(%d)  Unable to dup %s (%s)\n",pid,errName, c4);
  }

  FILE* fp = fdopen(fdOut, "w"); //fopen(outName, "w");
  int e5 = errno;
  if (fp != NULL) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setOut(fp);
  } else {
    const char *c5 = strerror(e5);
    fprintf(stderr, " (%d) Unable to fdopen %s (%s)\n",pid,outName, c5);
  }
  fp = NULL;
  fp = fdopen(fdErr, "w"); //fopen(errName, "w");
  int e6 = errno;
  if (fp != NULL) {
    setvbuf(fp, 0, _IOLBF, BUFSIZ);
    IO::setErr(fp);
  } else {
    const char *c6 = strerror(e6);
    fprintf(stderr, "(%d)  Unable to fdopen %s (%s)\n",pid,errName, c6);
  }
  fp = NULL;
}

void CmdLineClient::remapIO() {
  char name[40];
  char fname[40];
  char ename[40];
  sprintf(name,"%d",rank);
  sprintf(fname, "procOut%d", rank);
  sprintf(ename, "procErr%d", rank);
  mapIOToFile(fname, ename);
}

extern "C" {
  extern int gdbWaitForAttach();
};

void CmdLineClient::parseArgsX(int argc, char** argv) {



  char* usage = "%s --name MyHostName [--file <filename>] "
    "[--type <client,interactive,gui,oneProcInteractive,server>] "
    "[--ccafe-waitForGdbAttach] "
    "[--port]"
    "[--ccafe-rc <rc file>]\n"
    "[--help]\n"
"  --type \n"
"       More below: \n"
" \n"
"  --type  client        \n"
"       This is the \"normal\" position, it listens for a \n"
"       connection, probably the GUI.  The backend right \n"
"       now, always behaves as a client. \n"
" \n"
"  --type  interactive   \n"
"       Same as client but interacts in human readable form, \n"
"       rather than the way the GUI would be expecting to \n"
"       interact. \n"
" \n"
"  --type gui            \n"
"        default behavior, expecting to talk to a GUI. \n"
" \n"
"  --type oneProcInteractive    \n"
"        Expects that there will be only one \n"
"        process and that it will be talking to a human \n"
"        being. \n"
"\n"
"  --port <number>  \n"
"        Port number to listen on, default host name is localhost. \n"
" \n"
"  --name <host>  \n"
"        Host other than localhost to connect to. \n"
" \n"
"  --file <configFile>   \n"
"        A processor config file for the processor map, \n"
"        not an initialization file. \n"
" \n"
"  --ccafe-waitForGdbAttach \n"
"        Spins until gdb attaches for debugging, probably not useful in \n"
"        a parallel environment; every process would have to \n"
"        be attached simultaneously.  \n"
" \n"
"  --ccafe-rc <rc file> \n"
"       Source the given file into ccaffeine.\n"
"\n"
"  --ccafe-outputdir <directory>\n"
"       Ccaffeine creates files that are tied off to each process's \n"
"       stdout and stderr.  This flag  causes those files to appear in the \n"
"       specified directory.\n"
" \n"
"  --ccafe-io2tty\n"
"       map stderr and stdout directly to the controlling terminal.  Useful\n"
"       if you can't figure out where the heck your output has gone to.\n"
"       May not be of much use for parallel runs and is invalid for\n"
"       ccafe-batch.\n"
" \n"
"  --ccafe-remap-stdio\n"
"       map stderr and stdout directly to the output files in batch mode.\n"
"       Useful only in batch mode with MPI when you are sure closing and\n"
"       reopening stdout/stderr is ok with your environment.\n"
" \n"
"  --help \n"
"       This message. \n"
;


  const char* procName;
  if((procName = stp_get("name")) != NULL) {
    if(strlen(procName)) {
      myProcName = STRDUP(procName);
    } else {
      IO::en("--file requires an argument\nexiting ...");
      IO::en(usage, "Ccaffeine");
      exit(-1);
    }
  }

  const char* file;
  if((file = stp_get("file")) != NULL) {
    if(strlen(file)) {
      procFile = STRDUP(file);
    } else {
      IO::en("--file requires an argument\nexiting ...");
      IO::en(usage, "Ccaffeine");
      exit(-1);
    }
  }

  const char* type;
  if((type = stp_get("type")) != NULL) {
    if(strcmp(type, "client") == 0) runType = CLIENT;
    else if(strcmp(type, "humanclient") == 0) runType = HUMANCLIENT;
    else if(strcmp(type, "interactive") == 0) runType = INTERACTIVE;
    else if(strcmp(type, "gui") == 0) runType = GUI_INTERACTIVE;
    else if(strcmp(type, "server") == 0) runType = SERVER;
    else if(strcmp(type, "oneProcInteractive") == 0) {
      runType = ONE_PROC_INTERACTIVE;
    }else{
      IO::en("--type takes one of \"client\", \"humanclient\","
             "\"interactive\", \"gui\", or \"oneProcInteractive\"");
      IO::en(usage, "Ccaffeine");
      exit(-1);
    } 
  }




 
  port = DEFAULTPORT;
  const char* portStr;
  if((portStr = stp_get("port")) != NULL) {
    if(strlen(portStr)) {
      port = atoi(portStr);
    } else {
      IO::en("--port requires an argument\nexiting ...");
      IO::en(usage, "Ccaffeine");
      exit(-1);
    }
  }

  const char* waitForGdbAttach;
  if((waitForGdbAttach = stp_getn("ccafe", "waitForGdbAttach")) != NULL) {
    gdbWaitForAttach();
  }

  if(stp_get("help") != NULL) {
    fprintf(stderr, usage, argv[0]);
    exit(0);
  }

}


void CmdLineClient::parseArgs(int argc, char** argv) {
  char* usage = "%s --name MyHostName [--file <filename>] [--type <client,interactive,gui,oneProcInteractive>] [--waitForGdbAttach]\n";

  char* theOption;
  port = DEFAULTPORT;

  // Set the gnu getopt facility to inhibit errors for unrecognized
  // Stovepipe options.
  CCAFEopterr = 0;

  if(argc == 1) {
    IO::pn("%s no arguments: I need at least a name", argv[0]);
    exit(-1);
  }
  int i;
  for (i=0; i<argc; i++) {
    IO::pn("arg%d: %s\n",i, argv[i]);
  }

  while (1)
    {
      int option_index = 0;
      static struct CCAFEoption long_options[] =
        {
          {"name", required_argument, 0, 0},
          {"file", required_argument, 0, 0},
          {"type", required_argument, 0, 0},
          {"waitForGdbAttach", no_argument, 0, 0},
          {"port", required_argument, 0, 0},
          {0, 0, 0, 0}
        };

      int c = getCCAFEopt_long (argc, argv, "nf",
                                long_options, &option_index);
      if (c == -1) {
        if(debug) {
          IO::pn("end of options\n");
        }
        break;
      }

      switch (c)
        {
        case 0: // opt_long --name, or --file or, whatever
          theOption = (char*)long_options[option_index].name;
          debug = true;
          if(debug) {
            IO::pn("option:%s\n", theOption);
            if (CCAFEoptarg) {
              IO::pn(" with arg %s", CCAFEoptarg);
            }
            IO::pn("\n");
          }
          break;
        default: // fell through to error.
          if(debug){
            IO::pn("non-ccaffeine option detected, that is OK.\n");
          }
        }
      if(strcmp(theOption, "name") == 0) {
        myProcName = STRDUP(CCAFEoptarg);
      } else if(strcmp(theOption, "file") == 0) {
        procFile = CCAFEoptarg;
      } else if(strcmp(theOption, "type") == 0) {
        char* type = CCAFEoptarg;
        if(strcmp(type, "client") == 0) runType = CLIENT;
        else if(strcmp(type, "humanclient") == 0) runType = HUMANCLIENT;
        else if(strcmp(type, "interactive") == 0) runType = INTERACTIVE;
        else if(strcmp(type, "gui") == 0) runType = GUI_INTERACTIVE;
        else if(strcmp(type, "oneProcInteractive") == 0) {
          runType = ONE_PROC_INTERACTIVE;
        }else{
          IO::en("--type takes one of \"client\", \"interactive\", or \"gui\"");
          IO::pn(usage, argv[0]);
          exit(-1);
        }

      } else if(strcmp(theOption, "port") == 0) {
        port = atoi(CCAFEoptarg);
        if((0 > port) || (port > 0xffff)) {
          IO::en("CmdLineClient::parseArgs: Bad value for port: %d", port);
          IO::en(usage, argv[0]);
          exit(-1);
        }
      } else if(strcmp(theOption, "waitForGdbAttach") == 0) {
        /** Do the wait immediately */
        gdbWaitForAttach(); /* returns when we are told to continue. */
      } else {
        // Used to be an error but now uses stovepipe.
      }
    }
}

void CmdLineClient::dumpMachines() {
    char * mess;
    JCPN(Enumeration)* e = mWrap->machines->elements();
    while(e->hasMoreElements()) {
      ProcessorInfo* pi = (ProcessorInfo*)e->nextElement();
      mess = pi->toString();
      IO::pn(mess);
      free(mess);
      mess = 0;
    }
    delete e;
    mess = ((ProcessorInfo*)(mWrap->machines->elementAt(myProcIndex)))->toString();
    IO::pn("My %s", mess);
    free(mess);
  }

#ifdef CCAFE_SOCKETS
/** Returns the ClientServerSocket for this configuration. */
/* CDELETE */ ClientServerSocket* CmdLineClient::setupSockets() {


    JCPN(ResourceHash)* procs = new JCPN(ResourceHash)(procFile);
    IO::pn("This is what the processor file looks like to me:");
    mWrap->dumpProcTable(procs);
    mWrap->machines = mWrap->getMachines(procs);
    if ( mWrap->machines  == 0) {
      IO::en("bad processor file");
      return 0;
    }
    myProcIndex = mWrap->findProcInfoIndex(myProcName, mWrap->machines);
    if(myProcIndex < 0) {
      IO::e("Hmmmmmmm.");
      IO::en("  I don't seem to be in the processor file machine list");
      IO::en("bailing ...");
      return 0;
    }

    // The resource hash now owns the key and value strings
    // stored in it (by copying inputs) so that we don't
    // have to clean procs out any more.
    delete procs;

    IO::pn("Here is the curent setup I am working on:");
    dumpMachines();
    

    ClientServerSocket* css = new ClientServerSocket(myProcIndex, 
                                                     port,
                                                     mWrap->machines);
    return css;
}
#endif // CCAFE_SOCKETS

void CmdLineClient::setInitRunType(runtype runType) {
  this->runType = runType;
}

void CmdLineClient::setSize(int size) {
  this->size = size;
}
void CmdLineClient::setRank(int rank) {
  this->rank = rank;
}

void CmdLineClient::setName(char *name) {
  myProcName = STRDUP(name);
}

CmdLineClient::CmdLineClient() {

  mWrap = new MachWrapper();
  useMPI = true;
  controller = 0;
  myProcName = 0;
  procFile = DEFAULTPROCFILEPATH;
  runType = CLIENT;
  debug = true;
  stp_initialized = false;
  fortranMPIComm = -1;
  hasComm = false;
}

CmdLineClient::~CmdLineClient() {
  delete controller;
  delete mWrap;
  controller = 0;
  mWrap = 0;
};

int CmdLineClient::main(int argc, char **argv, StaticFactory *sf) {


  parseArgsX(argc, argv);



  if (size == 1) {
    IO::initId(-1);
  } else {
    IO::initId(rank);
  }
  if(myProcName == 0) {
    // Most likely the procName could not be set because we are running MPI.
    IO::pn("my rank: %d, my pid: %d", rank, getpid()); 
    char name[400];
    sprintf(name, "%d", rank);
    setName(name);
  }
  switch(runType) {
  case SERVER:
#ifdef CCAFE_SOCKETS
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 1
      }

      IO::pn("Type: Server");

      // Now do the socket setup.
      struct sockaddr_in from, sin;
      memset(&sin, 0, sizeof(sin));
      memset(&from, 0, sizeof(from));
      // We overload the meaning of port to be the port we listen to
      // for a connection.
      sin.sin_port = htons(port);


      int t = socket(AF_INET, SOCK_STREAM, 0);

      // Tell the kernel that we do not want it to prohibit reuse of
      // this port (addr) for a while after an abnormal termination.
      {
	int val = 1;
	struct linger l;
	l.l_onoff = 0;
	l.l_linger = 0;
	
	setsockopt(t, SOL_SOCKET, SO_LINGER, &l, sizeof(struct linger));
	setsockopt(t, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
      }

      if(bind(t, (const sockaddr*)&sin, sizeof(sin))) { 
        perror("ClientServerSocket::acceptConnections");
        IO::en("bind: network problem");
        return -4;
      }
      int backlog = 1;
      listen(t, backlog);
      socklen_t len = sizeof(from);
#if __linux
 // this block shouldn't be needed with the change to socklen_t.
      int s = accept(t, (sockaddr*)&from, (unsigned int *)&len);
#else
      int s = accept(t, (sockaddr*)&from, &len);
#endif
      FILE* in = fdopen(s, "r");
      FILE* out = fdopen(s, "w");
      /*CDELETE*/  CmdLineBuilderView* bv1 = (CmdLineBuilderView *)
        new CmdLineBuilderViewForGUI();
      bv1->setOutputStream(out);
      int err;
      /* CDELETE */ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
           "CmdLineClient::main, bailing ...");
      }
      bv1->setBuilderModel(bm);
  
      void *bvv= 0;
      bvv = static_cast<void *>(bv1);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);


      controller = new CmdLineBuilderController2(in, bv1, bm);

      IO::pn("CmdLineClient parsing ...");
      controller->parse();

      delete controller;
      delete bv1;
    }
#else //  CCAFE_SOCKETS server
    IO::pn("Type: Server");
    IO::en("Type: Server");
    IO::en("Socket features not enabled in this ccaffeine build.");
    IO::en("Add --enable-sockets if sockets supported on your platform.");
#endif // CCAFE_SOCKETS server
    break;
  case CLIENT:
#ifdef CCAFE_SOCKETS
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 2
      }
      IO::pn("Type: Client");
      ClientServerSocket* css = setupSockets();
      if(css == 0) {
        IO::en("failed to create sockets");
        exit(-1);
      }
      if(css->isServer()) {
        IO::en("The configuration claims that I am a server, ");
        IO::en("don't know how to do that ...\nbailing ...");
        exit(-1);
      }
      if(css->makeConnection() < 0) {  //physically make the socket connections
         IO::en("An error occurred in making the socket connections:");
         IO::en("bailing ...");
         exit(-1);
      }
      int size;
      FILE** outGuy = css->getOut(size);
      FILE* out = outGuy[0];
      FILE** inGuy = css->getIn(size);
      FILE* in = inGuy[0];


      CmdLineBuilderView* bv1 = 0;
      bv1 =  new CmdLineBuilderViewForGUI();
      bv1->setOutputStream(out);
      CmdLineBuilderView* bv2 = 0;
      bv2 = (CmdLineBuilderView *) new CmdLineBuilderViewForGUI();
      bv2->setOutputStream(IO::getErr());
      CmdLineBuilderViewMux* mux = new CmdLineBuilderViewMux();
      CmdLineBuilderView_shared sbv1(bv1);
      CmdLineBuilderView_shared sbv2(bv2);
      mux->addCLBV(sbv1);
      mux->addCLBV(sbv2);
      bv1 = 0; // handed off to muxer permanently.
      bv2 = 0; // handed off to muxer permanently.

      int err;
      /* CDELETE */ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
           "CmdLineClient::main, bailing ...");
      }
      mux->setBuilderModel(bm);
  

      void *bvv= 0;
      bvv = static_cast<void *>(mux);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);

      controller = new CmdLineBuilderController2(in, mux, bm);

      IO::pn("CmdLineClient parsing ...");
      controller->parse();

      delete controller;
      delete css;
      delete mux;
    }
#else //  CCAFE_SOCKETS client
    IO::pn("Type: Client");
    IO::en("Type: Client");
    IO::en("Socket features not enabled in this ccaffeine build.");
    IO::en("Add --enable-sockets if sockets supported on your platform.");
#endif // CCAFE_SOCKETS client
    break;
  case HUMANCLIENT:
#ifdef CCAFE_SOCKETS
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 3
      }
      // Even though we have a human client, we may be one of many remapIO
      IO::pn("Type: Human Client");
      ClientServerSocket* css = setupSockets();
      if(css == 0) {
        IO::en("failed to create sockets");
        exit(-1);
      }
      if(css->isServer()) {
        IO::en("The configuration claims that I am a server, ");
        IO::en("don't know how to do that ...\nbailing ...");
        exit(-1);
      }
      if(css->makeConnection() < 0) {  //physically make the socket connections
        IO::en("An error occurred in making the socket connections:");
        IO::en("bailing ...");
        exit(-1);
      }
      int size;
      FILE** outGuy = css->getOut(size);
      FILE* out = outGuy[0];
      FILE** inGuy = css->getIn(size);
      FILE* in = inGuy[0];


      /*CDELETE*/ CmdLineBuilderView* bv1 = (CmdLineBuilderView *)
        new CmdLineBuilderViewForHuman();
      bv1->setOutputStream(out);
      /*CDELETE*/ CmdLineBuilderView* bv2 = (CmdLineBuilderView *)
        new CmdLineBuilderViewForHuman();
      bv2->setOutputStream(IO::getOut());
      CmdLineBuilderViewMux* mux = new CmdLineBuilderViewMux();
      CmdLineBuilderView_shared sbv1(bv1);
      CmdLineBuilderView_shared sbv2(bv2);
      mux->addCLBV(sbv1);
      mux->addCLBV(sbv2);
      bv1 = 0; // now muxers delete.
      bv2 = 0; // now muxers delete.

      int err;
      /*CDELETE*/ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
               "CmdLineClient::main, bailing ...");
      }
      mux->setBuilderModel(bm);

      void *bvv= 0;
      bvv = static_cast<void *>(mux);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);

      controller = new CmdLineBuilderController2(in, mux, bm);

      IO::pn("CmdLineClient parsing ...");
      controller->parse();

      delete controller;
      delete css;
      delete mux;
    }
#else //  CCAFE_SOCKETS client
    IO::pn("Type: Human Client");
    IO::en("Type: Human Client");
    IO::en("Socket features not enabled in this ccaffeine build.");
    IO::en("Add --enable-sockets if sockets supported on your platform.");
#endif // CCAFE_SOCKETS
    break;
  case INTERACTIVE:
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 4
      }
      IO::pn("Type: Interactive");
      /*CDELETE*/ CmdLineBuilderView *bv = (CmdLineBuilderView *)
        new CmdLineBuilderViewForHuman();
      bv->setOutputStream(IO::getOut());

      int err;
      /*CDELETE*/ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
               "CmdLineClient::main, bailing ...");
      }
      bv->setBuilderModel(bm);

      void *bvv= 0;
      bvv = static_cast<void *>(bv);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);

      controller = new CmdLineBuilderController2(IO::getIn(), bv, bm);

      int res = controller->parse();

      delete controller;
      delete bv;
      return res;
    }
    break;
  case ONE_PROC_INTERACTIVE:
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 5
      }
      IO::pn("Type: One Processor Interactive");
      /*CDELETE*/ CmdLineBuilderView *bv = (CmdLineBuilderView *)
        new CmdLineBuilderViewForHuman();
      bv->setOutputStream(stdout);

      int err;
      /*CDELETE*/ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm, hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
               "CmdLineClient::main, bailing ...");
        exit(-1);
      }
      bv->setBuilderModel(bm);

      void *bvv= 0;
      bvv = static_cast<void *>(bv);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);


      controller = new CmdLineBuilderController2(stdin, bv, bm);

      int res = controller->parse();

      delete controller;
      delete bv;
      return res;
      break;
    }
  case BATCH:
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        IO::pn("--ccafe-io2tty has been detected: this *never* "
               "makes sense for batch mode, ignoring ...");
      }
      IO::pn("Type: BATCH");
      /*CDELETE*/ CmdLineBuilderView *bv = (CmdLineBuilderView *)
        new CmdLineBuilderViewForHuman();
      bv->setOutputStream(IO::getOut());

      int err;
      /*CDELETE*/ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
               "CmdLineClient::main, bailing ...");
        exit(-1);
      }
      bv->setBuilderModel(bm);

      void *bvv= 0;
      bvv = static_cast<void *>(bv);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);

      controller = new CmdLineBuilderController2(IO::getIn(), bv, bm);

      int res = controller->parse();

      delete controller;
      delete bv;
      return res;
      break;
    }
  case GUI_INTERACTIVE:
    {
      if(stp_getn("ccafe", "io2tty") != NULL) {
        mapEverythingToTTY(); // 6
      }
      IO::pn("Type: GUI Interactive");
      /*CDELETE*/ CmdLineBuilderView *bv = (CmdLineBuilderView *)
        new CmdLineBuilderViewForGUI();
      bv->setOutputStream(IO::getOut());
      // omit builderviewmuxing

      int err;
      /*CDELETE*/ DefaultBuilderModel* bm = new DefaultBuilderModel(err, sf, fortranMPIComm,hasComm);
      if(err) {
        IO::en(":-( Could not create DefaultBuilderModel in "
               "CmdLineClient::main, bailing ...");
      }
      bv->setBuilderModel(bm);

      void *bvv= 0;
      bvv = static_cast<void *>(bv);
      bm->getFramework()->putFrameItem("CmdLineBuilderView", bvv);


      controller = new CmdLineBuilderController2(IO::getIn(), bv, bm);

      int res = controller->parse();

      delete controller;
      delete bv;
      return res;
    }
    break;
  default:
    break;
  }
  return -1;
}

void CmdLineClient::setComm(int64_t fComm)
{
	IO_dn2("CmdLineClient::setComm(%d)",(int)fComm);
	fortranMPIComm = fComm;
	hasComm = true;
}

void CmdLineClient::setUseMPI(bool b)
{
  useMPI = b;
}

bool CmdLineClient::getUseMPI()
{
  return useMPI;
}
