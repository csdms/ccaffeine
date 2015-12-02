#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: testConnectionFwk.cxx,v 1.22 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

#ifdef HAVE_BABEL_CARA
#include <iostream>
#include <stdlib.h>
using namespace std;
int main(int argc, char* argv[]) {
				std::cerr << "This test cannot yet build standalone when babel is enabled." << std::endl;
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
  int err;
  forceLink(); 
  ConnectionFramework* fwk = new ConnectionFramework(err);
  if (fwk == 0 || err != 0) {
    IO::en((char *)"ERROR:  failed to create new ConnectionFramework");
    return -1;
  }
  ComponentFactory_shared cf = fwk->getBaseComponentFactory();
  if (argc > 1) {
    std::vector< std::string > argv1;
    argv1.push_back(argv[1]);
    cf->setComponentPath(argv1);
  }
  cf->indexComponentPath();
  if (argc < 2 ) {
    IO::en("You probably need to give a path argument like ../component\n");
    exit(1);
  }

  cf->loadClass( (char *)"StarterComponent",true,0);
  cf->loadClass( (char *)"PrinterComponent",true,0);
  cf->loadClass( (char *)"TimeStamper",true,0);
  cf->loadClass( (char *)"Timer",true,0);
  cf->loadClass( (char *)"OPPFTest",true,0);
  
  ::std::vector< ::std::string > v = cf->getComponentClassAliases();
  ::ccafeopq::TypeMap_shared tm( static_cast< ::ccafeopq::TypeMap_Interface * >(0));
  ::ccafeopq::TypeMap_shared tm2;
  unsigned int i = 0;
  i = 0;
    IO::pn("TESTING instantiation of all on palette.");
  for ( ; i < v.size(); i++) {
    std::string sn = v[i];
    std::string cn = v[i];
    const char * name = sn.c_str();
    IO::pn((char *)"item #%d: %s", i, name);
    sn += "0";
    ComponentInfo_shared ci;
    ci = fwk->instantiate(cn, sn, tm);
    std::string str;
    str = ci->toString();
    IO::pn((char *)"%s", str.c_str());
  }
  IO::pn("TESTING instantiation of all on pallet done.");
  // what does this do again? if 7 components, try fred setup.
  if (i ==8) {
	  bool f2 = tm2->hasKey("fred");
  }
  
  if (i == 0) {
    IO::pn("Pallet empty. dynamic linking problem maybe?");
    IO::pn("bye bye.");
    exit(1);
  }
  IO::pn("TESTING printer assembly.");
  ComponentInfo_shared starterCI = fwk->instantiate("StarterComponent", "aStarter", tm);

  ComponentInfo_shared printerCI = fwk->instantiate("PrinterComponent", "aPrinter");
  
  ComponentInfo_shared stamperCI = fwk->instantiate("TimeStamper", "aStamper");

  ComponentInfo_shared timerCI = fwk->instantiate("Timer", "aTimer");
  
  fwk->connect("aStamper", (char *)"in_port",      "aStarter",  (char *)"out0");
  fwk->connect("aTimer",   (char *)"time_port",    "aStamper",  (char *)"time0");
  fwk->connect("aPrinter", (char *)"printer_port", "aStamper",  (char *)"out0");
  IO::pn("TESTING printer assembly done.");
  IO::pn("TESTING printer compute.");
  fwk->goOne("aStarter", "go_port");
	std::cerr << std::endl;
	std::cout << std::endl;
  IO::pn("TESTING printer compute done.");
  fflush(0);

  IO::pn("TESTING OPPF");
  ComponentInfo_shared oppfCI = fwk->instantiate("OPPFTest", "OT1");
  fwk->goOne("OT1", "go");
	std::cerr << std::endl;
	std::cout << std::endl;
  IO::pn("TESTING OPPF done");
  fflush(0);

  IO::pn("shutting down");

  IO::pn("deleting fwk");
  delete fwk;
  IO::pn("done");
}
#endif // havebabel
