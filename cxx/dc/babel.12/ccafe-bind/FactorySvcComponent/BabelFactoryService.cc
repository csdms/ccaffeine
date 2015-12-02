#include <vector>
#include <string>

using namespace std;

#include <cca.h>
#include "util/IO.h"

#include "dc/export/AllExport.hh"
#ifdef _AIX
/** on aix, /usr/include/sys/proc.h
  defines SIDL. bad. bad.
 */
#undef SIDL
#endif // OS_AIX
#include <SIDL_Loader.hxx>
#include "AllCCA.hh"
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hxx"
#include "util/StringTools.hh"
#include "stovepipe/stp.h"
#include "dc/babel.12/ccafe-bind/FactorySvcComponent/BabelFactoryService.hxx"


BabelFactoryService::BabelFactoryService() {
  IO_dn1("BabelFactoryService::BabelFactoryService  entry");
  bypassPaths = true;
  if (!bypassPaths) {
    char * p = getenv("SIDL_DLL_PATH");
    if(p != NULL) {
      path = StringTools::chomp(p);
    }
    string s = StringTools::chomp(std::string(stp_getn("babel", "path")));
    if(s.size() >= 0) {
      path += ";" + s; 
    }
    SIDL::Loader::setSearchPath(path.c_str());
  }
    
  const char * cmpts = stp_getn("babel", "components");    
  if(cmpts != NULL) {
    IO_dn2("raw --babel-components = %s", cmpts);
    compList = StringTools::split(cmpts);
  }
  for(int i = 0;i < compList.size();i++) {
    IO_dn2("compList[i] = %s", compList[i].c_str());
  }

  initKernel();
}
  /** 
   * All created components will be returned to the factory for
   * destruction. exception if class unknown.
   */
ccafeopq::Component * 
BabelFactoryService::createComponentInstance(const  std::string & className) 
  throw (ccafeopq::Exception) {
  gov::cca::Component c;
  IO_dn2("createComponentInstance called for %s", className.c_str());
  try {
    c = SIDL::Loader::createClass(className.c_str());
  } catch(std::exception e) {
    IO_dn2("Exception: %s\n", e.what());
    throw ccafeopq::Exception(string(e.what()));
  }
  return new BabelComponentWrapper(c);
}

std::vector< ::ccafeopq::ComponentClassDescription_shared > getComponentClasses()
{
  std::vector< ::ccafeopq::ComponentClassDescription_shared > ccds;

  throw ::ccafeopq::Exception("BabelFactoryService.cc: getComponentClasses unimplemented");
  return ccds;
}

::ccafeopq::Component *createComponentInstance (const std::string & className, ::ccafeopq::TypeMap_shared & properties)
{
  ::ccafeopq::Component *c = 0;
  throw ::ccafeopq::Exception("BabelFactoryService.cc: createComponentInstance(s,tm) unimplemented.");
  return c;
}

void 
BabelFactoryService::destroyComponentInstance(const std::string & componentClassName, ::ccafeopq::Component * component) 
  throw ( ::ccafeopq::Exception ) {
  delete component;
}

std::vector< std::string > 
BabelFactoryService::getComponentClassNames() {
  return compList;
}

void
BabelFactoryService::setServices(ccafeopq::Services * svc) 
  throw (ccafeopq::Exception) {
  IO_dn1("BabelFactoryService::setServices entry");
  std::map<std::string, std::string> nilMap;
  ccafeopq::PortInfo * opi = 
    svc->createPortInfo(std::string("BabelFactoryService"), 
			std::string("ccafeopq::FactoryService"), 
			nilMap);
  svc->addProvidesPort(this, opi);
}
