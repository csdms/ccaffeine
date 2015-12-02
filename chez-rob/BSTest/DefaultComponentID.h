#ifndef __DEFAULTCOMPONENTID_H__
#define __DEFAULTCOMPONENTID_H__


class DefaultComponentID : public virtual gov::cca::ComponentID {
 private:

  char* fullyQualName;
  char* instanceName;

 public:
  
  virtual ~DefaultComponentID();

  DefaultComponentID(char* fullyQualName, char* instanceName);

  virtual char* toString();
};

#endif // __DEFAULTCOMPONENTID_H__
