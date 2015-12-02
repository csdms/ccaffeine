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

using namespace gov::cca;

int main(int argc, char** argv) {
  AbstractFramework* fwk = 
   dynamic_cast<AbstractFramework*>
    (new CcaffeineAbstractFramework(argc, argv));
  Services* svc = fwk->getBootstrapServices("test0", "testAbstractFwk", NULL);
  svc->createPortInfo("fooName", "fooType", NULL);
  fprintf(stderr, "For all I know it might have worked!\n");
  exit(0);
}
