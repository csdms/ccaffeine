#ifndef  BuilderModel_h_seen
#define  BuilderModel_h_seen

#include <vector>
#include <string>


/** This is the Model part of a Model-View-Controller design pattern.
    This is the object that actually deals first hand with the
    connection framework itself.  It has a concept of a pallet - a set
    of instantiatable classes maintained by the connection framework;
    a concept of an arena - a space where instantiated components are
    hooked together to create a program, and a go() or method that
    fires the flow executive in the connection framework.  */
class BuilderModel : public virtual ComponentChangedListener { 

public:

  virtual ~BuilderModel(){}

  /** do things that set up the default contents of the frame. */
  virtual void initScript() = 0;

  /** Add a listener for a change in the status of a component. */
  virtual void addComponentChangedListener(ComponentChangedListener* l) = 0;

  /** Instantiate a component that presently exists on the pallet and
place it in the arena with the given instance name.  

      @returns A string that is the instantiated components unique
      instance name. Rturns null if class not found. */

  virtual std::string pullDownFromPallet(const ::std::string & className, const ::std::string & instanceName) =0;

  /** Instantiate a component that presently exists on the pallet and
place it in the arena.  

      @returns A string that is the instantiated components unique
      instance name. returns null if class not found. */ 
  virtual std::string pullDownFromPallet( const ::std::string & className)=0;


  /** Disconnect
      component, already residing in the arena, from another component
      in the arena.  Note that the order here honors the port flow.
      Port's flow from "fromInstance" to toInstance in the argument
      list.  Data flow moves in the opposite direction of port flow.
      Returns 0 if ok, -1 if connection vetoed -2 if input bogus. */
  virtual int disconnect(const char *fromInstance, const char *providesInstance, 
		      const char *toInstance, const char *usesInstance)=0;


  /** Connect the instance of an already "pulled down" (instantiated)
      component, already residing in the arena, to another component
      in the arena.  Note that the order here honors the port flow.
      Port's flow from "fromInstance" to toInstance in the argument
      list.  Data flow moves in the opposite direction of port flow.
      Returns 0 if ok, -1 if connection vetoed -2 if input bogus. */
  virtual int connect(const char *fromInstance, const char *providesInstance, 
		      const char *toInstance, const char *usesInstance)=0;


  /** The arena is where instantiated components live and can be
      subsequently connected together. 
      key is String-valued instance name of the instantiated component.
  */
    virtual ::std::map< ::std::string, ComponentInfo_shared > getArena()=0;


  /** The pallet is an array of String's that are the class names
      (types) of components that can be instantiated by the connection
      framework. On return, pallet_length holds the length of result. */
    virtual std::vector< std::string > getPallet()=0;

    /** return list of all names for instances. */
    virtual std::vector< std::string > getInstanceNames()=0;

  virtual std::vector< std::string >getComponentProperties( ::std::string & instanceName)=0;
  
  virtual const std::string getComponentProperty(const char * instanceName, const char * key)=0;
  virtual void setComponentProperty(const char * instanceName, const char * key, const char * value) =0;

  virtual int loadPorts(const std::string & libPathName) = 0;
};

#endif //BuilderModel_h_seen
