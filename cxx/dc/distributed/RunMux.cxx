#include <unistd.h>
#include <errno.h>
#include <gnu/getopt/getCCAFEopt.h>
#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "util/IO.h"
#include "ProcessorInfo.h"
#include "ConnectionManager.h"
#include "SocketConnectionManager.h"
#include "ClientInterfaces.h"
#include "DataCollectorFactory.h"
#include "ServerMux.h"
//#include "RunMux.h"

#define DEFAULTPORT 3141
#define DEFAULTNEXTPORT 3142
#define DEFAULT_PROCFILE_NAME "processors"

#ifndef Driver_RunMux

#else

extern char *usage;
class RunMux {
public:


  /** Find a ProcessorInfo* index into a JCPN(Vector)* keyed by the name field
    in the ProcessorInfo*. */
  int RunMux::findProcInfoIndex(char *name, 
			/* vec of ProcessorInfo*'s*/ JCPN(Vector)* v ) {
    JCPN(Enumeration)* e = v->elements();
    while(e->hasMoreElements()) {
      ProcessorInfo* el = 
	dynamic_cast<ProcessorInfo*>(e->nextElement()); CHECKDC(el);
      if(strcmp(el->getName(), name) == 0) return v->indexOf(el);
    }
    delete e;
    return -1;
  }

  /** Creates a vector of ProcessorInfo*'s parsed from a JCPN(StringHash)
    containing procNames and either "client" or "server" */
  CDELETE JCPN(Vector)* 
  RunMux::getMachines(JCPN(ResourceHash)* procs) {
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

  /** Echos the processor file */
  void RunMux::dumpProcTable(JCPN(ResourceHash)* procs) {
    JCPN(StringEnumeration)* k = procs->keys();
    while(k->hasMoreElements()) {
      char* p = (char*)k->nextElement();
      char* v = (char*)procs->get(p);
      IO::pn("proc: %s, type: %s", p, v);
    }
  }

  void RunMux::dumpMachines(JCPN(Vector)* machines, int myProcIndex) {
    JCPN(Enumeration)* e = machines->elements();
    while(e->hasMoreElements()) {
      ProcessorInfo* pi = (ProcessorInfo*)e->nextElement();
      IO::pn(pi->toString());
    }
    delete e;
    IO::pn("My %s", 
           ((ProcessorInfo*)machines->elementAt(myProcIndex))->toString());
  }

  CDELETE ConnectionManager* RunMux::getConnectionManagerFromFile (
							   char* procFile, 
							   char* name,
							   int port
							   )
  {
    JCPN(Vector)* machines;
    int myProcIndex = 0;
  
    // read the config (processors) file
    JCPN(ResourceHash)* procs = new JCPN(ResourceHash)(procFile);
    IO::pn("This is what the processor file looks like to me:");
    dumpProcTable(procs);
    if((machines = getMachines(procs)) == 0) {
      IO::en("bad processor file");
      return 0;
    }
    myProcIndex = findProcInfoIndex(name, machines);
    if(myProcIndex < 0) {
      IO::e("Hmmmmmmm.");
      IO::en("  I don't seem to be in the processor file machine list");
      IO::en("bailing ...");
      return 0;
    }
  
    delete procs;

    IO::pn("Here is the current setup I am working on:");
    dumpMachines(machines, myProcIndex);

    // actually make the connection manager
    SocketConnectionManager* scmClients = new SocketConnectionManager(myProcIndex, 
								      port,
								      machines);
    // more cleanup
    delete machines;
  
    // wait for connections
    int error = scmClients->makeConnection(0);
    if (error == 0)
      {
	return scmClients;
      }
    else 
      {
	perror("Could not make connections to clients");
	return NULL;
      }
  }  


  int RunMux::run(char* procFile, char* name, int port, char* nextServerName, int nextMachinePort)
  {
    // fix up all the arguments if they weren't set properly
    if (port == 0)
      port = DEFAULTPORT;
    if (nextMachinePort == 0)
      nextMachinePort = DEFAULTNEXTPORT;
    if (strlen(name) == 0) {
      printf("Bad option: %s\n", "name");
      printf("%s\n", usage);
      exit(-1);
    }
    if (strlen(procFile) == 0)
      procFile = DEFAULT_PROCFILE_NAME;

  // create the connection managers
    IO::pn("The client connection is being run as a server "
	   "at port %i", port);
    ConnectionManager* cmClients = getConnectionManagerFromFile(procFile, 
								name, port);

    if (!cmClients) {
      IO::en("No client connection, exiting");
      exit(-1);
    }

  // BUGBUG - make this take a config (processors) file as well?
    SocketConnectionManager* scmController = NULL;
    if (strlen(nextServerName) != 0) {
      IO::pn("The controller connection is being run as a client of machine %s"
	     " at port %i", nextServerName, nextMachinePort);
      scmController = new SocketConnectionManager(nextMachinePort,
						  nextServerName
						  );
    } else {
      IO::pn("The controller connection is being run as a server "
	     "at port %i", nextMachinePort);
      scmController = new SocketConnectionManager(nextMachinePort, 
						  1);
    }

    int error = scmController->makeConnection(0);
    if (error != 0) {
      perror("Could not make connection to controller\n");
      return error;
    }


    // set up the server mux using the connections created above
    if(cmClients->isServer()) {
      //signal(SIGPIPE, &pipeSignal); // disable signals on pipe disconnect
    
      Connection* connect = dynamic_cast<Connection*> (scmController->getConnections()->elementAt(0));
      ServerMux mux(cmClients, connect);
    
      // start up the necessary threads
      mux.doClientIO();
      IOThread scmIO(scmController);
      scmIO.start();
      ConnectThread scmConn(scmController);
      scmConn.start();
      printf("Started server multiplexor\n");
      mux.join();
      scmController->shutdown();

    } else {
      printf("Put an error message here!\n");
    }
    if (scmController)
      delete scmController;
    if (cmClients)
      delete cmClients;

    return 0;
  }

};

//define Driver_RunMux
extern char *usage;
char* usage = "RunMux --name MyHostName [--file <filename>] "
"[--port <portNum>] [--nextMachinePort <portNum>] "
"[--nextServerName <nextHostName>]\n";

int main (int argc, char** argv)
{

  // variables for the passed in args
  int port = 0;
  int nextMachinePort = 0;
  JCPN(StringJC) name, procFile, nextServerName;
  char* theOption;


  // parse the args
  while (1) {
    int option_index = 0;
    static struct CCAFEoption long_options[] =
    {
      {"name", required_argument, 0, 0},
      {"file", required_argument, 0, 0},
      {"port", required_argument, 0, 0},
      {"nextMachinePort", required_argument, 0, 0},
      {"nextServerName", required_argument, 0, 0},
      {0, 0, 0, 0}
    };
    
    //optstring: p:(port)n:(name)f:(proc file)s:(next server name)c:(client port)
    int c = getCCAFEopt_long (argc, argv, "n:f:p:m:s:",
			 long_options, &option_index);
    if (c == -1) {
      break;
    }
    switch (c)
      {
      case 0:
	theOption = (char*)long_options[option_index].name;
	printf("option:%s\n", theOption);
	if (CCAFEoptarg)
	  printf (" with arg %s", CCAFEoptarg);
	printf ("\n");
	break;
      default:
	printf("%s\n", usage);
	exit(-1);
      }
    if(strcmp(theOption, "name") == 0) {
      name.append(CCAFEoptarg);
    } else if(strcmp(theOption, "file") == 0) {
      procFile.append(CCAFEoptarg);
    } else if(strcmp(theOption, "port") == 0) {
      port = atoi(CCAFEoptarg);
    } else if(strcmp(theOption, "nextMachinePort") == 0) {
      nextMachinePort = atoi(CCAFEoptarg);
    } else if(strcmp(theOption, "nextServerName") == 0) {
      nextServerName.append(CCAFEoptarg);
    } else {
      printf("Bad option: %s\n", theOption);
      printf("%s\n", usage);
      exit(-1);
    }
  }

  RunMux rm;
  rm.run(procFile.getBuffer(), name.getBuffer(), port, 
	  nextServerName.getBuffer(), nextMachinePort);
}
#endif // Driver_RunMux




