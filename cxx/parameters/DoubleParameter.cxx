// package parameters;
#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/jc++util.h"
#include "parameters/BaseParameter.h"

#include "parameters/DoubleParameter.h"

#include <stdlib.h>
#include <assert.h>

#include "util/freefree.h"

#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: DoubleParameter.cxx,v 1.10 2003/07/07 19:08:40 baallan Exp $";
} ENDSEMI

DoubleParameter::~DoubleParameter() {
  if (valueString != 0) {
    free(valueString);
    valueString = 0;
  }
}

DoubleParameter::DoubleParameter(char *name_, char *help_, char *prompt_, double Default_, double low_, double high_) {
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
  valueString=0;
}

int DoubleParameter::setValue(char *val){
  double d = Default; // not needed if exceptions arent broken.
  int numGot;
  numGot = sscanf(val,"%lg",&d); // possible nonportability. strtod?
  if (numGot != 1 || d < low || d > high) {
    char *result;
    JCPN(StringBuffer) *sb = new JCPN(StringBuffer)((char *)"Double value {");
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

CFREE char *DoubleParameter::toString() {
  JCPN(StringBuffer) *sb = new JCPN(StringBuffer)();
  char *result;
  sb->append((char *)"DOUBLE&");
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

CFREE char *DoubleParameter::toString(char *infix) {
  JCPN(StringBuffer) *sb =
    new JCPN(StringBuffer)((char *)"newParamField ");
  sb->append(infix);
  sb->append((char *)" DOUBLE ");
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
  char *rval;
  rval = sb->toString();
  delete sb;
  return rval;
}


char *DoubleParameter::getValueString() {
  if (valueString == 0) {
    valueString = (char *)malloc(40);
    assert(valueString!=0);
  }
  sprintf(valueString,"%21.18g",value);
  return valueString;
}

