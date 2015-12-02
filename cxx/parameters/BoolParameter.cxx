// package parameters;


// to eat our own package header
#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/StringVector.h"

// to eat our implementation of string functions.
#include "jc++/util/JString.h"
#include "jc++/util/StringBuffer.h"

#include "parameters/BaseParameter.h"

#include "parameters/BoolParameter.h"

#include "util/freefree.h"
#include "dc/export/config.hh"

namespace {
char id[]=
"$Id: BoolParameter.cxx,v 1.13 2005/02/01 00:14:31 baallan Exp $";
} ENDSEMI

BoolParameter::BoolParameter(char *name_, char *help_, char *prompt_, bool Default_) {
  name = name_;
  Default=Default_;
  help=help_;
  prompt=prompt_;
  value=Default;
  valueString = (char *)(value?"true":"false");
}


int BoolParameter::setValue(char *val) {
  if (JString::compareToIgnoreCase(val,(char *)"n")==0 ||
      JString::compareToIgnoreCase(val,(char *)"no")==0 ||
      JString::compareToIgnoreCase(val,(char *)"nyet")==0 ||
      JString::compareToIgnoreCase(val,(char *)"nada")==0 ||
      JString::compareToIgnoreCase(val,(char *)"zip")==0 ||
      JString::compareToIgnoreCase(val,(char *)"f")==0 ||
      JString::compareToIgnoreCase(val,(char *)"false")==0 ||
      JString::compareToIgnoreCase(val,(char *)"0")==0 ||
      JString::compareToIgnoreCase(val,(char *)"wrong")==0 ||
      JString::compareToIgnoreCase(val,(char *)"buzz")==0) {
    value = false;
    return 0;
  }

  if (JString::compareToIgnoreCase(val,(char *)"y")==0 ||
      JString::compareToIgnoreCase(val,(char *)"yes")==0 ||
      JString::compareToIgnoreCase(val,(char *)"da")==0 ||
      JString::compareToIgnoreCase(val,(char *)"si")==0 ||
      JString::compareToIgnoreCase(val,(char *)"yep")==0 ||
      JString::compareToIgnoreCase(val,(char *)"t")==0 ||
      JString::compareToIgnoreCase(val,(char *)"true")==0 ||
      JString::compareToIgnoreCase(val,(char *)"1")==0 ||
      JString::compareToIgnoreCase(val,(char *)"right")==0 ||
      JString::compareToIgnoreCase(val,(char *)"correct")==0 ||
      JString::compareToIgnoreCase(val,(char *)"bingo")==0 ||
      JString::compareToIgnoreCase(val,(char *)"ok")==0 ||
      JString::compareToIgnoreCase(val,(char *)"ding!")==0) {
    value = true;
    return 0;
  }

  char *result;
  JCPN(StringBuffer) *sb = new JCPN(StringBuffer)((char*)"Non-boolean value {");
  sb->append(val);
  sb->append((char *)"} given for ");
  sb->append(prompt);
  result = sb->toString();
  delete sb; sb=null;
  IO::en(result);
  return -1;
}

char *BoolParameter::toString() {
  JCPN(StringBuffer) *sb = new JCPN(StringBuffer)();
  char *result;
  sb->append((char*)"BOOL&");
  sb->append(name);
  sb->append((char*)"&");
  sb->append(value);
  sb->append((char*)"&");
  sb->append(help);
  sb->append((char*)"&");
  sb->append(prompt);
  sb->append((char*)"&");
  sb->append(Default);
  result = sb->toString();
  delete sb;
  return result;
}

/*CFREE*/ char *BoolParameter::toString(char *infix) {
  JCPN(StringBuffer) *sb =
    new JCPN(StringBuffer)((char*)"newParamField ");
  sb->append(infix);
  sb->append((char*)" BOOL ");
  sb->append((char*)" ");
  sb->append(name);
  sb->append((char*)"\n");
  sb->append((char*)"paramCurrent ");
  sb->append(infix);
  sb->append((char*)" ");
  sb->append(name);
  sb->append((char*)" ");
  sb->append(getValueString());
  sb->append((char*)"\n");
  sb->append((char*)"paramHelp ");
  sb->append(infix);
  sb->append((char*)" ");
  sb->append(name);
  sb->append((char*)" ");
  sb->append(help);
  sb->append((char*)"\n");
  sb->append((char*)"paramPrompt ");
  sb->append(infix);
  sb->append((char*)" ");
  sb->append(name);
  sb->append((char*)" ");
  sb->append(prompt);
  sb->append((char*)"\n");
  sb->append((char*)"paramDefault ");
  sb->append(infix);
  sb->append((char*)" ");
  sb->append(name);
  sb->append((char*)" ");
  sb->append(getValueString(Default));
  sb->append((char*)"\n");
  char *rval;
  rval = sb->toString();
  delete sb;
  return rval;
}


char *BoolParameter::getValueString() {
  valueString = (char *)(value?"true":"false");
  return valueString;
}

char *BoolParameter::getValueString(bool val) {
  valueString = (char *)(val?"true":"false");
  return valueString;
}

#ifdef _BoolParameter_MAIN
int main(int argc, char **argv){
  BoolParameter *p = new BoolParameter("which word didn't you understand?",
                                       "enter true or false",true);
  printf("%s\n",p->toString());
}
#endif // _BoolParameter_MAIN
