
#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/jc++util.h"
#include "parameters/BaseParameter.h"

#include "parameters/StringParameter.h"

#include "util/freefree.h"
#include "dc/export/config.hh"

namespace {
char id[]=
"$Id: StringParameter.cxx,v 1.13 2005/02/01 00:14:31 baallan Exp $";
} ENDSEMI


void StringParameter::addChoice(char *s) {
  stringlist.push_back(s);
}

::std::vector< ::std::string > StringParameter::getChoices() {
  return stringlist;
}

StringParameter::StringParameter(char *name_, char *help_, char *prompt_, char *Default_) {
  name=STRDUP(name_==0?this->fillString((char *)"anonName"):name_);
  Default=STRDUP(Default_==0?"":Default_);
  help=STRDUP(help_==0?"":help_);
  prompt=STRDUP(prompt_==0?"":prompt_);
  value=STRDUP(Default==0?"":Default);
}

StringParameter::~StringParameter() {
  free(value);
  free(help);
  free(prompt);
  free(Default);
  value=0;
  help=0;
  prompt=0;
  Default=0;
}

int StringParameter::setValue(char *val) {
  if (stringlist.size() == 0) {
    char *oldvalue = value;
    value = STRDUP(val==0?"":val);
    free(oldvalue);
    return 0;
  }
  for (size_t i = 0; i < stringlist.size(); i++) {
    if (stringlist[i] == val) {
      free(value); value = 0;
      value = STRDUP(val==0?"":val);
      return 0;
    }
  }
  std::string sb = "Choice {";
  sb += val;
  sb += "} not in list for ";
  sb += prompt;
  IO::en(sb.c_str());
  return -1;
}

char *StringParameter::toString() {
	char buf[40];
  ::std::string sb = "STRING&";
  sb += name;
  sb += "&";
  sb += value;
  sb += "&";
  sb += help;
  sb += "&";
  sb += prompt;
  sb += "&";
  sb += Default;
  sb += "&";
  sb += "Nchoices=";
  sprintf(buf,"%d",int(stringlist.size()));
  sb += buf;
  sb += "&";
  for (size_t i = 0; i < stringlist.size(); i++) {
    sb += stringlist[i];
    sb += "&";
  } 
  char *result;
  result = STRDUP(sb.c_str());
  return result;
}

/*CFREE*/ char *StringParameter::toString(char *infix) {
  std::string sb = "newParamField ";
  sb += infix;
  sb += " STRING ";
  sb += " ";
  sb += name;
  sb += "\n";
  sb += "paramCurrent ";
  sb += infix;
  sb += " ";
  sb += name;
  sb += " ";
  sb += value;
  sb += "\n";
  sb += "paramHelp ";
  sb += infix;
  sb += " ";
  sb += name;
  sb += " ";
  sb += help;
  sb += "\n";
  sb += "paramPrompt ";
  sb += infix;
  sb += " ";
  sb += name;
  sb += " ";
  sb += prompt;
  sb += "\n";
  sb += "paramDefault ";
  sb += infix;
  sb += " ";
  sb += name;
  sb += " ";
  sb += Default;
  sb += "\n";
  for (size_t i = 0; i < stringlist.size(); i++) {
    sb += "paramStringChoice ";
    sb += infix;
    sb += " ";
    sb += name;
    sb += " ";
    sb += stringlist[i];
    sb += "\n";
  }

  char *result;
  result = STRDUP(sb.c_str());
  return result;
}


char *StringParameter::getValueString() {
  return value;
}

