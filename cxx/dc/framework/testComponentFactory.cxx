#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: testComponentFactory.cxx,v 1.20 2004/12/08 23:01:56 baallan Exp $";
} ENDSEMI

#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO

#ifdef HAVE_BABEL_CARA
#include <iostream>
#include <stdlib.h>
using namespace std;
int main(int argc, char* argv[]) {
	cerr << "This test cannot yet build standalone when babel is enabled." << endl;
	exit(1);
}
#else // havebabel

#include <util/IO.h>
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
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
#include <string>
#include <vector>
#include "ComponentRecord_Impl.h"
#include "KernelPort.h"
#include "ComponentRegistrar.h"
#include "ComponentFactory.h"

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


int cf_test(ComponentFactory &cf) {

 
  cf.dumpFactory();
  std::cout << "======== creating ============ " << std::endl;
#if 0
  cf.loadPalette( (char *)"PrinterComponent",0,0);
  // cf.loadPalette( (char *)"RevalidateTest",0,0);
  cf.loadPalette( (char *)"StarterComponent",0,0);
  cf.loadPalette( (char *)"TimeStamper",0,0);
  cf.loadPalette( (char *)"Timer",0,0);
#endif
  cf.loadPalette( (char *)"OPPFTest",0,0);

  ::std::vector< ::std::string > v = cf.getPalette();
  size_t i = 0;
  for( ; i < v.size(); i++) {
    IO::en("component%d = %s", i, v[i].c_str());  
  }
  ccafeopq::Component *ci = 0;
  if (i == 0) {
    IO::en("Empty pallet!");
    return 1;
  } else {
    for( i = 0 ; i < v.size(); i++) {
	  // fixme create 1 each.
	  // destroy create 1 each.
      ci = cf.instantiate(v[i].c_str());
      if (ci != 0) {
        std::cout << "Created " << v[i] << std::endl;
        cf.destroyComponentInstance(v[i], ci);
        std::cout << "Destroyed " << v[i] << std::endl;
      } else {
        std::cout << "Failed instantiate " << v[i] << std::endl;
      }
    }

    ci = 0;
  }
  v.clear();
  return 0;

}

int main(int argc, char** argv) {
  forceLink();
  ComponentFactory cf;
  if (argc > 1) {
    const char **argv1;
    argv1 = const_cast<const char **>( &(argv[1]) );
    cf.setComponentPath(argv1);
  }
  int found = 0;
  found = cf.searchComponentPath();
  IO::en("Found %d components.", found);
  if ( found < 1 || argc < 2 ) {
    IO::en("You probably need to give a path argument like ../component\n");
    exit(1);
  }
  int i = cf_test(cf);
  std::vector< std::string > pf = cf.getParsedFiles();
  for(size_t i = 0 ; i < pf.size(); i++) {
    IO::en("Read metadata file: %s", pf[i].c_str());  
  }
  return i;

}
#endif //endif
