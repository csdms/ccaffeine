#ifndef __PROCESSORINFO_H__
#define __PROCESSORINFO_H__

#include <stdio.h>
#include <string.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC


/** A class to create a server and multiple clients connected by
    sockets overwhich the clients can converse */
class ProcessorInfo : public JCPN(Object) {
 private:
  char* name;
  boolean isServer_; // true if I am the serve, false if I am the client
 public:
  ProcessorInfo(/*CFREE */ char* name, boolean isServer);
  char* getName() {return name;}
  boolean isServer(){ return isServer_;}
  // Note: not virtual
  ~ProcessorInfo();
  /*CFREE*/ char* toString();
};
#endif // __PROCESSORINFO_H__
