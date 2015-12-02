#ifndef __DEFAULTBUILDERSERVICE_H__
#define __DEFAULTBUILDERSERVICE_H__

// #include <unistd.h>
// #include <stdio.h>
// #include <cca.h>

class DefaultBuilderService : public virtual BuilderService {


 private:

  char* fullyQualName;
  char* instanceName;

 public:
  
  DefaultBuilderService();  

  virtual ~DefaultBuilderService();
  
  /** Tell the framework to create an instance of this component from
      its pallet of components. */
  virtual gov::cca::ComponentID* 
    createLocalInstance(char* fullyQualName, char* instanceName)
    throw (gov::cca::CCAException);
  };

#endif // __DEFAULTBUILDERSERVICE_H__
