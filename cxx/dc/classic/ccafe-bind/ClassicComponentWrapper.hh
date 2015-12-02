#ifndef __CLASSICCOMPONENTWRAPPER_HH__
#define __CLASSICCOMPONENTWRAPPER_HH__

class ClassicServicesHelper;

class ClassicComponentWrapper : public virtual ccafeopq::Component {
private:

  ClassicServices * cs;
  classic::gov::cca::Component* cptr;
  ClassicServicesHelper *csh_ptr;

public: 

  ClassicComponentWrapper(classic::gov::cca::Component* cmpt);

  virtual ~ClassicComponentWrapper();

  virtual void setServices( ccafeopq::Services * svc)  throw (ccafeopq::Exception);

};

#endif // __CLASSICCOMPONENTWRAPPER_HH__
