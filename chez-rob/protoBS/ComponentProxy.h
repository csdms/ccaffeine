#ifndef __COMPONENTPROXY_H__
#define __COMPONENTPROXY_H__

// #include <cca.h>
// #include "jc++util.h"


/** A proxy class that is for use with AbstractFramework
 * implementations.  This will be seeded in the framework from
 * instantiation.  The create method in CcaffeineAbstractFramework
 * simply hands back an already created proxy that fronts for the real
 * entity trying that wants to look like a component.  */

class ComponentProxy : public virtual gov::cca::Component, 
		       public virtual jcpp::Object /* For class StringHash */ {
 private:

  gov::cca::Services* svc;
  char* instanceName;

 public:
  ComponentProxy();

  virtual void setServices(gov::cca::Services* svc);

  /** Get the Services object that has been set on this proxy, or NULL
      if it has not been set yet. */
  virtual gov::cca::Services* getServices();

  /** Set the instance name for this ComponentProxy. */
  virtual void setInstanceName(char* instanceName);
  
  /** Get the instance name for this ComponentProxy. */
  virtual CFREE char* getInstanceName();
};

#endif // __COMPONENTPROXY_H__
