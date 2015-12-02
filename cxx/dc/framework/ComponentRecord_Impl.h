#ifndef __COMPONENTRECORD_IMPLH__
#define __COMPONENTRECORD_IMPLH__

namespace ccafe {

/**
 * Class metadata record.
 */
class ComponentRecord_Impl : public virtual ccafeopq::ComponentClassDescription_Interface {
private:
  ccafeopq::ComponentClassDescription_shared ccd;
  void * (*create)();
  int inFactory;   // if 1, className will be found in ccafe_factory_list.
  void setInFactory(int i);
  bool foundInPath;

public:

  ComponentRecord_Impl();
  virtual ~ComponentRecord_Impl() ;

  // char * libraryClassName; // className found with library introspection.
  virtual ::std::string getComponentClassName() throw (ccafeopq::Exception );
  

  // char * componentType;    // classic, babel, etc.
  virtual ::std::string getCCASpecBinding() throw (ccafeopq::Exception ) ;

  // char * indexName;        // where we found out about this class.
  virtual ::std::string getIndexFile() throw (ccafeopq::Exception ) ;
  
  //char * className;        // className defined for user, possibly disambiguated
                           // or taken from .cca file for library.
  virtual ::std::string getDeploymentClassAlias() throw (ccafeopq::Exception ) ;

  // char * cFuncName;        // constructor function name for className
  virtual ::std::string getConstructorName() throw (ccafeopq::Exception );

  // dynamic
  virtual ::std::string getLibraryLoading() throw (ccafeopq::Exception);

  // char * libraryPath;      // .so file name where class+cfunc is found.
  virtual ::std::string getLibraryName() throw (ccafeopq::Exception );

  char * buildLocation;    // component data, if available.
  virtual ::std::string getLibraryLocation() throw (ccafeopq::Exception );

  // dummy
  virtual ::std::string getExecScript() throw (ccafeopq::Exception );

  // dummy
  virtual void getDOMTree() throw (ccafeopq::Exception );

  bool getInFactory();
  
  void setCCD( ccafeopq::ComponentClassDescription_shared ccd);

  /** return the constructor, if set, for classic, opaque components. */
  // ConstructorFunc  getConstructorFunc();
  void *getConstructorFunc();

  /** store the constructor
  * classic::gov::cca::Component * (*create)();
  * or
  * neo::cca::Component * (*create)();
  */
  void setConstructorFunc( void * func);

  /** return whether the description was loaded by a glob
   * (FoundInPath) or was derived from a specifically named uri.
   */
  bool getFoundInPath();

  void setFoundInPath(bool tf);

  std::string toString();

}; // end class ComponentRecord_Impl

} // end namespace ccafe

#endif // __COMPONENTRECORD_IMPLH__
