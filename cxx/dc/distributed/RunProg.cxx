#include <errno.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>
#include <gnu/getopt/getCCAFEopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "jc++/io/jc++io.h"
#include "jc++/util/Thread.h"
#include "ConnectionManager.h"
#include "SocketConnectionManager.h"
#include "ServerMux.cxx"


#define BUF_SIZE 256

#ifndef Driver_RunProg

// here for the makefile genericity

#else // Driver_RunProg



class MuxToBash : public virtual ReadCallback {
  FILE* bashWriter;
public:
  MuxToBash(int fd) {
    bashWriter = fdopen(fd, "w");
    ::fprintf(bashWriter, "reader is awake\n");
    ::fflush(bashWriter);
  }
  void readReady(Connection* connect) {
    //    printf("got a read ready call\n");
    JCPN(BufferedReader) reader(connect->getIn());
    char* str;
    while ((str = reader.readLine())) {
      ::fprintf(bashWriter, str);
      ::fprintf(bashWriter, "\n");
      ::fflush(bashWriter);
      printf("Wrote string %s to bash\n", str);
      free(str);
    }
    perror("Finished reading, error is");
    if (!((errno == EAGAIN))) {
      printf("Could not read from multiplexor, ::exiting\n");

      connect->disconnect();
      printf("disconnected the connection\n");
      ::fprintf(bashWriter, "::exit\n");
      ::fflush(bashWriter);
      
    }
  }
};



class BashToMuxThread : public CCAFEThread {
  FILE* bFilePtr;
  JCPN(Writer)* muxWriter;
public:
  BashToMuxThread(Connection* connect, int fd) 
  {
    if (connect)
      muxWriter = connect->getOut();
    else
      muxWriter = NULL;
    bFilePtr = fdopen(fd, "r");
  }
  void* run() {
    printf("BashToMuxThread started\n");
    char str[BUF_SIZE];
    while (fgets(str, BUF_SIZE, bFilePtr)) {
      printf("parent got string %s", str);
      if (muxWriter) {
	muxWriter->write(&str[0]);
	muxWriter->flush();
      }
    }
    printf("Could not read from stream, ::exiting\n");
    return NULL;
  }
};

char* usage = "RunBash --name nextHostName [--port <portNum>]";

int main (int argc, char** argv) 
{
  

  int pipeids1[2];
  int error = pipe(pipeids1);
  if (error < 0) {
    perror("Error creating pipe: ");
  }
  int pipeids2[2];
  error = pipe(pipeids2);
  if (error < 0) {
    perror("Error creating pipe: ");
  }
 
  int pid = fork();
  if (pid == 0)
    {
      /* this was test code
      FILE* out = fdopen(pipeids1[1], "w");
      FILE* in = fdopen(pipeids2[0], "r");
      printf("I am the child process\n");
      ::fprintf(out, "Child sending message\n");
      ::fflush(out);
      char str[BUF_SIZE];
      while (fgets(str, BUF_SIZE, in)) {
	printf("Bash got string: %s\n", str);
      }
      */
      
	dup2(pipeids1[1], fileno(stdout));
	dup2(pipeids2[0], fileno(stdin));
	dup2(pipeids1[1], fileno(stderr));
	
	char* argvBash[2];
	argvBash[0] = "bash";
	argvBash[1] = "-s";

	int error = execvp(argvBash[0], argvBash);
	if (error != 0)
	{
	  perror("exec failed with error");
	}
      
    }
  else 
    {
      
      // args:
      // port (int)
      // machine name (string)
      // variables for the passed in args
      int port = 0;
      jcpp::StringJC name;
      char* theOption;

      /* this was test code
      FILE* out = fdopen(pipeids2[1], "w");
      FILE* in = fdopen(pipeids1[0], "r");
      printf("I am the parent process\n");
      ::fprintf(out, "Parent sending message\n");
      ::fflush(out);
      */
    
      // parse the args
      while (1) {
	int option_index = 0;
	static struct CCAFEoption long_options[] =
	{
	  {"name", required_argument, 0, 0},
	    {"port", required_argument, 0, 0},
	      {0, 0, 0, 0}
	};
    
	//optstring: p:(port)n:(name)f:(proc file)s:(next server name)c:(client port)
	int c = getCCAFEopt_long(argc, argv, "n:p:",
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
	    ::exit(-1);
	  }
	if(strcmp(theOption, "name") == 0) {
	  name.append(CCAFEoptarg);
	} else if(strcmp(theOption, "port") == 0) {
	  port = atoi(CCAFEoptarg);
	} else {
	  printf("Bad option: %s\n", theOption);
	  printf("%s\n", usage);
	  ::exit(-1);
	}
      }

      if (name.length() == 0) {
	name.append("127.0.0.1");
      }
      if (port == 0) {
	port = 3141;
      }

      // set up the connection
      printf("I am the parent process. Child pid is: %i\n", pid);
      SocketConnectionManager scm(port, name.getBuffer(), FALSE);
      int error = scm.makeConnection(0);
      if (error != 0)
	{
	  perror("Could not connect to server, error");
	}
      
      // prepare to read from and write to the connection
      Connection* connect = dynamic_cast<Connection*> (scm.getConnections()->elementAt(0)); CHECKDC(connect);
      MuxToBash reader(pipeids2[1]);
      connect->setReadCallback(&reader);

      BashToMuxThread wThread(connect, pipeids1[0]);
      wThread.start();

      IOThread iothread(&scm);
      iothread.start();
    

      // ::wait for the child to ::exit
    int status;
    ::wait (&status);

    printf("Child pid : %i ::exited\n", pid);
    scm.shutdown();

    ::printf("Shutdown socket connection manager\n");
    ::close(pipeids1[0]);
    ::close(pipeids2[0]);
    ::close(pipeids1[1]);
    ::close(pipeids2[1]);
    ::close(fileno(stdin)); // attempt to stop the writer thread - doesn't work
  }
}

#endif 
