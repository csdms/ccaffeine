

#include <cstring>
#include <stdlib.h>
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif

#include "dc/export/config.hh"
#include "parameters/parametersStar.h"
#include "port/supportInterfaces.h"
#include "dc/port/DefaultParameterPort.h"
#include "dc/framework/Check.h"
#include "util/freefree.h"

namespace {
char id[]=
"$Id: DefaultParameterPort.cxx,v 1.17 2008/12/24 19:38:42 baallan Exp $";
} ENDSEMI 

namespace {
	char * STRDUP(const char *s)
	{
		size_t n = strlen(s) +1;
		char *v = (char *)malloc(n);
		strcpy(v,s);
		return v;
	}
} ENDSEMI

DefaultParameterPort::DefaultParameterPort() {
  clearRequests();
}

DefaultParameterPort::~DefaultParameterPort() {
  free(title);
  title = 0;
  tabVector.clear();
  pVector.clear();
  configured = false;
  requestCount = -1;
  getListeners.clear();
  setListeners.clear();
}

int DefaultParameterPort::setConfigurationString(char *fieldName, char *value) {
  BaseParameter *p = getParameter(fieldName);
  CHECKDC(p);
  char * sval;
  sval = p->toString();
  if (strcmp(value,sval)==0) { free(sval); return 0; }
  free(sval); sval = 0;
  if (p->setValue(value)) {
    return -1;
  }
  configured = true;
  ParameterPort *pp;
  pp = dynamic_cast<ParameterPort *>(this);
  if (setListeners.size() != 0) {
    ParameterSetListener *powner;
    for (size_t i = 0; i < setListeners.size(); i++) {
      powner = setListeners[i];
      powner->updatedParameterValue(pp, fieldName, value);
    }
  }
  return 0;
}


/*CFREE*/ char *DefaultParameterPort::getConfigurationString(char *infix) {

  bool changed;
  ConfigurableParameterPort *cpp;
  if (getListeners.size() != 0) {
    ParameterGetListener *powner;
    cpp = dynamic_cast<ConfigurableParameterPort *>(this);
    for (size_t i = 0; i < getListeners.size(); i++) {
      powner = getListeners[i];
      changed = powner->updateParameterPort(cpp);
      if (changed != false) {
        configured = false;
      }
    }
  }

  if (tabVector.size() == 0) {
    return STRDUP("");
  }

  std::string sb = "newParamDialog ";
  sb += infix; 
  sb += " ";
  sb += title;
  sb += "\n";

  size_t numTabs = tabVector.size();
  BaseParameter *bp;
  for (size_t i = 0 ; i < numTabs; i++) {
    sb +=  "newParamTab ";
    sb +=  infix;
    sb +=  " ";
    sb += tabVector[i][0].getN(); 
    sb += "\n";
    size_t numItems = tabVector[i].size();
    for (size_t j=1; j < numItems; j++) {
      bp = tabVector[i][j].getP();
      char *bps;
      bps = bp->toString(infix);
      sb += bps;
      free(bps); 
      bps = 0;
    }
  }
  sb += "paramEndDialog ";
  sb += infix;
  sb += "\n";
  const char *result;
  result = sb.c_str();
  return STRDUP(result);
}

/*CFREE*/ char *DefaultParameterPort::getConfigurationString(char *infix, char *fieldName) {

  bool changed;
  ConfigurableParameterPort *cpp;
  if (getListeners.size() != 0) {
    ParameterGetListener *powner;
    cpp = dynamic_cast<ConfigurableParameterPort *>(this);
    for (size_t i = 0; i < getListeners.size(); i++) {
      powner = getListeners[i];
      changed = powner->updateParameterPort(cpp);
      if (changed != false) {
        configured = false;
      }
    }
  }

  BaseParameter *bp;
  bp = getParameter(fieldName);
  if (!bp) { return ""; }
  return bp->toString(infix);
}

bool DefaultParameterPort::isFullyConfigured() {
  return configured;
}

void DefaultParameterPort::clearRequests() {
  title = "No Title Given";
  tabVector.clear();
  pVector.clear();
  configured = false;
  requestCount = 0;  // should match pvector->size();
  getListeners.clear();
  setListeners.clear();
}

void DefaultParameterPort::setUpdater(ParameterGetListener *po) {
  getListeners.push_back(po);
}

void DefaultParameterPort::setUpdatedListener(ParameterSetListener *po) {
  setListeners.push_back(po);
}


void DefaultParameterPort::setBatchTitle(char *title_) {
  title = STRDUP(title_);
}

void DefaultParameterPort::setGroupName(char *name) {
  ::std::string ns(name);
  dpp::tvElement first(ns);
  std::vector< dpp::tvElement > newtab;
  newtab.push_back(first);
  tabVector.push_back(newtab);
}

void DefaultParameterPort::addRequest(BaseParameter *p) {
  size_t len = tabVector.size();
  int ilen = len;
  if (len == 0) {
    char tmp[30];
    sprintf(tmp,"Tab%d",ilen);
    ::std::string sn(tmp);
    dpp::tvElement first(sn);

    std::vector< dpp::tvElement > newtab;
    newtab.push_back(first);
    tabVector.push_back(newtab);
  }
  len = tabVector.size();
  dpp::tvElement newbp(p);
  pVector.push_back(p);
  tabVector[len-1].push_back(newbp);
  requestCount++;
}

BaseParameter *DefaultParameterPort::getParameter(char *name) {
  size_t i, len;
  len = pVector.size();
  for (i = 0; i < len; i++) {
    BaseParameter *p = pVector[i]; CHECKDC(p);
    char *n = p->getName();
    if (strcmp(name,n) == 0) {
      return p;
    }
  }
  return 0;
}


