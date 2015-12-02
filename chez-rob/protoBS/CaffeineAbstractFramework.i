%{

#include <cca.h>
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

class CcaffeineAbstractFramework : public AbstractFramework {

  virtual Services* getBootstrapServices(char* selfInstanceName, 
					 char* selfClassName, 
					 char** selfProperties);

  virtual void releaseBootstrapServices(Services* svc);

  virtual void shutdownFramework();

  virtual AbstractFramework* createFramework();

};
