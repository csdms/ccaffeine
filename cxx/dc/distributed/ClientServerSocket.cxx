#ifdef CCAFE_SOCKETS

#include "ClientServerSocket.h"
#include "util/freefree.h"
#include <stdio.h>
#include <stdlib.h>

#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: ClientServerSocket.cxx,v 1.13 2007/06/28 13:12:19 rob Exp $";
} ENDSEMI


ClientServerSocket::ClientServerSocket(int myProcNumber, int serverPort, 
				       CDELETE JCPN(Vector)* machines) {
  this->serverPort = serverPort;
  this->machines = machines;
  this->myProcNumber = myProcNumber;
  for(int i = 0;i < machines->size();i++) {
    ProcessorInfo *pi = (ProcessorInfo*)machines->elementAt(i);
    if(pi->isServer()) serverProcNumber = i;	
  }
  if(isServer()) {
    in = new FILE*[machines->size()];
    out = new FILE*[machines->size()];
  } else {
    in = new FILE*[1];
    out = new FILE*[1];
  }
  buffering = (char)LINE_BUF;
  // Number of processes that can be backed up waiting for me to accept
  // connections.
  backlog = 100; 
}
ClientServerSocket::~ClientServerSocket(){
  //delete machines and close fd's and delete their arrays
}
int ClientServerSocket::acceptConnections() { 


  struct sockaddr_in from, sin;
  memset(&sin, 0, sizeof(sin));
  memset(&from, 0, sizeof(from));
  sin.sin_port = htons(serverPort);

  int t = socket(AF_INET, SOCK_STREAM, 0);
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
  listen(t, backlog);
  size_t len = sizeof(from);
#if __linux
  unsigned int ulen = len;
#endif
  // Probably should set an alarm...
  for(int i = 0;i < machines->size() - 1;i++) {
    //Note that the order of sockets in array ss is not the same as
    //the order in JCPN(Vector) machines.
#if __linux
    int s = accept(t, (sockaddr*)&from, &ulen);
    len = ulen;
#else
    socklen_t ilen = (socklen_t)len;
    int s = accept(t, (sockaddr*)&from, &ilen);
    len = (int) ilen;
#endif
    struct hostent* frm = gethostbyaddr((char*)&from, len, AF_INET);
    if(frm != NULL) {
      IO::en("connected to: %s", frm->h_name);
    } else {
      IO::en("Hey! cannot tell who connected ... (proceeding)");
    }
    in[i] = fdopen(s, "r");
    out[i] = fdopen(s, "w");
    switch(buffering)
      {
      case NORMAL_BUF:
	break;
      case LINE_BUF:
	setvbuf(in[i], NULL, _IOLBF, BSIZ);
	setvbuf(out[i], NULL, _IOLBF, BSIZ);
	break;
      case NO_BUF:
	setvbuf(in[i], NULL, _IONBF, BSIZ);
	setvbuf(out[i], NULL, _IONBF, BSIZ);
	break;
      }
  }
  return 0;
}

int ClientServerSocket::connectToServer() {
  ProcessorInfo* serv = 
    (ProcessorInfo*)machines->elementAt(serverProcNumber);
  hostent* hp = gethostbyname(serv->getName());
  if(hp == NULL) { 
    perror("ClientServerSocket::connectToServer");
    IO::en("unknown host: %s\n", serv->getName());
    return -1;
  }
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(serverPort);  
  int s = socket(AF_INET,SOCK_STREAM,0);
  {
    int val = 1;
    struct linger l;
    l.l_onoff = 0;
    l.l_linger = 0;
	
    setsockopt(s, SOL_SOCKET, SO_LINGER, &l, sizeof(struct linger));
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  }

  if(s < 0) { 
    perror("ClientServerSocket::connectToServer:");
    IO::en("socket: there is some network problem\n");
    return -3;
  }
#ifdef __linux
  if(connect(s, (const sockaddr*)&server, sizeof(server)) < 0) {
#else
  if(connect(s, (sockaddr*)&server, sizeof(server)) < 0) {
#endif
    perror("ClientServerSocket::connectToServer");
    IO::en("connect: there is some network problem\n");
    return -3; 
  }
  in[0] = fdopen(s, "r");
  out[0] = fdopen(s, "w");
      
  switch((char)buffering)
    {
    case NORMAL_BUF:
      break;
    case LINE_BUF:
      setvbuf(in[0], NULL, _IOLBF, BSIZ);
      setvbuf(out[0], NULL, _IOLBF, BSIZ);
      break;
    case NO_BUF:
      setvbuf(in[0], NULL, _IONBF, BSIZ);
      setvbuf(out[0], NULL, _IONBF, BSIZ);
      break;
    }
  return 0;
}

boolean ClientServerSocket::isServer() {
  return myProcNumber == serverProcNumber;
}
/** Go ahead and make the connection that has already been set up.
      Returns: 0 for sucess, -1 for failure due to inconsistency in
      the current configuration, -2 for failure due to a network
      problem */
int ClientServerSocket::makeConnection() {
  if(isServer()) {
    if(acceptConnections() != 0) return -1;
  }
  else {
    if(connectToServer() != 0) return -1;
  }

  return 0;
}

FILE** ClientServerSocket::getIn(int& size) {
  if(isServer()) {
    size = machines->size() - 1;
  } else {
    size = 1;
  }
  return in;
}

FILE** ClientServerSocket::getOut(int& size) {
  if(isServer()) {
    size = machines->size() - 1;
  } else {
    size = 1;
  }
  return out;
}

#else // CCAFE_SOCKETS
int ccafe_no_clientserversocket;
#endif // CCAFE_SOCKETS
