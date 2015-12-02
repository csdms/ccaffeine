%module BuilderSvc

%{


#ifndef lint
static char id[] = 
"$Id: BuilderSvc.i,v 1.2 2002/02/02 21:41:29 rob Exp $";
#endif
#include <cca.h>
#include "../CCAException.h"
#include "../DefaultComponentID.h"
#include "../BuilderServiceTest.h"
#include "../DefaultBuilderService.h"

using namespace gov::cca;

%}

class ComponentID {
public:	
   char* toString();
};

class DefaultComponentID {
	DefaultComponentID();
	virtual ~DefaultComponentID();
	char* toString();
};

class Port {
};

class BuilderService : public virtual Port {
 private:
 public:
	
    virtual ComponentID* createLocalInstance(char* fullyQualName,
        				     char* instanceName);

};

class DefaultBuilderService : public virtual BuilderService {
 private:
 public:

	DefaultBuilderService();
	virtual ~DefaultBuilderService();

    ComponentID* createLocalInstance(char* fullyQualName,
				     char* instanceName);
};


