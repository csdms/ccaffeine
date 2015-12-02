#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include "cca.h"
#endif
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "parameters/parametersStar.h"
#include "port/supportInterfaces.h"
#include "dc/port/DefaultParameterPort.h"
#include "dc/port/DefaultConfigurableParameterFactory.h"

DefaultConfigurableParameterFactory::DefaultConfigurableParameterFactory() { };

ConfigurableParameterPort *DefaultConfigurableParameterFactory::createConfigurableParameterPort()
{
  ConfigurableParameterPort *foo;
  DefaultParameterPort *dpp;
  dpp = new DefaultParameterPort();
  foo = dynamic_cast<ConfigurableParameterPort *>(dpp);
  return foo;
}

