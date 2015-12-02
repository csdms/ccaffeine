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

/** This is a Ccaffeine implementation of Abstract framework.  It
 * creates a proxy component that stands in for the external caller
 * that wants a bootstrapServices.  It relies heavily on the
 * asynchronous features within the framework, for example,
 * ComponentChangedListener, to keep the framework up to date.  It
 * will only be after the setServices() call on the proxy component
 * completes that the external caller will have a chance to register
 * or add ports to the system.
 * */


/** This is the ComponentProxy creators, we must declare them
 *    statically and ahead of time because we cannot create a function
 *    pointer dynamically (can we?).  */
extern "C" {

  static char* ComponentProxyName0 = "ComponentProxy0_";
  static gov::cca::Component *ComponentProxy0 = 0;
  static gov::cca::Component *get_ComponentProxy0() {
    return ComponentProxy0;
  }
  
  static char* ComponentProxyName1 = "ComponentProxy1_";
  static gov::cca::Component *ComponentProxy1 = 0;
  static gov::cca::Component *get_ComponentProxy1() {
    return ComponentProxy1;
  }
  
  static char* ComponentProxyName2 = "ComponentProxy2_";
  static gov::cca::Component *ComponentProxy2;
  static gov::cca::Component *get_ComponentProxy2() {
    return ComponentProxy2;
  }
  
  static char* ComponentProxyName3 = "ComponentProxy3_";
  static gov::cca::Component *ComponentProxy3;
  static gov::cca::Component *get_ComponentProxy3() {
    return ComponentProxy3;
  }
  
  static char* ComponentProxyName4 = "ComponentProxy4_";
  static gov::cca::Component *ComponentProxy4;
  static gov::cca::Component *get_ComponentProxy4() {
    return ComponentProxy4;
  }

  static gov::cca::Component** CmptProxy[] = { &ComponentProxy0,
						 &ComponentProxy1,
						 &ComponentProxy2,
						 &ComponentProxy3,
						 &ComponentProxy4  };
  typedef gov::cca::Component *(*CmptProxyFnPtrDef)(void);
  static CmptProxyFnPtrDef CmptProxyFnPtr[] = { get_ComponentProxy0,
						  get_ComponentProxy1,
						  get_ComponentProxy2,
						  get_ComponentProxy3
						  };
  static char* CmptProxyName[] = { "ComponentProxy0_",
				     "ComponentProxy1_",
				     "ComponentProxy2_",
				     "ComponentProxy3_",
				     "ComponentProxy4_",
				     };
  static int numCmptProxy = 5;
};



/* Arguments indicate the environment that the Framework will find
   *       itself in: e.g. how many processors, whether MPI/PVM has
   *       already been initiated, etc.  */

CcaffeineAbstractFramework::CcaffeineAbstractFramework(int argc, 
						       char** argv) {
  
  initArgv = (char**)malloc(sizeof(char*)*argc);
  for(int i = 0;i < argc;i++) {
    initArgv[i] = strdup(argv[i]);
  }
  initArgc = argc;
  optionDebug = TRUE;
  parseArgs(initArgc, initArgv);
  initComponentFactory();

  /** Some Ben-isms.*/
  int notfound;
  bm = new DefaultBuilderModel(notfound);
  builder = new CcaffeineBuilderService(bm);
  exteriorComponents = new jcpp::StringHash();
  shutdown = FALSE;
  count = 0;
}

CcaffeineAbstractFramework::CcaffeineAbstractFramework(gov::cca::StringList* list) {

  debug = TRUE;
  if(debug) {
    fprintf(stderr, "CcaffeineAbstractFramework::CcaffeineAbstractFramework(gov::cca::StringList* list) entry\n");
    fprintf(stderr, "list = 0x%x\n", list);
    fprintf(stderr, "list->size() = %d\n", list->size());
  }
  if(list->size() > 0) {
    initArgv = (char**)malloc(sizeof(char*)*list->size());
    for(int i = 0;i < list->size();i++) {
      initArgv[i] = strdup(list->get(i));
    }
    initArgc = list->size();
    optionDebug = TRUE;
    parseArgs(initArgc, initArgv);
  }
  initComponentFactory();

  /** Some Ben-isms.*/
  int notfound;
  bm = new DefaultBuilderModel(notfound);
  builder = new CcaffeineBuilderService(bm);
  exteriorComponents = new jcpp::StringHash();
  shutdown = FALSE;
  count = 0;
}

CcaffeineAbstractFramework::~CcaffeineAbstractFramework() {
  if(shutdown == FALSE) {
    shutdownFramework();
  }
}

void
CcaffeineAbstractFramework::initComponentFactory() {
  ComponentFactory::initPallet();
  char* setPath[] = { "/home/rob/cca/dccafe-classic/cxx/dc/component", 0};
  ComponentFactory::setComponentPath(setPath);
  ComponentFactory::searchComponentPath();
  char** comp = ComponentFactory::getUnloadedComponents();
  for(int i = 0;comp[i] != 0;i += 2) {
    ComponentFactory::loadPallet(comp[i + 1], true, true);
  }
}
  
void
CcaffeineAbstractFramework::parseArgs(int argc, char** argv) {
  char* usage = "%s [--with-MPI]";
  char* theOption;
  
  if(argc == 1) {
    return;
  }
  while (1)
    {
      int option_index = 0;
      static struct CCAFEoption long_options[] =
      {
        {"with-MPI", no_argument, 0, 0},
	  //	  {"file", required_argument, 0, 0},
	  {0, 0, 0, 0}
      };
      int c = getCCAFEopt_long (argc, argv, "m",
				long_options, &option_index);
      if (c == -1) {
        break;
      }

      switch (c)
        {
        case 0: // opt_long --name, or --file or, whatever
          theOption = (char*)long_options[option_index].name;
	  if(optionDebug) {
	    printf("option:%s\n", theOption);
	    if (optarg)
	      printf (" with arg %s", optarg);
	    printf ("\n");
	  }
          break;
        default: // fell through to error.
          IO::pn(usage, argv[0]);
          exit(-1);
        }
      if(strcmp(theOption, "with-MPI") == 0) {
	withMPI = true;
	//      } else if(strcmp(theOption, "file") == 0) {
	//        procFile = optarg;
	//      }
      } else {
        printf("Bad option: %s", theOption);
        IO::pn(usage, argv[0]);
        exit(-1);
      }
    }
}


gov::cca::Services* 
CcaffeineAbstractFramework::getBootstrapServices(char* selfInstanceName, 
						 char* selfClassName, 
						 char** selfProperties) 
  throw (gov::cca::CCAException) {
  if(shutdown == TRUE) {
    throw new CcafeCCAException(":-( Framework has not been created yet, or has been already shutdown");
  }
  if(count >= numCmptProxy) {
    throw new CcafeCCAException(":-( CcaffeineAbstractFramework::getBootstrapServices ran out of ComponentProxies, limit is %d", numCmptProxy);
  }
  if(exteriorComponents->get(selfInstanceName) != NULL) {
    char* msg = ":-( CcaffeineAbstractFramework::getBootstrapServices: selfInstanceName = %s already exists, please choose another.";
    IO::en(msg, selfInstanceName);
    throw new CcafeCCAException(msg, selfInstanceName);
  }
  ComponentProxy* p = new ComponentProxy();
  *(CmptProxy[count]) = (gov::cca::Component*)p;
  //  ComponentFactory::addClass(CmptProxyName[count], 
  //			     CmptProxyFnPtr[count]);
  int status = ComponentFactory::addClass(selfClassName, 
					  CmptProxyFnPtr[count]);
  if(status == -1) {
    throw new CcafeCCAException("CcaffeineAbstractFramework::"
				"getBootstrapServices: class name: %s "
				"already exists.", selfClassName);
  }
  char* instName = bm->pullDownFromPallet(selfClassName, selfInstanceName);
  if(instName == NULL) {
    throw new CcafeCCAException(":-( BuilderModel::pullDownFromPallet instantiation failed");
  }
  count++;
  instName = strdup(instName); // not ours.
  if(strcmp(instName, selfInstanceName) != 0) {
    throw new CcafeCCAException(":-( CcaffeineAbstractFramework::"
				"getBootstrapServices: Instance name: %s "
				"is already in use, component creation "
				"failed.", selfInstanceName);
  }
  p->setInstanceName(selfInstanceName);
  exteriorComponents->put(selfInstanceName, p);
  gov::cca::Services* svc = p->getServices();
  if(svc == NULL) {
    char* msg = "=8-O For some reason, CcaffeineAbstractFramework::getBootstrapServices: p->getServices() is NULL, this will almost certainly cause big problems.";
    IO::en(msg);
    throw new CcafeCCAException(msg);
  }
    Gizzard* g = dynamic_cast<Gizzard*>(svc);CHECKDC(g);
    g->setService("gov.cca.BuilderService", builder);
  return svc;
}

void 
CcaffeineAbstractFramework::releaseBootstrapServices(gov::cca::Services* svc) 
  throw (gov::cca::CCAException) {
  /** Right now we have no way of getting rid of a component. This
      is embarrasing :-} */
  return;
}

gov::cca::AbstractFramework* CcaffeineAbstractFramework::createFramework() 
  throw (gov::cca::CCAException) {
  return new CcaffeineAbstractFramework(initArgc, initArgv);
}

void 
CcaffeineAbstractFramework::shutdownFramework() {
  shutdown = TRUE;
  delete bm;
  delete builder;
  jcpp::StringEnumeration* k = exteriorComponents->keys();
  while(k->hasMoreElements()) {
    char* key = k->nextElement();
    ComponentProxy* cp = 
      dynamic_cast<ComponentProxy*>(exteriorComponents->get(key));
    delete cp;
    free(key);
  }
  for(int i = 0;i < initArgc;i++) {
    free(initArgv[i]);
  }
  free(initArgv);
}
