#ifndef __CLASSICCOMPONENTID_HH__
#define __CLASSICCOMPONENTID_HH__

class ClassicComponentID : public virtual classic::gov::cca::ComponentID {

private:

  ::ccafeopq::ComponentID_shared cid;

public:

  virtual ~ClassicComponentID(){}

  ClassicComponentID(ccafeopq::ComponentID_shared & cid_) {
    cid = cid_;
  }

  virtual CFREE char* toString(); // oddly, located in ClassicServices.cc

};

#endif // __CLASSICCOMPONENTID_HH__
