#ifndef __SELFPROXYFACTORY_HH__
#define __SELFPROXYFACTORY_HH__

class ProxyClass : public virtual ccafeopq::Component {
private:
  ccafeopq::Services * svc;
public:
  virtual ~ProxyClass(){}
  ProxyClass() {
    svc = 0;
  }
  virtual void setServices(ccafeopq::Services * svc) throw () {
    this->svc = svc;
  }
  ccafeopq::Services * getServices() {
    return svc;
  }
};

#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr< ProxyClass > ProxyClass_ptr;


class SelfProxyFactory : public virtual XCmptFactory {
private:

  std::string myType;
  std::map< std::string, ProxyClass * > proxies;

public:
  virtual ~SelfProxyFactory(){}
  
  SelfProxyFactory(const ::std::string & myType) {
    this->myType = myType;
  }

  virtual ::std::vector< ::std::string> getComponentClassNames() {
    ::std::vector< ::std::string> v;
    v.push_back(myType);
    return v;
  }

  virtual bool hasComponent( const ::std::string & cmptType) {
    return (cmptType == myType);
  }

  virtual ccafeopq::Component * instantiate( const ::std::string & cmptType) {
    if(proxies.find("Unknown") != proxies.end()) {
      IO_en1(":-( attempt to instantiate new proxy when a previous instance "
	    "has been unnamed\n replacing the old instance with a new one");
    }
    proxies["Unknown"] = new ProxyClass();
    return proxies["Unknown"];
  }

  virtual void destroy(const std::string & s, ccafeopq::Component*c) {
	  // FIXME 
  }

  void setLastInstanceToName(std::string instName) {
    if(proxies.find("Unknown") == proxies.end()) {
      IO_en2(":-( attempt to name (%s) a non-existent last instance, "
	     "doing nothing", instName.c_str());
      return;
    }
    proxies[instName] = proxies["Unknown"];
    proxies.erase("Unknown");
  }

  ccafeopq::Services * getServicesFor(std::string instName) {
    if(proxies.find(instName) == proxies.end()) {
      IO_en2(":-( attempt to retrieve a nonexistent proxy class with "
	     "instance name %s, returning NULL", instName.c_str());
      return NULL;
    }
    ProxyClass * p = proxies[instName];
    return p->getServices();
  }

};

typedef boost::shared_ptr< SelfProxyFactory > SelfProxyFactory_ptr;


#endif //__SELFPROXYFACTORY_HH__
