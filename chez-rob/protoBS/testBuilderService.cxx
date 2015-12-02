#include <stdio.h>
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
/** Done with BuilderService. */
#include "jc++/util/StringVector.h"
#include "DefaultStringList.h"
// #include "VectorStringList.h"
#include <EG.h>
#include <stdPorts.h>
#include "parameters/parametersStar.h"
// #include "siloon_casts.h"

using namespace gov::cca;

int main(int argc, char** argv) {

  int i, j;
  AbstractFramework* fwk = 
   dynamic_cast<AbstractFramework*>
    (new CcaffeineAbstractFramework(argc, argv));
  /* Get the Services object and make myself a component in the framework. */
  Services* svc = fwk->getBootstrapServices("test0", "testAbstractFwk", NULL);
  /* Now register and get a BuilderService Port */
  PortInfo* info = svc->createPortInfo("myBS", "gov.cca.BuilderService", NULL);
  svc->registerUsesPort(info);
  Port* p = svc->getPort("myBS");
  BuilderService* bs = dynamic_cast<BuilderService*>(p);CHECKDC(bs);
  /* We have the Builder Service, now create components, and connect
     them and do some stuff. */
  StringList* list = bs->getComponentClasses();
  fprintf(stderr, "there are %d available classes:\n", list->getSize());
  for(i = 0;i < list->getSize();i++) {
    char* className = list->get(i);
    fprintf(stdout, "%s\n", className);
  }
  delete list;
  ComponentID* print = bs->createInstance("PrinterComponent", "print0");
  fprintf(stderr, "Instantiated %s\n", print->toString());
  ComponentID* start = bs->createInstance("StarterComponent", "start0");
  fprintf(stderr, "Instantiated %s\n", start->toString());
  list = bs->getComponentInstanceNames();
  fprintf(stderr, "Here are the component instances in the arena:\n");
  for(i = 0;i < list->getSize();i++) {
    ComponentID* cid = bs->getComponentID(list->get(i));
    fprintf(stderr, "\nComponent instance %d: %s\n", i, list->get(i));
    fprintf(stderr, "\n\tProvides Ports:\n");
    StringList* l = bs->getProvidesPortStrings(cid);
    fprintf(stderr, "\t   Instance Name \tClass Name\n");
    for(j = 0;j < l->getSize();j += 2) {
      fprintf(stderr, "\t%d) %s \t\t%s\n", j, l->get(j), l->get(j+1));
    }
    delete l;
    l = bs->getUsesPortStrings(cid);
    fprintf(stderr, "\n\tUses Ports:\n");
    fprintf(stderr, "\t   Instance Name \tClass Name\n");
    for(j = 0;j < l->getSize();j += 2) {
      fprintf(stderr, "\t%d) %s \t\t%s\n", j, l->get(j), l->get(j+1));
    }
    delete l;
  }
  bs->connect(start, "out0", print, "printer_port", "aConnection");
  bs->go(start, "go_port");
  // Self connection test.

  // Note that StringConsumerPort is inconsistently named, it should
  // be gov.cca.StringConsumerPort, unfortunately that is how
  // PrinterComponent does it, we must comply.
  fprintf(stderr, "\n\nSelf Connection Test:\n\n");
  svc->registerUsesPort(svc->createPortInfo("myStringPort", 
					    "StringConsumerPort", 
					    NULL) );
  ComponentID* myID = svc->getComponentID();
  fprintf(stderr, "My name is: %s, printer name is: %s\n", 
	  myID->toString(), print->toString());
  bs->connect(myID, "myStringPort", print, "printer_port", "bConnection");
  gov::cca::StringConsumerPort* scp = 
    dynamic_cast<gov::cca::StringConsumerPort*>(svc->getPort("myStringPort"));
  CHECKDC(scp);
  scp->setString("Hello CCA World");
}
