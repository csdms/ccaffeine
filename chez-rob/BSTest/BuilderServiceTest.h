// #include <unistd.h>
// #include <stdio.h>
// #include <cca.h>

class BuilderService : public virtual gov::cca::Port {
 private:
 public:

  virtual gov::cca::ComponentID* createLocalInstance(char* fullyQualName,
					       char* instanceName) 
      throw (gov::cca::CCAException) = 0;

};
