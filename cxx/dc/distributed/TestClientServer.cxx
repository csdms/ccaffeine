#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: TestClientServer.cxx,v 1.8 2005/08/24 21:26:38 baallan Exp $";
} ENDSEMI
#include <unistd.h>
#include <gnu/getopt/getCCAFEopt.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "jc++/lang/Object.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "jc++/lang/String.hh"
#include "util/IO.h"
#include "ProcessorInfo.h"
#include "ClientServerSocket.h"
#include "jc++/io/Reader.h"
#include "jc++/io/Writer.h"
#include "jc++/io/BufferedReader.h"
#include "jc++/io/StdReader.h"
#include "jc++/io/StdWriter.h"
#include "jc++/io/BufferedReader.h"
#include "ConnectionManager.h"
#include "SocketConnectionManager.h"
#include "RunProcess.h"
#include "ClientInterfaces.h"
#include "LinewiseClient.h"
#include "SingleClientDataCollector.h"
#include "DataCollectorFactory.h"
#include "StaticIOConnection.h"
#include "MessageData.h"
#include "ServerMux.h"


#include "util/freefree.h"

#define DEFAULTPORT 3141
#define DEFAULTPROCFILEPATH "processors"


class TestNotify : public ConnectCallback {
public:
  virtual void connected(Connection* connect) 
  {
    JCPN(Writer)* out = connect->getOut();
    for(int i = 0;i < 5;i++) {
      char str[64];
      sprintf (str, "Here is line #%d\n", i);
      out->write(str);
    }
    JCPN(BufferedReader)* in = new JCPN(BufferedReader)(connect->getIn());
    char* str;
    for(int i = 0;i < 5;i++) {
      if((str = in->readLine()) == 0) break;
      IO::pn("Output from client: %s", str);
    }
    free(str);
    delete in;
    connect->disconnect();
  };
  virtual void disconnected(Connection* connection) {};

};

class ReadNotify : public ReadCallback {

public:
  void readReady(Connection* connect) {
      JCPN(BufferedReader)* in = new JCPN(BufferedReader)(connect->getIn());
      JCPN(Writer)* out = connect->getOut();
      char* str;
      while((str = in->readLine()) != 0)
	{
	  IO::pn("Output to client: %s", str);
	  out->write("client recieved:");
	  out->write(str);
	  out->write("\n");
	  out->flush();
	}
      //errors:
      // EAGAIN : no more data, try another select
      // EINTR : signal recieved, try again
      // try again

      // EPIPE : the socket is gone
      // EIO, EISDIR, EBADF, EINVAL, EFAULT etc - fd is unusable for
      // some reason, must be recreated before it can be used
      // do shutdown code, exit, and wait for the user to start us up 
      // again
      perror("Finished reading with error: ");
      IO::pn("Output from client finished\n");
      if ((!(errno == EAGAIN))/* || (errno == EINTR) || (errno == 0)*/) {
	exit(-1);
      }

      free(str);
      return;
  }
};

void pipeSignal(int data) { printf("SIGHNDLR: got a pipe broken signal with data %x\n", data); };

class TestThread :public CCAFEThread {
private:
  ConnectionManager* manager;
  boolean running;
public:
  TestThread(ConnectionManager* manager) {this->manager = manager; running = TRUE; };
  void* run() 
  {
     while (1) {
      manager->notifyReads();
    }
     return NULL;
  };
};
class TestClientServer {
private:

  char* procFile;
  int buflen;
  boolean isServer;
  int myProcIndex;
  JCPN(Vector)* machines;

public:

  TestClientServer() {
    procFile = DEFAULTPROCFILEPATH;
    buflen = BUFSIZ;
  }
  /** Run the client side, return < 0 is an error.*/
  int doTest0(char* name, char* fileName) {
    printf("doing test0\n");
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

    // What a mess! Getrid of memory. 
    JCPN(StringEnumeration)* e = procs->keys();
    while(e->hasMoreElements()) {
      char* key = (char*)e->nextElement();
      free((char*)procs->get(key));
      key = 0;
    }
    delete e;
    delete procs;

    IO::pn("Here is the curent setup I am working on:");
    dumpMachines();
    
    SocketConnectionManager* css = new SocketConnectionManager(myProcIndex, 
						     DEFAULTPORT,
						     machines);
    css->makeConnection(0);
    if(css->isServer()) {
      Connection* connect = dynamic_cast<Connection*> (css->getConnections()->elementAt(0)); CHECKDC(connect);
      JCPN(BufferedReader)* in = new JCPN(BufferedReader)(connect->getIn());
      int siz = 1024;
      char* str = (char*)malloc(siz);
      for(int i = 0;i < 5;i++) {
	if((str = in->readLine()) == 0) break;
	IO::pn("Output from client: %s", str);
      }
      free(str);
      JCPN(Writer)* out = connect->getOut();
      for(int i = 0;i < 5;i++) {
	char str[64];
	sprintf (str, "Here is line #%d\n", i);
	out->write(str);
      }
      TestNotify notif;
      connect->setConnectCallback (&notif);
      connect->disconnect();
      css->notifyReconnect();
    } else {
      Connection* connect = dynamic_cast<Connection*> (css->getConnections()->elementAt(0)); CHECKDC(connect);
      JCPN(Writer)* out = connect->getOut();
      for(int i = 0;i < 5;i++) {
	char str[64];
	sprintf (str, "Here is line #%d\n", i);
	out->write(str);
      }
      JCPN(BufferedReader)* in = new JCPN(BufferedReader)(connect->getIn());
      int siz = 1024;
      char* str = (char*)malloc(siz);
      for(int i = 0;i < 5;i++) {
      if((str = in->readLine()) == 0) break;
	IO::pn("Output from server: %s", str);
      }
      free(str);
      delete in;
    }
    delete css;
      return 0;
  }



  /** Test out the LinewiseClient class*/
  int doTest2(char* name, char* fileName) {
    printf("doing test0\n");
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

    // What a mess! Getrid of memory. 
    JCPN(StringEnumeration)* e = procs->keys();
    while(e->hasMoreElements()) {
      char* key = (char*)e->nextElement();
      free((char*)procs->get(key));
      key = 0;
    }
    delete e;
    delete procs;

    IO::pn("Here is the current setup I am working on:");
    dumpMachines();
    
    SocketConnectionManager* css = new SocketConnectionManager(myProcIndex, 
						     DEFAULTPORT,
						     machines);
    css->makeConnection(0);
    if(css->isServer()) {
      signal(SIGPIPE, &pipeSignal);
      Connection* connect = dynamic_cast<Connection*> (css->getConnections()->elementAt(0)); CHECKDC(connect);
      CCAFEThreadPool threadpool(2);
      LinewiseClient client(connect, &threadpool);
      connect->setReadCallback(&client);
      TestThread thread(css);
      thread.start();
      JCPN(Writer)* out = connect->getOut();
      for(int i = 0;i < 5;i++) {
	char str[64];
	sprintf (str, "Here is line #%d\n", i);
	client.write(str);
      }
      connect->setConnectCallback (&client);
      //      connect->disconnect();
      css->notifyReconnect();
    } else {
      Connection* connect = dynamic_cast<Connection*> (css->getConnections()->elementAt(0)); CHECKDC(connect);
      JCPN(BufferedReader)* in = new JCPN(BufferedReader)(connect->getIn());
      char* str;
      for(int i = 0;i < 5;i++) {
      if((str = in->readLine()) == 0) continue;
	IO::pn("Output from server: %s", str);
      }
      JCPN(Writer)* out = connect->getOut();
      char instr[256];
      fgets (instr, 256, stdin);
      while(strcmp(instr, "exit\n")) {
	out->write(instr);
	printf("wrote string %s", instr);
	fgets (instr, 256, stdin);
      }
      free(str);
      delete in;
      connect->disconnect();
      connect->shutdown();
      css->shutdown();
    }
    delete css;
      return 0;
  }



  int doTest4(char* procName, int port) {
    //RunProcess main(procName, port);
    while(1);
    return 0;
  }
  int doTest5(char* procName, int port) {
    SocketConnectionManager* sockets = new SocketConnectionManager(port, procName); // we want 1 client for now
    sockets->makeConnection(0);
    if (sockets->isServer())
      printf("Should not be a server\n");
 
    CCAFEThreadSafeQueue* connections = sockets->getConnections();
    if (!connections)
      printf("Could not get connections\n");
    SocketConnection* connection = dynamic_cast<SocketConnection*> (connections->elementAt(0)); CHECKDC(connection);
    JCPN(BufferedReader)* reader = new JCPN(BufferedReader)(connection->getIn());
    JCPN(Writer)* writer = connection->getOut();
    int siz = 1024;
    char* str = (char*)malloc(siz);
    for(int i = 0;i < 5;i++) {
      if(fgets(str, siz, stdin) == NULL) break;
      IO::pn("Input: %s", str);
      writer->write(str);
      char* tempstr;
      for(int i = 0;i < 5;i++) {
	if((tempstr = reader->readLine()) == 0) continue;
	IO::pn("Output from client: %s", tempstr);
      }
    }
    free(str);
    delete reader;
    return 0;
  }
  /** Run the client side, return < 0 is an error.*/
  int doTest1(char* name, char* fileName) {
    printf("doing test0\n");
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

    // What a mess! Getrid of memory. 
    JCPN(StringEnumeration)* e = procs->keys();
    while(e->hasMoreElements()) {
      char* key = (char*)e->nextElement();
      free((char*)procs->get(key));
      key = 0;
    }
    delete e;
    delete procs;

    IO::pn("Here is the curent setup I am working on:");
    dumpMachines();
    
    ClientServerSocket* css = new ClientServerSocket(myProcIndex, 
						     DEFAULTPORT,
						     machines);
    css->makeConnection();
    int size;
    if(css->isServer()) {
      FILE** in = css->getIn(size);
      int siz = 1024;
      char* str = (char*)malloc(siz);
      for(int i = 0;i < 5;i++) {
	if(fgets(str, siz, in[0]) == NULL) break;
	IO::pn("Output from client: %s", str);
      }
      free(str);
      FILE** out = css->getOut(size);
      for(int i = 0;i < 5;i++) {
	fprintf(out[0], "Here is line #%d\n", i);
      }
      fclose(out[0]);
      fclose(in[0]);
    } else {
      FILE** out = css->getOut(size);
      FILE** in = css->getIn(size);
      int siz = 1024;
      char* str = (char*)malloc(siz);

      int err = dup2(out[0]->_fileno, stdout->_fileno); // attempt to pipe stdout to the socket BUGBUG: _fileno probably not portable - is there a macro?
      if (err < 0)
	fprintf(stdout, "error is: %s\n", strerror (errno));
      while(fgets(str, siz, in[0]) != NULL){
	IO::en("Output from server: %s", str);
	if (str[0] == '#')
	  continue;
	printf("Got message: %s \n#END_OF_MESSAGE\n", str);
      }
      free(str);
      fclose(out[0]);
      fclose(in[0]);
    }
      return 0;
  }
  /** Creates a vector of ProcessorInfo*'s parsed from a JCPN(StringHash)
    containing procNames and either "client" or "server" */
  CDELETE JCPN(Vector)* getMachines(JCPN(ResourceHash)* procs) {
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
  
  int TestHashTable() {
    JCPN(Hashtable) table;
    StringJC string1("SingleClientDataCollector");
    CollectorCreator * create = new CollectorCreator(SingleClientDataCollector::create);
    table.put (&string1, create);
    StringJC string("SingleClientDataCollector");
    CollectorCreator* creator = dynamic_cast<CollectorCreator*> (table.get(&string)); CHECKDC(creator);
    if (creator) {
      printf("succeeded in retrieving element from hashtable\n");
    } else {
      printf ("failed\n");
    }
  }
  /** Test out the ServerMux class*/
  int TestServerMux(char* name, char* fileName) {
    printf("doing test0\n");
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

    // What a mess! Getrid of memory. 
    JCPN(StringEnumeration)* e = procs->keys();
    while(e->hasMoreElements()) {
      char* key = (char*)e->nextElement();
      free((char*)procs->get(key));
      key = 0;
    }
    delete e;
    delete procs;

    IO::pn("Here is the current setup I am working on:");
    dumpMachines();
    
    SocketConnectionManager* css = new SocketConnectionManager(myProcIndex, 
						     DEFAULTPORT,
						     machines);
    css->makeConnection(0);
    if(css->isServer()) {
      signal(SIGPIPE, &pipeSignal);
      int filedes[2];
      pipe (filedes);
      FILE* in = fdopen(filedes[0], "r");
      Connection* connect = new StaticIOConnection(in, stdout, 0);
      ServerMux mux(css, connect);
      
      printf("testing\n");
      mux.doClientIO();
      
      FILE* out = fdopen(filedes[1], "w");
      char str[256];
      while(1)
	{
	  printf("Please enter a string (\"shutdown\" to quit)\n");
	  fgets(str, 256, stdin);
	  if (!strncmp(str, "shutdown", strlen("shutdown")))
	    break;
	  fprintf(stdout, "printing: %s\n", str);
	  fprintf(out, "%s", str);
	  fflush(out);
	}
      printf("shutting down server mux\n");
      fprintf(out, "#<<ServerMux>>SHUTDOWN_MSG\n");
      fflush(out);
      mux.join();
      close(fileno(in));
      close(fileno(out));
      //while(1); 
    } else {
      Connection* connect = dynamic_cast<Connection*> (css->getConnections()->elementAt(0)); CHECKDC(connect);
      ReadNotify notif;
      connect->setReadCallback(&notif);
      TestThread thread(css);
      thread.start();
      printf("client started\n");
      thread.join();
    }
    delete css;
      return 0;
  }

/** Find a ProcessorInfo* index into a JCPN(Vector)* keyed by the name field
    in the ProcessorInfo*. */
  int findProcInfoIndex(char *name, 
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


/** Echos the processor file */
  void dumpProcTable(JCPN(ResourceHash)* procs) {
    JCPN(StringEnumeration)* k = procs->keys();
    while(k->hasMoreElements()) {
      char* p = (char*)k->nextElement();
      char* v = (char*)procs->get(p);
      IO::pn("proc: %s, type: %s", p, v);
    }
  }

  void dumpMachines() {
    JCPN(Enumeration)* e = machines->elements();
    while(e->hasMoreElements()) {
      ProcessorInfo* pi = (ProcessorInfo*)e->nextElement();
      IO::pn(pi->toString());
    }
    delete e;
    IO::pn("My %s", 
	   ((ProcessorInfo*)machines->elementAt(myProcIndex))->toString());
  }

  int doSetup(char* name, JCPN(StringHash)* procs) {

    char* type = (char*)procs->get(name);
    if(type == NULL) {
      IO::en("For some reason my processor: %s does not appear in the processor file: %s", name, procFile);
      return -1;
    }
    if(strcmp(type, "client") == 0) {
      isServer = FALSE;
    } else if(strcmp(type, "server") == 0) {
      isServer = TRUE;
    } else {
      IO::en("Got a different type other than \"client\" or \"server\"");
      IO::en("in file.  The type is: %s", type);
      return -1;
    }
    JCPN(Vector)* v = new JCPN(Vector)();
    JCPN(StringEnumeration)* k = procs->keys();
    while(k->hasMoreElements()) {
      char* el = (char*)k->nextElement();
      if(strcmp(el, name) == 0) {
	myProcIndex = v->size();
      }
      char* type = (char*)procs->get(el); // Shadows "type" above.
      boolean isServer; // Shadows isServer above.
      if(strcmp(type, "client") == 0) {
	isServer = FALSE;
      } else if(strcmp(type, "server") == 0) {
	isServer = TRUE;
      } else {
	IO::en("Got a different type other than \"client\" or \"server\"");
	IO::en("in file.  The type is: %s", type);
	return -1;
      }
      v->addElement(new ProcessorInfo(STRDUP(el), isServer));
    }    
    machines = v;
    delete k;
    return 0;
  }

};// TestClientServer

int main(int argc, char** argv) {
  char* usage = "TestClientServer --name MyHostName [--file <filename>] \n";

  char* procFile = 0; // File to read that contain the participating processors
  char* myName = 0; // My internet name or address.
  char* theOption;
  int testNum = 0;

  //Stolen verbatim from the man page for getopt.
  while (1)
    {
      int option_index = 0;
      static struct option long_options[] =
      {
	{"name", required_argument, 0, 0},
	  {"file", required_argument, 0, 0},
	  {"testNum", required_argument, 0, 0},
	    {0, 0, 0, 0}
      };

      int c = getCCAFEopt_long (argc, argv, "sc",
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
	myName = STRDUP(CCAFEoptarg);
      } else if(strcmp(theOption, "file") == 0) {
	procFile = CCAFEoptarg;
      } else if(strcmp(theOption, "testNum") == 0) {
	testNum = atoi(CCAFEoptarg);
      } else {
	printf("Bad option: %s", theOption);
	printf("%s\n", usage);
	exit(-1);
      }
    }
  //More stuff that could be used later:
//   if (CCAFEoptind < argc)
//     {
//       printf ("non-option ARGV-elements: ");
//       while (optind < argc)
// 	printf ("%s ", argv[optind++]);
//       printf ("\n");
//     }

  if(myName == 0) {
    printf("%s\n", usage);
    exit(-1);
  }
  TestClientServer* tst = new TestClientServer();
  switch (testNum) {
  case 0:
    tst->doTest0(myName, procFile);
    break;
  case 1:
    tst->doTest1(myName, procFile);
    break;
  case 2:
    tst->doTest2(myName, procFile);
    break;
  case 3:
    //tst->doTest3(myName, procFile);
    break;
  case 4:
    tst->doTest4(myName, DEFAULTPORT);
    break;
  case 5:
    tst->doTest5(myName, 3142);
    break;
  case 6:
    tst->TestHashTable();
    break;
  case 7:
    tst->TestServerMux(myName, procFile);
    break;
  }
  exit(0);
}
