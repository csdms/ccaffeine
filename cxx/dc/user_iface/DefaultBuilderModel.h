#ifndef DefaultBuilderModel_h_seen
#define DefaultBuilderModel_h_seen

/** This is implements the Model part of a Model-View-Controller design
    pattern.  This is the object that actually deals first hand with
    the connection framework itself.  It understands a concept of a pallet - a
    set of instantiatable classes maintained by the connection
    framework; a concept of an arena - a space where instantiated
    components are hooked together to create a program by the framework, 
    and a go() or
    method that fires the flow executive in the connection framework.
    It's mainly a legacy convenience for a lot of things that
    can be better done by cleaner methods now available.
    */
class DefaultBuilderModel : public virtual BuilderModel {

private:

  /** Create a unique instance name. don't free it. returns null from
   bogus input. */
  std::string createInstanceName(const std::string & className) ;

  /** Holds ComponentChangedListener's. */
  ::std::vector< ComponentChangedListener *> cmptChgLsnrs;


  /* CDELETE */ ConnectionFramework *fwk_data;

public:

  /** get the pointer */
  ConnectionFramework *getFramework();


  /** classNotFoundException 0 if ok, -1 if error in starting. 
   * sf will be used to initialize the factory if it is not null.
   * fComm will be ignored unless useComm is true, in which case it is
   * a fortran mpi comm representation (from comm_c2f())cast to an int64_t.
   */
  DefaultBuilderModel(int & classNotFoundException, StaticFactory *sf, int64_t fComm, bool useComm); 
  virtual ~DefaultBuilderModel() ;

  /** run the default setup */
  virtual void initScript();

  /** Signal a change in the Component's status. */
  virtual void componentChanged(ComponentChangedEvent* evt) ;
  
  /** Add a listener for a change in the status of a component. */
  virtual void addComponentChangedListener(ComponentChangedListener* l) ;


  /** Instantiate a component that presently exists on the pallet and
place it in the arena with the given instance name.  
      @returns A string that is the instantiated components unique
      instance name. returns null if an error occurs. */
  std::string pullDownFromPallet(const std::string & className, const std::string & instanceName);

  /** Instantiate a component that presently exists on the pallet and
      place it in the arena with the given instance name.  
      The given properties (cprops) will be available during setServices
      if the component queries for them.
      @returns A string that is the instantiated components unique
      instance name. returns null if an error occurs. */
  std::string pullDownFromPallet(const ::std::string & className,
		  const ::std::string & instanceName,
		  ::ccafeopq::TypeMap_shared cprops);

  /** Instantiate a component that presently exists on the pallet and
      place it in the arena.  
      @returns A string that is the instantiated components unique
      instance name. returns null if an error occurs. */
  std::string pullDownFromPallet(const std::string & className);


  /** diconnect two components. same return as connect.  */
  int disconnect(const char *fromInstance, const char *providesInstance, 
                 const char *toInstance, const char *usesInstance);


  /** Connect the instance of an already "pulled down" (instantiated)
      component, already residing in the arena, to another component
      in the arena.  Note that the order here honors the port flow.
      Port's flow from "fromInstance" to toInstance in the argument
      list.  Data flow moves in the opposite direction of port flow.
      returns 0 if ok, -1 if vetoed, -2 if bogus input. */
  int connect(const char *fromInstance, const char *providesInstance, 
              const char *toInstance, const char *usesInstance);


  /** The arena is where instantiated components live and can be
      subsequently connected together. The component information is
      stored in a ComponentInfo_shared map.
      The key to each is the
      String-valued instance name of the instantiated component.

   */
  ::std::map< ::std::string, ComponentInfo_shared > getArena() ;


  /** The pallet is an array of String's that are the class names
      (types) of components that can be instantiated by the connection
      framework. 
      Do not delete (or cache) the pointer returned. */
  ::std::vector< std::string > getPallet() ;

    /** return list of all names for instances. */
  ::std::vector< std::string > getInstanceNames() ;

  /** use this one instead. */
  int goOne(const char * instanceName, const char * portName);


  void setDebug(bool tf) ;

  /** Remove an already instantiated component from the Arena. */
  void removeInstantiatedComponent(const std::string & iname);

  /** Remove an all instantiated components from the Arena. */
  void removeAllInstantiatedComponents();

  /** get configuration string for single field from parameter port on instance */
  /* CFREE */virtual char * getConfiguration(const char * instanceName, const char * portName, const char *fieldName);
  /** get configuration string for all fields from parameter port on instance */
  /*CFREE */virtual char * getConfiguration(const char * instanceName, const char * portName);

  /** set configuration field to parameter port on instance */
  virtual char * setConfiguration(const char * instanceName, const char * portName, const char *fieldName, const char * data);

  /** Get a string list of all property keys and value (an even length list).
      Destroy the list when done with it, but leave the strings alone.
      This is for the old KeyValuePort stuff */
  virtual std::vector< std::string > getComponentProperties( ::std::string & instanceName);
  /** Get the value of a property, or 0 if no such property exists.
   * This is for the old KeyValuePort stuff
   * */
  virtual const std::string getComponentProperty(const char * instanceName, const char * key);

  virtual std::vector< std::string > getComponentProperties(const std::string & instanceName);


  /** Copy the value into the properties of instance with the given key.
      Will replace previously defined values.
      This is for the old KeyValuePort stuff.
   */
  virtual void setComponentProperty(const char * instanceName, const char * key, const char * value); 

  virtual ::ccafeopq::TypeMap_shared getPortProperties(
		  const ::std::string & instanceName, 
		  const std::string & portName);

  virtual int setPortProperty(
		  const ::std::string & instanceName, 
		  const std::string & portName, const std::string & key,
		  const std::string & valueType, const std::string & value);


  /** =============  repository activities =============  */

  /** Set current module path from an argv. Input will only be read
      until argc or a null element is reached. Normal return is 0. */
  virtual int setRepositoryPath(char **argv, int argc);
  virtual int setRepositoryPath( const std::vector< std::string > & p);

  /** Get current componenent path as an argv. Path returned
      is null-terminated and has argc elements. Not yours
      to mess with the content. */
  virtual std::vector< std::string > getRepositoryPath();
  
  /** Return the list of unloaded classes and where
      they come from. argc is an even number, as you
      get the library location following each class entry.
      Class names will be unique, whether or not component
      writers worried about that.
. */
  virtual std::vector< std::string > getRepositoryClasses();
  
  /** Move a class from the repository to the
    pallet. Probably involves a dynamic load.
    returns 0 if transferred successfully.
  */
  virtual int loadRepositoryClass(const char *className, bool global, bool lazy);

  /** just load a library globally and forget about it. */
  virtual int loadPorts(const std::string & libPathName);
};
#endif // DefaultBuilderModel_h_seen
