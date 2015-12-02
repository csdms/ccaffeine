#ifndef __NEOCOMPONENTWRAPPER_HH__
#define __NEOCOMPONENTWRAPPER_HH__


class NeoComponentWrapper : public virtual ccafeopq::Component {
private:

  NeoServices * cs;
  neo::cca::Component * cptr;
  NeoServicesHelper csh;

public: 

  NeoComponentWrapper(neo::cca::Component* cmpt) : cs(0), cptr(cmpt) {
  }
  NeoComponentWrapper(int bogon) : cs(0), cptr(0) {
  }


  virtual ~NeoComponentWrapper();

  /** this setservices has the set/setnull semantics of ccafeopq::Component.
   */
  virtual void setServices( ccafeopq::Services * svc)  throw (ccafeopq::Exception);

  /** return the neo pointer */
  neo::cca::Component* getWrapped();
};

#endif // __NEOCOMPONENTWRAPPER_HH__
