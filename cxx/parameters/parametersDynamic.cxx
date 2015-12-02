
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "parametersStar.h"
#include "parametersDynamic.h"

#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: parametersDynamic.cxx,v 1.4 2003/07/07 19:08:40 baallan Exp $";
} ENDSEMI

parameters_DynamicLink::parameters_DynamicLink(int i) {
  i_ = i;
  if (i) {
    bp = new  BoolParameter((char *)"a",(char *)"b",(char *)"c",0);
    dp = new  DoubleParameter((char *)"a",(char *)"b",(char *)"c",0,-1,1);
    fp = new  FloatParameter((char *)"a",(char *)"b",(char *)"c",0,-1,1);
    ip = new  IntParameter((char *)"a",(char *)"b",(char *)"c",0,-1,1);
    lp = new  LongParameter((char *)"a",(char *)"b",(char *)"c",0,-1,1);
    sp = new  StringParameter((char *)"a",(char *)"b",(char *)"c",(char *)"d");
  }
}

parameters_DynamicLink::~parameters_DynamicLink() {
  if (i_) {
#define forget(x) delete x; x = 0
    forget(bp);
    forget(dp);
    forget(fp);
    forget(ip);
    forget(lp);
    forget(sp);
  }
}
