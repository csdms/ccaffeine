#include "dc/framework/ComponentRegistrar.h"
#include "dc/framework/StaticFactory.h"
#include "dc/framework/BabelStaticFactory.h"
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/KernelPort.h"

#ifdef HAVE_BABEL
#include "AllCCA.hh"

#if BSUF == 100
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"
#include "dc/babel.new/ccafe-bind/AllCcafeBind.hh"
#endif
#if BSUF == 120
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
#endif

#ifdef _CCAMPI
#if BSUF == 100
#include "dc/babel.new/component/MPIComponent/server/ccafe6_MPIComponent.hxx"
#endif
#if BSUF == 120
#include "dc/babel.12/component/MPIComponent/server/ccafe6_MPIComponent.hxx"
#endif
#endif

// there's a more templatey way to do this.
#define CREATEDEF(cxxName,mangle) \
static void *create_##mangle() \
{  \
  cxxName bc = cxxName::_create(); \
  gov::cca::Component babelCmpt; \
  babelCmpt = ::babel_cast<gov::cca::Component> (bc); \
  if (babelCmpt._is_nil()) { \
    return static_cast< ccafeopq::Component* >(0); \
  } \
  BabelComponentWrapper * bcw = new BabelComponentWrapper(babelCmpt); \
  ccafeopq::Component *oc = bcw; \
  return oc; \
} 

// requires component_name_string defined elsewhere as const char*
#define ADDCLASS(name, create) \
  f->addStaticClassBabel(name, create, name); \
  component_name_string = "PRELOAD component " name


// for i in babel c++ names: CREATEDEF(cxxName, mangle)
#ifdef _CCAMPI
CREATEDEF(ccafe6::MPIComponent, ccafe6_MPIComponent)
#endif

void BabelStaticFactory::addClasses(ComponentRegistrar *f)
{
  const char* component_name_string = 0; // force the string into the binary searchably.
// for i in names, ADDCLASS
#ifdef _CCAMPI
   ADDCLASS("ccafe6.MPIComponent", create_ccafe6_MPIComponent);
#endif
}

#else //HAVE_BABEL
void BabelStaticFactory::addClasses(ComponentRegistrar *f) {
  (void)f;
}
#endif //HAVE_BABEL
