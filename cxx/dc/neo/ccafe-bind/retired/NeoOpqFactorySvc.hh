#ifndef __NEOOPAQUEFACTORYSERVICE_HH__
#define __NEOOPAQUEFACTORYSERVICE_HH__

#include <vector>
#include <string>

/** A component that exports a Factory Service that Ccaffeine will
    recognize. */


class NeoOpqFactorySvc : public virtual ccafeopq::FactoryService, 
			     public virtual neo::cca::Component {
private:

  NeoFactory_ptr fac;
  neo::cca::Services * svc;

public:
  NeoOpqFactorySvc();

  virtual int setServices(neo::cca::Services * svc);
  virtual const std::vector<std::string> getComponentClassNames();

  // vector<ComponentClassDescription> getComponentClasses() = 0;

  virtual ccafeopq::Component * createComponentInstance(const std::string className);

  virtual void destroyComponentInstance(const std::string componentClassName, 
				ccafeopq::Component * component) {
    // can't do anything, smart pointer will do the work (I hope)
  }
};


#endif // __NEOOPAQUEFACTORYSERVICE_HH__
