#ifndef __CONNECTIONFRAMEWORK_H__
#define __CONNECTIONFRAMEWORK_H__

#include "dc/framework/XCmptFactory.hh"
#include <string>

#include "dc/framework/CmpBox.h"

namespace ccafe {
class Frame;
} ENDSEMI

class OpqGUIService;
class OpqServiceRegistry;
class OpqBuilderService;
class DefaultJPrintfPort;
class ClassicOpaquePort;
namespace ccafeopq {
	namespace event {
		class ContextEventManager;
	} ENDSEMI
} ENDSEMI

typedef	 boost::shared_ptr< ccafeopq::ComponentFactory > ComponentFactory_shared;
/**
Our simple-minded implementation of a container for components
that lets one make and manage connections. 
Memory model rules:

ConnectionFramework owns all the cmpboxes.

CmpBox owns the gizzard in it until the framework
wants it back, and also the Component pointer.

The gizzard owns the Port-related data containers.

The gizzard is the source for all shared componentID and TypeMap.

The userportdata connection list owns the connectionids,
and the connectionframework/builderservice list is full of elements
originated in the gizzard and stored in the connection list.
Userportdata creates all connectionid.

Port pointers are kept in ProviderPortData as the ports are
originated by a component addProvidesPort.
Port pointers are kept only in ConnectionID data when they are from
the framework instead of another component, and they are cached
in the ConnectionID when connection is made from a ProviderPortData.
This is exactly equivalent to the old gizzard::pPort/uPort vector
usage.

PortInfo is no longer used in the kernel for anything -- it's just
a wrapper we have some legacy support for.

*/
class ConnectionFramework : public virtual ComponentChangedListener {

private:

  /** write something about et for failed getport named. */
  void nullPortMessage(std::string name, ccafeopq::ExceptionType et);

  /**
     This gizzard is the container the framework
     uses as a home so that the normal connections
     processes apply to services the frame provides.
     It doesn't go with a single component, though
     it appears to. Think of it as the thick wall
     of the framework in the component diagrams.
   */
  Gizzard *wall;

	 /** the base component factory with components
	  * ccaffeine happens to supply, which may be none,
	  * and support for dynamic loading (if built that way).
	  */
  ComponentFactory_shared ocf;

  std::vector< std::string > pallet;

  /** string lookup of components. across all bindings,
   * the keys in this table must be unique (component names).
   */
  ::std::map< ::std::string, ::ccafe::CmpBox_shared > instances;

  /** fetch the named cmpbox, if it exists. _shared item returned
   * may be the null item.
   * This function avoids the map side-effect of creating null
   * _shared items which direct [] lookup has.
   */
  ::ccafe::CmpBox_shared getInstance( const ::std::string & name);

  /** Contains ComponentChangedListener's. */
  std::vector< ComponentChangedListener * > cmptChgLsnrs;

  OpqServiceRegistry *osr;
  OpqBuilderService *obs;
  OpqGUIService *ogs;
  DefaultJPrintfPort *jpfp;
#ifdef HAVE_CLASSIC
  ClassicOpaquePort *cbs;
#endif // HAVE_CLASSIC
  ccafeopq::event::ContextEventManager *cem;

  /** A list of external component factories. */
  std::vector< XCmptFactory_shared > xCmptFactories;


#ifdef CCAFE_THREADS
  /** A map of threads and their states for go()'s with their own
      thread. */
  std::map< std::string, GoThread_shared > goThreads;
#endif

  bool debug;

  // This informs the framework that we are in the intantiate()
  // routine.  This prevents us from sending out
  // ComponentChangedEvent's before the component actually exists.
  bool instantiatingComponent; 

  std::map< std::string, void * > frameItems;

  /** Lookup the gizzard of the named component instance. */
  Gizzard *getGizzard(const char *instanceName);
  Gizzard *getGizzard(const ::std::string & instanceName);

  void initInternals(int64_t fComm, bool useComm);
  std::string deriveConfigurationString(const ::std::string & prefix, ::ccafeopq::TypeMap_shared tm);
  std::string deriveConfigurationString(const ::std::string & prefix, ::ccafeopq::TypeMap_shared tm, const ::std::string & key);
  int insertConfigurationString( ::ccafeopq::TypeMap_shared pptm, const std::string & fieldName, const std::string & configuration);

  friend class OpqBuilderService;
  friend class ccafe::Frame;

  int64_t fortranMPIComm;
  bool hasComm;

 public:

  /** create a framework */ 
  ConnectionFramework(int64_t fComm, bool useComm) ;
  /** create a framework and tell nicely if it fails. */ 
  ConnectionFramework(int64_t fComm, bool useComm, int & status) ;
  virtual ~ConnectionFramework();
  int setDebug(bool tf) { debug = tf; return -1; }
  /** finds the hidden ComponentFactory instance within the frame
   * and exposes its ComponentRegistrar interface to the sf given.
   * sf will never be cached by the frame.
   */
  void initStaticFactory(StaticFactory *sf);

  /** return the ur-factory that comes with the framework. */
  ComponentFactory_shared getBaseComponentFactory();

  std::vector< ::ccafeopq::ComponentID_shared > 
    getComponentsThatUse(const std::string& portType);

  std::vector< ::ccafeopq::ComponentID_shared > 
    getComponentsThatProvide(const std::string& portType);

  /** add an arbitrary piece of state scoped with the frame. */
  void putFrameItem(std::string s, void *item);
  void *getFrameItem(std::string s);

  /** Lists the pallet of components that are available to be instantiated. */
   std::vector< std::string > getComponentClasses() ;

  /** Takes a component from the pallet (i.e. list of available
      components) and instantiates it, placing it in the Arena, and
      making it available for connections to other components.
   */
   ComponentInfo_shared instantiate( char* className,  char* instanceName) ;
   ComponentInfo_shared instantiate(const ::std::string & className, const ::std::string & instanceName, ::ccafeopq::TypeMap_shared tm) ;

   /** create a component with no Component interface to keep track of. */
   ComponentInfo_shared addExternalComponent(const ::std::string & className, const ::std::string & instanceName, ::ccafeopq::TypeMap_shared tm);

   /** remove a component added with addExternalComponent. */
   void removeExternalComponent(const ::std::string & instanceName);

  /** Remove an already instantiated component from the Arena. */
  void removeInstantiatedComponent(const std::string & instanceName);

  /** ============== component wiring  =========*/
  /** Make a connection from the providing component <\em fromName>
      with the provides port <\em fromPortName> to the using component
      <\em toName> with the uses port <\em toPortName>. 
   */
  int  connect(const char* fromName, const char* fromPortName, 
	 const	char* toName, const char* toPortName) ;


  /** Make a connection from the providing component <\em fromName>
      with the provides port <\em fromPortName> to the using component
      <\em toName> with the uses port <\em toPortName>. */
  int  directConnect(const char* fromName, const char* fromPortName, 
		      const char* toName, const   char* toPortName) ;

  /** Break a connection from the providing component <\em fromName>
      with the provides port <\em fromPortName> to the using component
      <\em toName> with the uses port <\em toPortName>. 
      Return 0 if ok, -1 if there's a problem, -2 if there's just bogus
      input.
   */
  int disconnect(const char* fromName, const char* fromPortName, 
         	  const char* toName,   const char* toPortName) ;
  int disconnect( const ::std::string & fromName,
                  const ::std::string & fromPortName,
                  const ::std::string & toName,
                  const ::std::string & toPortName);
  int disconnect(const ::ccafeopq::ComponentID_shared  fromC,
                 const ::std::string & fromPortName,
                 const ::ccafeopq::ComponentID_shared  toC,
                 const ::std::string & toPortName);

  /** Eliminate all connections to and from this component.*/
  int disconnectAll(const char* componentInstanceName);

  /** Break a connection from the providing component <\em fromName>
      with the provides port <\em fromPortName> to the using component
      <\em toName> with the uses port <\em toPortName>. 
  */
  int  directDisconnect(const char* fromName, const char* fromPortName, 
		        const char* toName,   const char* toPortName) ;

  /** Return the list of key/value pairs.
      DEPRECATED. see getComponentPropertyTypeMap.
   */
  std::vector< std::string>getComponentProperties(const std::string & instanceName);

  /** Return the value corresponding to key, or NULL if key unknown.  
   * DEPRECATED. see getComponentPropertyTypeMap.*/
  const std::string getComponentProperty(const std::string & instanceName,
                                         const std::string & key);

  /** Set the value corresponding to key. Returns nonzero if an error occurs.
      key/value given are copied not kept. 
      DEPRECATED. see setComponentPropertyTypeMap.
   */
  void setComponentProperty(const std::string & instanceName, const std::string & key, const std::string & value);


  /** tries to go a specific instance and portname. returns
    0- ok, -1 whine but component can continue, -2 component/code should quit. */
  int goOne(const char * instanceName, const char * portInstanceName);

  /** =================== component configuration  =========*/
  /** Get the parameter data from a component, if it has any,
      or the empty string if it doesn't or an error occurs. */
  char * getConfiguration(const char * instanceName, const char * portInstanceName) ;

  /** Get the parameter data from a component, if it has any,
      or the empty string if it doesn't or an error occurs. */
  char * getConfiguration(const char * instanceName, const char * portInstanceName, const char *fieldName) ;

  /** Set the parameter data from a component, if it has any.
      Return the parameters if it takes any, or the empty
      string if it doesn't or an error occurs. */
  char * setConfiguration(const char * instanceName, const char * portInstanceName, const char *fieldName, const char * configuration) ;
    
  /** =================== events =======================*/
  /** Implements ComponentChangedListener.  Signal a change in the
      Component's status. */
  virtual void componentChanged(ComponentChangedEvent* evt) ;
  
  /** Add a factory for creating components. */
  void addXCmptFactory(XCmptFactory_shared xs);

  /** Add a listener for a change in the status of a component. */
  virtual void addComponentChangedListener(ComponentChangedListener* l);


  /** fetch the names of current component instances. */
  ::std::vector< ::std::string > instanceNames();

  ::std::map< ::std::string, ::ccafe::CmpBox_shared > getInstances();

  /** dig up a connid based on strings.
   * @param uc - using component name
   * @param up - uses port name
   * @param pc - providing component name
   * @param pp - provides port name
   */
  ::ccafeopq::ConnectionID_shared getConnectionID(const char* uc, const char* up, const char* pc, const char* pp);

  /** see cca.sidl */
  ::ccafeopq::TypeMap_shared getConnectionProperties( ::ccafeopq::ConnectionID_shared & conn);

  void setConnectionProperties( ::ccafeopq::ConnectionID_shared & connID,  ::ccafeopq::TypeMap_shared & map) throw ( ::ccafeopq::Exception );

  /** see cca.sidl */
  ::std::vector< ::ccafeopq::ConnectionID_shared > getConnectionIDs( ::std::vector< ::ccafeopq::ComponentID_shared> & clist);

  ::std::vector < ::ccafeopq::ConnectionID_shared > getConnectionIDs(  const ::std::string & userName, const ::std::string & usingPortName,  const ::std::string & providerName, const ::std::string & providingPortName) throw (::ccafeopq::Exception );


   /** copy data from the map, or throw if illformed input. */
  void setPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception );

  /** copy data in for a specific key, type, value. if this requires redefining the key type,
     returns a nonzero result and does not do the modification. */
  int setPortProperty(const ::std::string & instanceName, const std::string & portName,
                        const std::string & key, const std::string & valueType, const std::string & value);

  /** fetch up the typemap, or throw if ill formed input. */
  ::ccafeopq::TypeMap_shared getPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname) throw ( ::ccafeopq::Exception );

  /** converts all exceptions to an int, and does the lookup-from-name. */
  ::ccafeopq::TypeMap_shared getPortProperties( const ::std::string & cName, const ::std::string & portname) throw ();
  
  ::ccafeopq::TypeMap_shared getComponentPropertyTypeMap(const ::std::string & instanceName);
  bool setComponentPropertyTypeMap( const ::std::string & instanceName, ::ccafeopq::TypeMap_shared & tm);


  /** =================== repository use ==================*/
  /** Set current module path from an argv. Input will only be read
      until argc or a null element is reached. Normal return is 0. */
  virtual int setRepositoryPath(char **argv, int argc);
  virtual int setRepositoryPath(const std::vector< std::string > & p);

  /** Get current componenent path as a vector.
      */
  virtual std::vector< std::string > getRepositoryPath();
  
  /** Return the list of unloaded classes and where
      they come from. argc is an even number, as you
      get the library location following each class entry.
      Class names will be unique, whether or not component
      writers worried about that.
  */
  virtual std::vector< std::string > getRepositoryClasses();
  
  /** Move a class from the repository to the
    pallet. Probably involves a dynamic load.
    returns 0 if transferred successfully.
  */
  virtual int loadRepositoryClass(const char *className, bool global, bool lazy);

  /** recompute the pallet of instantiable components */
  virtual void refreshPallet();

  /** dlopen a port library globally and forget it. */
  virtual int loadPorts(const std::string & libPathName);

};

#endif // __CONNECTIONFRAMEWORK_H__
