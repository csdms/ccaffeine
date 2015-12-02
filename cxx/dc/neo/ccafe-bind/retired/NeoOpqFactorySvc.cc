#include "dc/neo/ccafe-bind/NeoOpqFactorySvc.hh"

NeoOpqFactorySvc::NeoOpqFactorySvc() {
    fac = NeoFactory_ptr(new NeoFactory());
    fac->setDebug(true);
    fac->initPallet();
    string path = stp_getn("neo", "path");
    string * pathList = parsePath(path);
    fac->setComponentPath(pathList);
    destroyPath(pathList);
    int numCmpts = fac->searchComponentPath();
    if(numCmpts <= 0) {
      IO_dn1("Warning: No components found.");
    }
}
int 
NeoOpqFactorySvc::setServices(neo::cca::Services * svc) {
    this->svc = svc;
    PortInfo* pi = svc->createPortInfo("OpaqueFactoryService", 
				       "neoFactory", 0);
    svc->addProvidesPort((OpaqueFactoryService*)this, pi);
    return 0;
  }
  const std::vector<std::string> 
NeoOpqFactorySvc::getComponentClassNames() {
    std::vector<std::string> ret;
    string * l = fac->getLoadedComponents();
    string * u = fac->getUnloadedComponents();
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
ccafeopq::Component *
NeoOpqFactorySvc::createComponentInstance(const std::string className) {
    int s = fac->componentStatus(className.c_str());
    if(s == -1) {
      IO_dn2("Nonexistent name for component: %s", 
	     className.c_str());
      return 0;
    }
    if(s == 0) {
// FIXME fac? default should be global or per xml private-- it's c++.
      fac->loadPallet(className.c_str(), false /* not global */, 
		      true /* is lazy */);
      neo:gov::cca::Component * c = 
		fac->instantiate(className.c_str(), 0);
      NeoComponentWrapper *ncomp = new NeoComponentWrapper(c);
      return ncomp;
    }
  }

std::vector<string>
NeoOpqFactorySvc::parsePath(string path) {
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

