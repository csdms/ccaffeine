#ifndef __DEFAULTXCMPTFACTORY_HH__
#define __DEFAULTXCMPTFACTORY_HH__

#include <vector>
#include <string>
#include "dc/framework/XCmptFactory.hh"

class Gizzard;

class DefaultXCmptFactory : public virtual XCmptFactory {
private:

  ::std::string portInstance;

  Gizzard * giz;
  int last;
  ::std::string lastCmpt;

public:

  static XCmptFactory_shared createFactory(Gizzard * giz, const std::string & portInstance);

  virtual ~DefaultXCmptFactory(){}

  DefaultXCmptFactory(Gizzard * giz, ::std::string portInstance);

  virtual ::std::vector< ::std::string> getComponentClassNames();

  virtual bool hasComponent( const ::std::string & cmptType);

  virtual ccafeopq::Component * instantiate( const ::std::string & cmptType);
  virtual void destroy( const ::std::string & cmptType, ccafeopq::Component *c);

};

typedef boost::shared_ptr< DefaultXCmptFactory > DefaultXCmptFactory_ptr;

#endif // __DEFAULTXCMPTFACTORY_HH__
