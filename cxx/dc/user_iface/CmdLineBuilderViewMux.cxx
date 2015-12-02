
#define CmdLineCommonInternal_dependent
#include "dc/user_iface/CmdLineCommonInternal.h"
#include "dc/user_iface/CmdLineBuilderViewMux.h"

#include "util/freefree.h"

#ifndef lint
static char id[]=
"$Id: CmdLineBuilderViewMux.cxx,v 1.18 2005/11/16 03:21:28 baallan Exp $";
#endif


CmdLineBuilderViewMux::CmdLineBuilderViewMux() {
}

CmdLineBuilderViewMux::~CmdLineBuilderViewMux() {
}

void CmdLineBuilderViewMux::addCLBV(CmdLineBuilderView_shared bv) {
  if (bv!=0) {
    clbv.push_back(bv);
  }
}

/** iterate on a method in CmdLineBuilderView for all views.
 * X must be a method call, less the object it is called from.
 */
#define LOOPALL(X) \
for (size_t nv = 0; nv < clbv.size(); nv++)  clbv[nv]->X

void CmdLineBuilderViewMux::setOutputStream(FILE* out) {
  LOOPALL(setOutputStream(out));
}

void CmdLineBuilderViewMux::setBuilderModel(BuilderModel* bm) {
  LOOPALL(setBuilderModel(bm));
  bm->addComponentChangedListener(this);
}

void CmdLineBuilderViewMux::displayPallet() {
  LOOPALL(displayPallet());
}

void CmdLineBuilderViewMux::displayInstantiatedComponents() {
  LOOPALL(displayInstantiatedComponents());
}

void CmdLineBuilderViewMux::displayComponentInfo(const char* instanceName) {
  LOOPALL(displayComponentInfo(instanceName));
}

void CmdLineBuilderViewMux::connect(const char* fromInstance, const char* providesInstance, const char* toInstance, const char* usesInstance) {
  LOOPALL(connect(fromInstance,  providesInstance, toInstance, usesInstance));
}

void CmdLineBuilderViewMux::disconnect( const char* fromInstance, const  char* providesInstance, const  char* toInstance, const  char* usesInstance) {
  LOOPALL(disconnect(fromInstance,  providesInstance, toInstance, usesInstance));
}

void CmdLineBuilderViewMux::pullDownComponent(const char* className, 
				const char* instanceName) {
  LOOPALL(pullDownComponent(className, instanceName));
}

void CmdLineBuilderViewMux::displayConnectionFailed(const char *msg) {
  LOOPALL(displayConnectionFailed(msg));
}

void CmdLineBuilderViewMux::displayDisconnectionFailed(const char *msg) {
  LOOPALL(displayDisconnectionFailed(msg));
}

void CmdLineBuilderViewMux::displayChain() {
  LOOPALL(displayChain());
}

void CmdLineBuilderViewMux::error(const char* msg) {
  LOOPALL(error(msg));
}
void CmdLineBuilderViewMux::error(const std::string msg) {
	error(msg.c_str());
}


void CmdLineBuilderViewMux::errorFatal(const char *msg) {
  LOOPALL(errorFatal(msg));
}

void CmdLineBuilderViewMux::pn(const char* s) {
  LOOPALL(pn(s));
}

void CmdLineBuilderViewMux::p(const char* s) {
  LOOPALL(p(s));
}

void CmdLineBuilderViewMux::pn(const char c) {
  LOOPALL(pn(c));
}

void CmdLineBuilderViewMux::p(const char c) {
  LOOPALL(p(c));
}

void CmdLineBuilderViewMux::displayConfiguration(const char * instanceName, const char * portName, const char * data) {
  LOOPALL(displayConfiguration(instanceName,portName,data));
}

void CmdLineBuilderViewMux::setConfiguration(const char * instanceName, const char * portName, const char * fieldName, const char * data) {
  LOOPALL(setConfiguration(instanceName,portName,fieldName,data));
}

void CmdLineBuilderViewMux::displayComponentProperties(const char * instanceName, std::vector< std::string > & props)
{
  LOOPALL(displayComponentProperties(instanceName,props));
}

void CmdLineBuilderViewMux::displayComponentProperty(const char * instanceName, const char * key, const char * value) {
  LOOPALL(displayComponentProperty(instanceName,key,value));
}

void CmdLineBuilderViewMux::setComponentProperty(const char * instanceName, const char * key, const char * value, int err) {
  LOOPALL(setComponentProperty(instanceName,key,value,err));
}

void CmdLineBuilderViewMux::displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key) 
{
  LOOPALL(displayPortProperties(iname, pname, t, key));
}

void CmdLineBuilderViewMux::setPortProperty(const std::string & instanceName, const std::string & portName, const std::string & key, const std::string & vType, const std::string & value, int err)
{
  LOOPALL(setPortProperty(instanceName, portName, key, vType, value, err));
}

