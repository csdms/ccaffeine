#ifndef __CLASSICOPAQUEFACTORYSERVICE_HH__
#define __CLASSICOPAQUEFACTORYSERVICE_HH__

#include <vector>
#include <string>

/** A component that exports a Factory Service that Ccaffeine will
    recognize. */


class ClassicOpqFactorySvc : public virtual OpaqueFactoryService, 
			     public virtual classic::gov::cca::Component {
private:

  ClassicFactory_ptr fac;
  classic::gov::cca::Services * svc;

public:
  ClassicOpqFactorySvc();

  virtual int setServices(classic::gov::cca::Services * svc);
  virtual const std::vector<std::string> getComponentClassNames();

  // vector<ComponentClassDescription> getComponentClasses() = 0;
  virtual OpaqueComponent_ptr 
  createComponentInstance(const std::string className);
  virtual void destroyComponentInstance(const std::string componentClassName, 
				OpaqueComponent_ptr component) {
    // can't do anything, smart pointer will do the work (I hope)
  }
};


#endif // __CLASSICOPAQUEFACTORYSERVICE_HH__
