%module AbstractFwk


%{


#ifndef lint
  static char id[] = 
    "$Id: AbstractFramework.i,v 1.6 2001/08/18 04:29:39 rob Exp $";
#endif
#include <cca.h>
#include "CCAException.h"
#include "DefaultComponentID.h"
#include "StringList.h"
#include "BuilderService.h"
#include "AbstractFramework.h"

  using namespace gov::cca;

  /** For CcaffeineAbstractFramework */

#include "jc++/util/jc++util.h"
#include "ccaFrameworkServices.h"
/** For BuilderModel: */
#include "parameters/parametersStar.h"
#include "jc++/jc++.h"
#include "dc/framework/dc_fwkStar.h"
#include "port/portInterfaces.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/Link.h"
#include "dc/user_iface/DefaultBuilderModel.h"

#include "util/freefree.h"
/** Done with BuilderModel. */

#include "CcaffeineAbstractFramework.h"

#include "CcafeCCAException.h"
#include "jc++/util/jc++util.h"
#include "ComponentProxy.h"
// this is just <getopt.h> under linux but we aren't linux always
// so include our own which is from the gnu distribution.
#include <unistd.h>
#include "gnu/getopt/getCCAFEopt.h"
/** For BuilderService... */
#include "BuilderService.h"
#include "DefaultStringList.h"
#include "CcaffeineBuilderService.h"
/** Done with BuilderService. */
%}

%include ../cca.i
%include ../BuilderSvc.i

class AbstractFramework {
  
public:
  
  virtual ~AbstractFramework();

  virtual Services* getBootstrapServices(char* selfInstanceName, 
					 char* selfClassName, 
					 char** selfProperties);

  virtual void releaseBootstrapServices(Services* svc);

  virtual void shutdownFramework();

  virtual AbstractFramework* createFramework();
};

class CcaffeineAbstractFramework : public AbstractFramework {
  
public:
  
  CcaffeineAbstractFramework(StringList* l);

  ~CcaffeineAbstractFramework();

  virtual Services* getBootstrapServices(char* selfInstanceName, 
					 char* selfClassName, 
					 char** selfProperties);

  virtual void releaseBootstrapServices(Services* svc);

  virtual void shutdownFramework();

  virtual AbstractFramework* createFramework();
};





