#ifndef __CCAFECONNECTION_H__
#define __CCAFECONNECTION_H__

class CcafeConnection : public virtual jcpp::Object {
 public:
  char* providingInstance;
  char* providingPortName;
  char* usingInstance;
  char* usingPortName;
  CcafeConnection(char* providingInstance, char* providingPortName, 
		  char* usingInstance, char* usingPortName) {
    this->providingInstance = providingInstance;
    this->providingPortName = providingPortName;
    this->usingInstance = usingInstance;
    this->usingPortName = usingPortName;
  }
  virtual ~CcafeConnection(){}
};

#endif // __CCAFECONNECTION_H__

