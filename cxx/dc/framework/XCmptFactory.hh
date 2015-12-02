#ifndef __XCMPTFACTORY_HH__
#define __XCMPTFACTORY_HH__

#include <vector>
#include <string>

class Gizzard;
class XCmptFactory;

typedef boost::shared_ptr< XCmptFactory > XCmptFactory_shared;

class XCmptFactory {
private:

public:

  virtual ~XCmptFactory(){}

  virtual ::std::vector< ::std::string> getComponentClassNames() = 0;

  virtual bool hasComponent( const ::std::string & cmptType) = 0;

  /** create by name given */
  virtual ccafeopq::Component * instantiate( const ::std::string & cmptType) = 0;

  /** destroy by name given if it's one this factory made. */
  virtual void destroy( const ::std::string & cmptType, ccafeopq::Component *victim ) = 0;

};


#endif // __XCMPTFACTORY_HH__
