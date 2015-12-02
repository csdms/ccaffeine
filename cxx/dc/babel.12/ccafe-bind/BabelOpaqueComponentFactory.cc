#include "gov_cca.hxx"
#include "gov_cca_ports.hxx"
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/KernelPort.h"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
#include "dc/babel.12/babel-cca/server/ccaffeine_TypeMap_Impl.hxx"
#include "util/IO.h"
#include "dc/babel.12/ccafe-bind/BabelOpaqueComponentFactory.hh"

int BabelOpaqueComponentFactory::goNextNum = 0;

// side effect: define cf ready to use, or return rval if not. // CAST
#define UNWRAP(func,rval) \
::gov::cca::Port cp = getBabelPort(); \
ccaffeine::ports::ComponentFactory  cf; \
if (cp._not_nil()) { \
		cf = ::babel_cast<ccaffeine::ports::ComponentFactory> (cp); \
		if (cf._is_nil()) { \
			IO_dn2("BabelOpaqueComponentFactory::%s babel port not a ComponentFactory.", func); \
			return rval; \
                } \
} else { \
	IO_dn2(":-( BabelOpaqueComponentFactory::%s no babel found.", func); \
	return rval; \
}  do {} while(0)


BabelOpaqueComponentFactory::~BabelOpaqueComponentFactory()
{
	ncf = 0;
	goNum = -goNum;
}
  
BabelOpaqueComponentFactory::BabelOpaqueComponentFactory( ccaffeine::ports::ComponentFactory cf) : BabelOpaquePort(cf)
{
	if (cf._is_nil()) return; 
	goNextNum++;
	goNum = goNextNum;
	IO_dn2("BabelOpaqueComponentFactory created %d", goNum);
}


  /** Names of classes for which this factory can make instances.
   * These names are the palette alias names for presentation to
   * a user. The real names can be obtained by querying the
   * corresponding componentClassDescriptions.
   * The names returned here are those of classes that are
   * definitely in the runtime in the case of classic/opaque
   * components and those of classes that are babel components.
   */
std::vector< std::string> 
BabelOpaqueComponentFactory::getComponentClassAliases()
{
	std::vector< std::string> list;
	UNWRAP("getComponentClassAliases",list);
	sidl::array<gov::cca::ComponentClassDescription> clist
		= cf.getAvailableComponentClasses();
	int upper = clist.upper(0);
	int lower = clist.lower(0);
	for (int i = lower; i <= upper; i++) {
		gov::cca::ComponentClassDescription ccd = clist.get(i);
		list.push_back(ccd.getComponentClassName());
	}
	return list;
}

  /** Descriptions of classes this factory might make based
   * on parsing metadata files. A loadClass may be needed
   * before createComponentInstance is possible.
   */
std::vector< ccafeopq::ComponentClassDescription_shared > 
BabelOpaqueComponentFactory::getComponentClasses()
{
	std::vector< ccafeopq::ComponentClassDescription_shared > olist;
	sidl::array< gov::cca::ComponentClassDescription > list;
	UNWRAP("getComponentClasses",olist);
	list = cf.getAvailableComponentClasses();
	// fixme: wrapperify babelccds to opqccds BabelOpaqueComponentFactory::getComponentClasses
	return olist;
}

  /**
   * Make one uninitialized instance object on which something
   * must still setServices: either a driver or the framework.
   * This raw instance will eventually come back to this port
   * for disposal.
   * @param properties -- whatever suggestions the driver has
   * or the framework obtains by whatever method from the user.
   */
ccafeopq::Component * 
BabelOpaqueComponentFactory::createComponentInstance(const std::string & className)
{
	ccafeopq::Component *oc = 0;
	gov::cca::Component nc;
	UNWRAP("createComponentInstance",oc);
	nc = cf.createComponentInstance(className);
	if (nc._is_nil()) return oc;
	oc = new BabelComponentWrapper(nc);
	return oc; // fixme createComponentInstance logic ok?
}
  /** properties is currently ignored. */
ccafeopq::Component * 
BabelOpaqueComponentFactory::createComponentInstance(const std::string & className, ccafeopq::TypeMap_shared & properties)
{
#if 1
	return createComponentInstance(className);
#else
	ccafeopq::Component *oc = 0;
	gov::cca::Component nc;
	UNWRAP("createComponentInstance",oc);
	gov::cca::TypeMap btm;
	btm = ccaffeine::TypeMap_impl::babelWrap(properties);
	nc = cf.createComponentInstance(className,btm);
	if (nc == 0) return oc;
	oc = new BabelComponentWrapper(nc);
	return oc; // fixme createComponentInstance logic ok?
#endif
}

/**
* This call will be made *after* setServices(0) has
* been called on the component wrapper obtained from createInstance.
*/
void 
BabelOpaqueComponentFactory::destroyComponentInstance(const std::string & componentClassName, ccafeopq::Component * component)
{
	UNWRAP("destroyComponentInstance",);
	BabelComponentWrapper * ncw = dynamic_cast< BabelComponentWrapper *>(component);
	if (ncw != 0) {
		::gov::cca::Component nc = ncw->getWrapped();
		cf.destroyComponentInstance(componentClassName,nc);
		delete component; // kill the wrapper
	}
}

/** replace current path with new paths. each vector element is one
* directory name. Path is searched for .cca elements.
*/
void 
BabelOpaqueComponentFactory::setComponentPath(const std::vector< std::string > & paths)
{
	IO_dn1("BabelOpaqueComponentFactory::setComponentPath called unexpectedly");
	return;
}

  /** return the list of directories searched for .cca files. */
std::vector< std::string > 
BabelOpaqueComponentFactory::getComponentPath()
{
	std::vector< std::string > x;
	IO_dn1("BabelOpaqueComponentFactory::getComponentPath called unexpectedly");
	return x;
}

  /** parse a file for component descriptions and add them
   * to repository list.
   */
void 
BabelOpaqueComponentFactory::loadComponentDescription(const std::string & uri)
{
	IO_dn1("BabelOpaqueComponentFactory::loadComponentDescription called unexpectedly");
}
  /**
   * Generate an index (populate the component repository) based on 
   * current component path value.
   */
void 
BabelOpaqueComponentFactory::indexComponentPath( )
{
	IO_dn1("BabelOpaqueComponentFactory::indexComponentPath called unexpectedly");
}

  /**
   * Cause the named class to become instantiable by a subsequent
   * call to createComponentInstance(). This may require side effects
   * with dlopen.
   *   In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
   *                  global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
   */
void 
BabelOpaqueComponentFactory::loadClass( const std::string paletteClassAlias , bool global, bool lazy)
{
	IO_dn1("BabelOpaqueComponentFactory::loadPath called unexpectedly");
}

int
BabelOpaqueComponentFactory::loadPorts( const std::string & paletteClassAlias )
{
	IO_dn1("BabelOpaqueComponentFactory::loadPorts called unexpectedly");
	return 1;
}

BabelOpaqueComponentFactory test_BabelOpaqueComponentFactory(1); // bogon
