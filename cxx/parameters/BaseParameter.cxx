#include "util/IO.h"
#include "parameters/BaseParameter.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "dc/export/config.hh"

namespace {
char id[]=
"$Id: BaseParameter.cxx,v 1.5 2009/02/03 21:40:44 baallan Exp $";
} ENDSEMI

char *BaseParameter::fillString(char *s) {
  int size;
  assert(s!=0);
  size = strlen(s);
  char *anonymous;
  anonymous = (char *)::malloc(size+40);
  ::sprintf(anonymous,"%s%p",s,this);
  return anonymous;
}
