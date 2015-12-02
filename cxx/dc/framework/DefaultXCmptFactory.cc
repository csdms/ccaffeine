
#include "dc/export/AllExport.hh"
#include "dc/framework/Check.h"
#include "dc/framework/dc_fwkStar.h"
#include "dc/framework/XCmptFactory.hh"
#include "dc/framework/DefaultXCmptFactory.hh"

namespace {
char id[]=
"$Id: DefaultXCmptFactory.cc,v 1.7 2007/10/17 17:19:33 baallan Exp $";
} ENDSEMI
using std::string;


XCmptFactory_shared
DefaultXCmptFactory::createFactory(Gizzard * giz, const string & portInstance)
{
	DefaultXCmptFactory *df = new DefaultXCmptFactory(giz,portInstance);
	XCmptFactory_shared xs(df);
	return xs;
}

DefaultXCmptFactory::DefaultXCmptFactory(Gizzard * giz, string portInstance) {
  this->giz = giz;
  this->portInstance = portInstance;
  last = -1;
}


bool 
DefaultXCmptFactory::hasComponent(const std::string & cmptType) {
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  ccafeopq::Port * p = giz->getPort(portInstance, status);
  if (p == 0) {
    IO_dn3("DefaultXCmptFactory::hasComponent(%s) returning false from port %s because it has disappeared!",cmptType.c_str(), portInstance.c_str());
    return false;
  }
  ccafeopq::ComponentFactory * svc = dynamic_cast< ccafeopq::ComponentFactory * >(p);
  CHECKDC(svc);
  std::vector< std::string > names = svc->getComponentClassAliases();
  for(size_t i = 0;i < names.size(); i++) {
    if(names[i] == cmptType) {
      last = i;
      lastCmpt = cmptType;
      giz->releasePort(portInstance);
      return true;
    }
  }
  last = -1;
  giz->releasePort(portInstance);
  return false;
}

std::vector< std::string> 
DefaultXCmptFactory::getComponentClassNames() {
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  ccafeopq::ComponentFactory * svc = 
    dynamic_cast< ccafeopq::ComponentFactory * >(giz->getPort(portInstance, status));
  std::vector< std::string> ret = svc->getComponentClassAliases();
  giz->releasePort(portInstance);
  return ret;
}

void
DefaultXCmptFactory::destroy(const std::string & cmptType, 
		ccafeopq::Component *c)
{
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  ccafeopq::ComponentFactory * svc = 
    dynamic_cast< ccafeopq::ComponentFactory * >(giz->getPort(portInstance, status));
  if (svc == 0) {
    return ; // !!!gahhh
  }
  try {
    svc->destroyComponentInstance(cmptType,c);
    giz->releasePort(portInstance);
    return;
  } catch(ccafeopq::Exception e) {
    IO_dn2("Exception: %s\n", e.what());
    giz->releasePort(portInstance);
    return;
  }
}

ccafeopq::Component * 
DefaultXCmptFactory::instantiate(const std::string & cmptType) {
  if((lastCmpt == cmptType) || hasComponent(cmptType)) {
    ccafeopq::ExceptionType status = ccafeopq::Correct;
    ccafeopq::ComponentFactory * svc = 
      dynamic_cast< ccafeopq::ComponentFactory * >(giz->getPort(portInstance, status));
    if (svc == 0) {
      return 0; // !!!gahhh
    }
    ccafeopq::Component * c;
    try {
      c = svc->createComponentInstance(cmptType);
      giz->releasePort(portInstance);
      return c;
    } catch(ccafeopq::Exception e) {
      IO_dn2("Exception: %s\n", e.what());
      giz->releasePort(portInstance);
      return 0;
    }
    giz->releasePort(portInstance);
    return 0;
  }
  // not reached, we hope.
  return 0;
}

