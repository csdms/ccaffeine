#include "dc/classic/ccafe-bind/ClassicOpqFactorySvc.hh"

ClassicOpqFactorySvc::ClassicOpqFactorySvc() {
    fac = ClassicFactory_ptr(new ClassicFactory());
    fac->setDebug(true);
    fac->initPallet();
    string path = stp_getn("classic", "path");
    char** pathList = parsePath(path);
    fac->setComponentPath(pathList);
    destroyPath(pathList);
    int numCmpts = fac->searchComponentPath();
    if(numCmpts <= 0) {
      IO_dn1("Warning: No components found.");
    }
}
int 
ClassicOpqFactorySvc::setServices(classic::gov::cca::Services * svc) {
    this->svc = svc;
    PortInfo* pi = svc->createPortInfo("OpaqueFactoryService", 
				       "classicFactory", 0);
    svc->addProvidesPort((OpaqueFactoryService*)this, pi);
    return 0;
  }
  const std::vector<std::string> 
ClassicOpqFactorySvc::getComponentClassNames() {
    std::vector<std::string> ret;
    char** l = fac->getLoadedComponents();
    char** u = fac->getUnloadedComponents();
    int i = 0;
    while((l[i] != NULL) && (l[i+1] != NULL)) {
      string s = STRDUP(l[i+1]);
      ret.push_back(s);
      i += 2
    }
    i = 0
    while((u[i] != NULL) && (u[i+1] != NULL)) {
      string s = STRDUP(u[i+1]);
      ret.push_back(s);
      i += 2
    }
    return ret;
  }
OpaqueComponent_ptr 
ClassicOpqFactorySvc::createComponentInstance(const std::string className) {
    int s = fac->componentStatus(className.c_str());
    if(s == -1) {
      IO_dn2("Nonexistent name for component: %s", 
	     className.c_str());
      return OpaqueComponent_ptr(0);
    }
    if(s == 0) {
      fac->loadPallet(className.c_str(), false /* not global */, 
		      true /* is lazy */);
      classic:gov::cca::Component * c = 
		fac->instantiate(className.c_str(), 0);
      return OpaqueComponent_ptr(new ClassicComponentWrapper(c));
    }
  }

std::vector<string>
ClassicOpqFactorySvc::parsePath(string path) {
  std::vector< string > ret;
  int b = 0;
  int l = path.find(':');
  int npos = path.find('%'); // the nonexistent return value.
  while(l != npos) {
    string s = path.substr(b, l);
    ret.push_back(s);
    b = l;
    l = path.find(':');
  }
  ret.push_back(path.substr(b, path.size()));
  return ret;
}

