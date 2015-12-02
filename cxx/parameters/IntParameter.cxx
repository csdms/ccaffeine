// package parameters;
#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/jc++util.h"
#include "parameters/BaseParameter.h"

#include "parameters/IntParameter.h"

#include <stdlib.h>
#include <assert.h>

#include "util/freefree.h"

#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: IntParameter.cxx,v 1.10 2003/07/07 19:08:40 baallan Exp $";
} ENDSEMI

IntParameter::IntParameter(char *name_, char *help_, char *prompt_, int Default_, int low_, int high_) {
  name = name_;
  Default = Default_;
  help = help_;
  prompt = prompt_;
  low = low_;
  high = high_;
  if (low > high) {
    low = high_;
    high = low_;
  }
  if (Default < low) {
    Default = low;
  }
  if (Default > high) {
    Default = high;
  }
  value = Default;
}

int IntParameter::setValue(char *val) {
  int d = Default;
  int numGot;
  numGot = sscanf(val,"%d",&d); 
  if (numGot != 1 || d < low || d > high) {
    char *result;
    JCPN(StringBuffer) *sb = new JCPN(StringBuffer)((char *)"Int value {");
    sb->append(val);
    sb->append((char *)"} out of range for ");
    sb->append(prompt);
    result = sb->toString();
    delete sb;
    sb=null;
    IO::en(result);
    free(result);
    return -1;
  }
  value = d;
  return 0;
}

CFREE char *IntParameter::toString() {
  JCPN(StringBuffer) *sb = new JCPN(StringBuffer)();
  char *result;
  sb->append((char *)"INT&");
  sb->append(name);
  sb->append((char *)"&");
  sb->append(value);
  sb->append((char *)"&");
  sb->append(help);
  sb->append((char *)"&");
  sb->append(prompt);
  sb->append((char *)"&");
  sb->append(Default);
  sb->append((char *)"&");
  sb->append(low);
  sb->append((char *)"&");
  sb->append(high);
  result = sb->toString();
  delete sb;
  return result;
}

CFREE char *IntParameter::toString(char *infix) {
  JCPN(StringBuffer) *sb =
    new JCPN(StringBuffer)((char *)"newParamField ");
  sb->append(infix);
  sb->append((char *)" INT ");
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)"\n");
  sb->append((char *)"paramCurrent ");
  sb->append(infix);
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)" ");
  sb->append(value);
  sb->append((char *)"\n");
  sb->append((char *)"paramHelp ");
  sb->append(infix);
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)" ");
  sb->append(help);
  sb->append((char *)"\n");
  sb->append((char *)"paramPrompt ");
  sb->append(infix);
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)" ");
  sb->append(prompt);
  sb->append((char *)"\n");
  sb->append((char *)"paramDefault ");
  sb->append(infix);
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)" ");
  sb->append(Default);
  sb->append((char *)"\n");
  sb->append((char *)"paramNumberRange ");
  sb->append(infix);
  sb->append((char *)" ");
  sb->append(name);
  sb->append((char *)" ");
  sb->append(low);
  sb->append((char *)" ");
  sb->append(high);
  sb->append((char *)"\n");

  char *rval; rval = sb->toString(); delete sb; return rval;
}

IntParameter::~IntParameter() {
  if (valueString != 0) {
    free(valueString);
    valueString = 0;
  }
}

char *IntParameter::getValueString() {
  if (valueString == 0) {
    valueString = (char *)malloc(40);
    assert(valueString!=0);
  }
  sprintf(valueString,"%d",value);
  return valueString;
}

