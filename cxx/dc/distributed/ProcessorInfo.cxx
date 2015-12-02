#include <stdlib.h>
#include "ProcessorInfo.h"
#include "util/freefree.h"


#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: ProcessorInfo.cxx,v 1.4 2003/07/07 19:08:38 baallan Exp $";
} ENDSEMI


ProcessorInfo::ProcessorInfo(CFREE char* name, boolean isServer) {
  this->name = name;
  this->isServer_ = isServer;
}

  ProcessorInfo::~ProcessorInfo(){
    free(name);
  }

CFREE char* ProcessorInfo::toString() {
  char* type;
  if(isServer_) {
    type = "is a server";
  } else {
    type = "is a client";
  }
  int siz = 80 + strlen(name);
  char* str = (char*)malloc(siz);
  sprintf(str,  "ProcessorInfo: name = %s, %s\n", name, type);
  return str;
}
