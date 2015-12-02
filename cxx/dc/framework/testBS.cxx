#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: testBS.cxx,v 1.9 2005/11/10 00:08:22 baallan Exp $";
} ENDSEMI

using namespace std;
#ifdef HAVE_BABEL_CARA
#include <iostream>
#include <stdlib.h>
int main(int argc, char* argv[]) {
	cerr << "This test cannot yet build standalone when babel is enabled." << endl;
	exit(1);
}

#else // havebabel

#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
#include "util/IO.h"
#include <jc++/jc++.h>
#include <jc++/lang/jc++lang.h>
#include <jc++/util/jc++util.h>
#include <jc++/io/jc++io.h>
#include <jc++/jc++dynamic.h>
#include <parameters/parametersStar.h>
#include <parameters/parametersDynamic.h>
#include <port/supportInterfaces.h>
#include <dc/export/AllExport.hh>
#include <dc/port/portStar.h>
#include <dc/port/Caffeine_Port_DynamicLink.h>
#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/DefaultBuilderModel.h"

#include "util/freefree.h"

int forceLink() {
  // This should not be optimized away, as a C++ compiler has
  // no business assuming the lack of global side effects.
  // don't actually instantiate the pieces in jc++
  Caffeine_Port_DynamicLink* cpdl = new Caffeine_Port_DynamicLink(0);
  JCPP_DynamicLink *jdl = new JCPP_DynamicLink(0);
  parameters_DynamicLink *pdl = new parameters_DynamicLink(0);
  delete jdl;
  delete pdl;
  delete cpdl;
  return 0;
}

int main(int argc, char* argv[]) {
  forceLink(); 
  int err;
  DefaultBuilderModel * bm = new DefaultBuilderModel(err,0,0);
  ConnectionFramework * fwk = bm->getFramework();
  if (fwk == 0 || err != 0) {
    IO::en((char *)"ERROR:  failed to get ConnectionFramework");
    return -1;
  }
  ComponentFactory_shared cf = fwk->getBaseComponentFactory();
  if (argc > 1) {
    std::vector< std::string > argv1;
    argv1.push_back(argv[1]);
    cf->setComponentPath(argv1);
  }
  cf->indexComponentPath();
  if ( argc < 2 ) {
    IO::en("You probably need to give a path argument like ../component\n");
    exit(1);
  }

  // should use bm->loadRepositoryClass instead
  cf->loadClass( (char *)"ComplicatedStarterComponent",true,0);
  cf->loadClass( (char *)"ComplicatedPrinterComponent",true,0);
  cf->loadClass( (char *)"StarterComponent",true,0);
  cf->loadClass( (char *)"PrinterComponent",true,0);
  cf->loadClass( (char *)"TimeStamper",true,0);
  cf->loadClass( (char *)"Timer",true,0);
  cf->loadClass( (char *)"BSTest",true,0);
  
  ::std::vector< ::std::string > v = cf->getComponentClassAliases();

  ::ccafeopq::TypeMap_shared tm( static_cast< ::ccafeopq::TypeMap_Interface * >(0));
  ::ccafeopq::TypeMap_shared tm2;
  unsigned int i = 0;
  i = 0;
  cerr << endl;
  cout << endl;
  fflush(0);

  // set 0 next to be noisy
#if 1
  IO::setDebug(false);
  fwk->setDebug(false);
#else
  IO::setDebug(true);
  fwk->setDebug(true);
#endif 
  //ComponentFactory::setDebug(true);
  ComponentInfo_shared bsCI = fwk->instantiate("BSTest", "bs");
  const char * str = 0;
  std::string ts = bsCI->toString();
  str = ts.c_str();
  IO::pn((char *)"%s", str);

  cout << "BSBSBSBS" << endl;
  try {
  fwk->goOne("bs","go");
  }
  catch (::ccafeopq::Exception e)
  {
	  cerr << e.what() << endl;
  }
  catch (std::exception e2)
  {
	  cerr << e2.what() << endl;
  }
  cerr << endl;
  cout << endl;
  fflush(0);

  delete bm;
}
#endif // havebabel
