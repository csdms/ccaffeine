#ifndef NeoOpaqueComponentFactory_hh_seen
#define NeoOpaqueComponentFactory_hh_seen


/** This is the wrapping for exposure to the framework
 *  of the neo definition of componentfactory.
 */ 
class NeoOpaqueComponentFactory : public virtual NeoOpaquePort,
public virtual ccafeopq::ComponentFactory
{
private:
  neo::cca::ports::ComponentFactory *ncf;
  int goNum;
  static int goNextNum;

public:
  virtual ~NeoOpaqueComponentFactory();
  NeoOpaqueComponentFactory(int bogon) : ncf(0), goNum(0) { }
  /* the real constructor. */
  NeoOpaqueComponentFactory( neo::cca::ports::ComponentFactory *cf);


  /** Names of classes for which this factory can make instances.
   * These names are the palette alias names for presentation to
   * a user. The real names can be obtained by querying the
   * corresponding componentClassDescriptions.
   * The names returned here are those of classes that are
   * definitely in the runtime in the case of classic/opaque
   * components and those of classes that are babel components.
   */
  virtual std::vector< std::string> getComponentClassAliases();

  /** Descriptions of classes this factory might make based
   * on parsing metadata files. A loadClass may be needed
   * before createComponentInstance is possible.
   */
  virtual std::vector< ccafeopq::ComponentClassDescription_shared > getComponentClasses();

  /**
   * Make one uninitialized instance object on which something
   * must still setServices: either a driver or the framework.
   * This raw instance will eventually come back to this port
   * for disposal.
   * @param properties -- whatever suggestions the driver has
   * or the framework obtains by whatever method from the user.
   */
  virtual ccafeopq::Component * createComponentInstance(const std::string & className);
  /** properties is currently ignored. */
  virtual ccafeopq::Component * createComponentInstance(const std::string & className, ccafeopq::TypeMap_shared & properties);

  /**
   * This call will be made *after* setServices(0) has
   * been called on the component obtained from createInstance.
   */
  virtual void destroyComponentInstance(const std::string & componentClassName, ccafeopq::Component * component);

  /** replace current path with new paths. each vector element is one
   * directory name. Path is searched for .cca elements.
   */
  virtual void setComponentPath(const std::vector< std::string > & paths);

  /** return the list of directories searched for .cca files. */
  virtual std::vector< std::string > getComponentPath();

  /** parse a file for component descriptions and add them
   * to repository list.
   */
  virtual void loadComponentDescription(const std::string & uri);
  /**
   * Generate an index (populate the component repository) based on 
   * current component path value.
   */
  virtual void indexComponentPath( );

  /**
   * Cause the named class to become instantiable by a subsequent
   * call to createComponentInstance(). This may require side effects
   * with dlopen.
   *   In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
   *                  global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
   */
  virtual void loadClass( const std::string paletteClassAlias , bool global, bool lazy);

  virtual int loadPorts(const std::string & lib);

}; // end class NeoOpaqueComponentFactory
#endif //  NeoOpaqueComponentFactory_hh_seen
