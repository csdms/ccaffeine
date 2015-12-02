#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#include "util/IO.h"
#include "dc/neo/ccafe-bind/NeoOpaqueComponentFactory.hh"
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"

int NeoOpaqueComponentFactory::goNextNum = 0;

// side effect: define cf ready to use, or return rval if not.
#define UNWRAP(func,rval) \
::neo::cca::Port *cp = getNeoPort(); \
neo::cca::ports::ComponentFactory * cf = 0; \
if (cp) { \
		cf = dynamic_cast<neo::cca::ports::ComponentFactory *>(cp); \
		if (!cf) { \
			IO_dn2("NeoOpaqueComponentFactory::%s neo port not a ComponentFactory.", func); \
			return rval; \
                } \
} else { \
	IO_dn2(":-( NeoOpaqueComponentFactory::%s no neo port pointer found.", func); \
	return rval; \
}  do {} while(0)


NeoOpaqueComponentFactory::~NeoOpaqueComponentFactory()
{
	ncf = 0;
	goNum = -goNum;
}
  
NeoOpaqueComponentFactory::NeoOpaqueComponentFactory( neo::cca::ports::ComponentFactory *cf) : NeoOpaquePort(cf)
{
	if (cf == 0) return; 
	goNextNum++;
	goNum = goNextNum;
	IO_dn2("NeoOpaqueComponentFactory created %d", goNum);
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
NeoOpaqueComponentFactory::getComponentClassAliases()
{
	std::vector< std::string> list;
	UNWRAP("getComponentClassAliases",list);
	list = cf->getComponentClassAliases();
	return list;
}

  /** Descriptions of classes this factory might make based
   * on parsing metadata files. A loadClass may be needed
   * before createComponentInstance is possible.
   */
std::vector< ccafeopq::ComponentClassDescription_shared > 
NeoOpaqueComponentFactory::getComponentClasses()
{
	std::vector< ccafeopq::ComponentClassDescription_shared > olist;
	std::vector< neo::cca::ports::ComponentClassDescription_shared > list;
	UNWRAP("getComponentClasses",olist);
	list = cf->getAvailableComponentClasses();
	// fixme: wrapperify neoccds to opqccds NeoOpaqueComponentFactory::getComponentClasses
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
NeoOpaqueComponentFactory::createComponentInstance(const std::string & className)
{
	ccafeopq::Component *oc = 0;
	neo::cca::Component *nc;
	UNWRAP("createComponentInstance",oc);
	nc = cf->createComponentInstance(className);
	if (nc == 0) return oc;
	oc = new NeoComponentWrapper(nc);
	return oc; // fixme createComponentInstance logic ok?
}
  /** properties is currently ignored. */
ccafeopq::Component * 
NeoOpaqueComponentFactory::createComponentInstance(const std::string & className, ccafeopq::TypeMap_shared & properties)
{
	ccafeopq::Component *oc = 0;
	neo::cca::Component *nc;
	UNWRAP("createComponentInstance",oc);
	::neo::cca::TypeMap_shared ntm = ccafe::TypeMap::neoWrap(properties);
	nc = cf->createComponentInstance(className,ntm);
	if (nc == 0) return oc;
	oc = new NeoComponentWrapper(nc);
	return oc; // fixme createComponentInstance logic ok?
}

/**
* This call will be made *after* setServices(0) has
* been called on the component wrapper obtained from createInstance.
*/
void 
NeoOpaqueComponentFactory::destroyComponentInstance(const std::string & componentClassName, ccafeopq::Component * component)
{
	UNWRAP("destroyComponentInstance",);
	NeoComponentWrapper * ncw = dynamic_cast< NeoComponentWrapper *>(component);
	if (ncw != 0) {
		::neo::cca::Component *nc = ncw->getWrapped();
		cf->destroyComponentInstance(componentClassName,nc);
		delete component; // kill the wrapper
	}
}

/** replace current path with new paths. each vector element is one
* directory name. Path is searched for .cca elements.
*/
void 
NeoOpaqueComponentFactory::setComponentPath(const std::vector< std::string > & paths)
{
	IO_dn1("NeoOpaqueComponentFactory::setComponentPath called unexpectedly");
	return;
}

  /** return the list of directories searched for .cca files. */
std::vector< std::string > 
NeoOpaqueComponentFactory::getComponentPath()
{
	std::vector< std::string > x;
	IO_dn1("NeoOpaqueComponentFactory::getComponentPath called unexpectedly");
	return x;
}

  /** parse a file for component descriptions and add them
   * to repository list.
   */
void 
NeoOpaqueComponentFactory::loadComponentDescription(const std::string & uri)
{
	IO_dn1("NeoOpaqueComponentFactory::loadComponentDescription called unexpectedly");
}
  /**
   * Generate an index (populate the component repository) based on 
   * current component path value.
   */
void 
NeoOpaqueComponentFactory::indexComponentPath( )
{
	IO_dn1("NeoOpaqueComponentFactory::indexComponentPath called unexpectedly");
}

  /**
   * Cause the named class to become instantiable by a subsequent
   * call to createComponentInstance(). This may require side effects
   * with dlopen.
   *   In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
   *                  global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
   */
void 
NeoOpaqueComponentFactory::loadClass( const std::string paletteClassAlias , bool global, bool lazy)
{
	IO_dn1("NeoOpaqueComponentFactory::loadPath called unexpectedly");
}

int
NeoOpaqueComponentFactory::loadPorts( const std::string & paletteClassAlias )
{
	IO_dn1("NeoOpaqueComponentFactory::loadPorts called unexpectedly");
	return 1;
}

NeoOpaqueComponentFactory test_NeoOpaqueComponentFactory(1); // bogon
