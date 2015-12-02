%module BuilderSvc

%{


#include <cca.h>
#include "CCAException.h"
#include "DefaultComponentID.h"
#include "StringList.h"
#include "DefaultStringList.h"
#include "BuilderService.h"

  using namespace gov::cca;

%}

%include ../cca.i
%include ../StringList.i
%include ../DefaultComponentID.i
 


class BuilderService : public virtual Port {

public:
	
  virtual StringList* getComponentClasses();

  virtual ComponentID* getComponentID(char* componentInstanceName);

  virtual ComponentID* createInstance(char* fullyQualName,
				      char* instanceName);
  virtual void destroyInstance(ComponentID* );

  virtual StringList* getContainerNames();

  virtual StringList* getComponentInstanceNames();

  virtual StringList* getProvidesPortStrings(ComponentID* cid);

  virtual StringList* getUsesPortStrings(ComponentID* cid);

  virtual StringList* getConnectionDetails();

  virtual void connect(ComponentID* user, char* usingPortName, 
		       ComponentID* provider, char* providingPortName, 
		       char* connectionName);
  virtual void disconnect(char* connectionName);

  virtual void getConfigurationStrings(ComponentID* cid, char* portName, 
				       StringList* kvl);

  virtual void setConfigurationStrings(ComponentID* cid, char* portName, 
				       StringList* kvl, int start, int count);

  virtual void go(ComponentID* cid, char* portName);

};



