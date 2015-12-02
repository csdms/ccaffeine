#ifdef CCAFE_SOCKETS

#ifndef __CLIENTSERVERSOCKET_H__
#define __CLIENTSERVERSOCKET_H__

#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "util/IO.h"
#include "ProcessorInfo.h"

#ifndef bufsize_seen
#define bufsize_seen
#define BSIZ BUFSIZ

enum {
  NORMAL_BUF,
  LINE_BUF,
  NO_BUF
};
#endif

class ClientServerSocket  {
 private:
  JCPN(Vector)* machines; // type ProcessorInfo*
  // A number that ranges from 0 to nproc -1
  int myProcNumber;
  int serverProcNumber; // The processor number for the Server
  int serverPort; // Port on which the server will be listening.

  // File descriptors for IO.  Server has a vector of valid fd's top
  // the clients clients have only in[0] and out[0] as valid.
  CDELETE FILE** in;
  CDELETE FILE** out;

  // Buffering options, probably LINE_BUF will work best.
  char buffering;
  //Backlog of connections that will wait on a connect.
  int backlog;

 public:

  ClientServerSocket(int myProcNumber, int serverPort, 
		     CDELETE JCPN(Vector)* machines);
  virtual ~ClientServerSocket();

  FILE** getIn(int& size);
  FILE** getOut(int& size);

  int acceptConnections();
  int connectToServer();

  boolean isServer();
  /** Go ahead and make the connection that has already been set up.
      Returns: 0 for sucess, -1 for failure due to inconsistency in
      the current configuration, -2 for failure due to a network
      problem */
  int makeConnection();
};

#endif // __CLIENTSERVERSOCKET_H__
#else
extern int ccafe_no_clientserversocket;
#endif // CCAFE_SOCKETS
