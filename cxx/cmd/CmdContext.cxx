#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: CmdContext.cxx,v 1.3 2003/07/07 19:08:36 baallan Exp $";
} ENDSEMI


#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"

#include "util/freefree.h"


CmdContext::CmdContext() {
  debug_ = false;
  verbose_ = true;
}

boolean CmdContext::setDebug(boolean d) {
  debug_ = d;
  return debug_;
}

boolean CmdContext::debug() {
  return debug_;
}

boolean CmdContext::setVerbose(boolean v) {
  verbose_ = v;
  return verbose_;
}

boolean CmdContext::verbose() {
  return verbose_;
}

