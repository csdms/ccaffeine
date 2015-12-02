#ifndef __BABELFACTORYSERVICE_HH__
#define __BABELFACTORYSERVICE_HH__


/** a class not actually used anywhere presently. */
class BabelFactoryService : 
public virtual ccafeopq::FactoryService,
public virtual KernelPort,
public virtual ccafeopq::Component {
private:

  std::string path;
  std::map<std::string,std::string> cmptInfo;

  bool bypassPaths;
  std::vector< std::string > compList;

public:
  virtual ~BabelFactoryService(){}
  BabelFactoryService();

  // ccafeopq::Component implementation

  virtual void setServices(ccafeopq::Services * svc) throw (::ccafeopq::Exception);


  // End OpqueComponent implementation

  // FactoryServicePort implementation

  virtual std::vector< std::string > getComponentClassNames();

  /** Memory Lifecycle
   * Returned description is shared_ptr.
   */
  virtual std::vector< ::ccafeopq::ComponentClassDescription_shared > getComponentClasses();

  virtual ::ccafeopq::Component *createComponentInstance (const std::string & className, ::ccafeopq::TypeMap_shared & properties);

  /** 
   * All created components will be returned to the factory for
   * destruction. exception if class unknown.
   */
  virtual ::ccafeopq::Component * 
    createComponentInstance(const  std::string & className) 
    throw (ccafeopq::Exception);

  virtual void 
    destroyComponentInstance(const std::string & componentClassName, 
			     ::ccafeopq::Component * component) 
    throw (ccafeopq::Exception );


  // End FactoryServicePort implementation
};

#endif // __BABELFACTORYSERVICE_HH__
