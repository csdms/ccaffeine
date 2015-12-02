#ifndef __BUILDERSERVICE_H__
#define __BUILDERSERVICE_H__
namespace gov {
  namespace cca {

    /** This interface describes an all-string convenience
    builder within a CCA framework or context. Its functions all
    act on the peer components in the same framework.
    All its functions are more directly accessible by
    using the individual interfaces. It might be reasonable
    to move this interface into the public layer of a
    reference implementation rather than make it a standard port,
    but that then leaves all the gui's reinventing this layer.

    An XMLBuilderService would be highly appropriate as well,
    which would simplify greatly some of the StringList usage
    in this interface. Requiring an xml parsing engine at the
    application level, however, is liable to turn off some users
    so we will keep this interface.
 */
    
    class BuilderService : public virtual Port {

    public:

      ///////////////////////////////////////////////////////////////
      //// Composite all factory services.

      /** Collect the currently obtainable class names from
	  factories in the framework and the instantiated
	  components.
	  @param cl A list, to which the class names found
	  will be appended.
	  @return 0 if all is well, 1 if no factories were found,
	  -1 if something is unwell.
      */
      //# sidlpragma flow inout
      virtual CDELETE StringList* getComponentClasses() = 0;

      /** Cause a new component instance to appear
	  in the environment the BuilderService inhabits.
	  @param className Input: the name of a class available from
	  some factory in the framework of the BuilderService.
	  @param requestedInstanceName Input: the instance name desired
	  for the new object in the framework of the BuilderService.
	  If given name is the empty string, the BuilderService will
	  make one up.
	  @return ComponentID for the intantiated.

	  Throws CCAException if the instance name is already taken or
	  if the className cannot be found or if instantiation
	  otherwise fails.  
	  
      */
      virtual CDELETE ComponentID* createInstance(string className, 
				  string requestedInstanceName)
	throw (CCAException) = 0;

      /** Return the ComponentID for the given instance name. */
      virtual CDELETE ComponentID* getComponentID(string componentInstanceName) = 0;

      /** Cause an existing instance to disappear from the framework, which
	  may involve hefty connection activities.
	  @param id The target to be removed from the framework.

	  note that this does not destroy the ComponentID argument,
	  that must be done with a separate delete.
      */

      virtual void destroyInstance(ComponentID* id) throw (CCAException) = 0;


      ///////////////////////////////////////////////////////////////
      //// FrameworkInfo and PortInfoService strings
  
      /** Get framework name strings.
	  @param nl A list, to which will be appended the following strings:
	  <pre>
	  frameworkClassName, frameworkLocalName, 
	  frameworkGlobalName, frameworkToString
	  </pre>
	  from the framework in which the BuilderService lives.
	  @return 0 if ok, -1 if bogosity occurs.
      */
      //# sidlpragma flow inout
      virtual StringList* getFrameworkNames() = 0;
      
      /** Collect the current component instance names from framework.
	  @param il A list, to which the instance local names found
	  will be appended.
	  @return 0 if all is well, 1 if no components were found, and
	  -1 if something is unwell.
      */
      //# sidlpragma flow inout
      virtual ComponentIDList* getComponentIDs() = 0;

      /** Collect port names and types provided on a component.
	  @param componentName One of the strings obtained with 
	  getComponentInstanceNames.
	  @param pList a list to which will be appended N
	  pairs of strings: portInstanceName, portClass,...
	  @return -1 if error occured, N >=0 the number of
	  ports currently provided by the component.
      */
      //# sidlpragma flow in inout
      virtual PortInfoList* getProvidesPortStrings(ComponentID* cid) = 0;

      /** Collect uses port names and types registered by a component.
	  @param cid ComponentID returned from getComponentInstances.
	  @return uList a list to which will be appended N
	  pairs of strings: portInstanceName, portClass,...
      */
      //# sidlpragma flow in inout
      virtual PortInfoList* getUsesPortStrings(ComponentID* cid) = 0;

      /** Get the current details of all the connections in the framework.
	  The string list is appended with a set of 6-tuples:
	  {connectionName,
	  userName, usingPortName, providerName, providingPortName,
	  isInUse ("true" or "false")
	  }
	  @param cdl The list to which 6*N strings are appended.
	  @return N >= 0, ok and N connection tuples were appended. If
	  N < 0, some error occured.
      */
      //# sidlpragma flow inout
      virtual CDELETE ConnectionInfoList* getConnections() = 0;


      ///////////////////////////////////////////////////////////////
      //// Composite ConnectionService

      /** Connect the instance of an already created (instantiated)
	  component residing in the framework of the BuilderService.
	  @param user The caller component id.
	  @param usingPortName The registered port on the caller.
	  @param provider The callee component id.
	  @param providingPortName The name of the port the callee provides.
	  @param connectionName The name to be assigned to the connection.
      */
      virtual void connect(ComponentID* user, PortInfo* usingPortName, 
		   ComponentID* provider, PortInfo* providingPortName, 
		   string connectionName) throw (CCAException) = 0;

      /** Disconnect the instance of an already created (instantiated)
	  component residing in the framework of the BuilderService.
	  @param connectionName The name of the connection assigned in 
	  the connect() method.
      */
      virtual void disconnect(ConnectionInfo* ci) throw (CCAException) = 0;


      ///////////////////////////////////////////////////////////////
      //// Composite key-value configuration ports.

      /** Get the strings in a named KeyValue port from an instance. 
	  @param cid The ComponentID (from getComponentInstances) of a
	  component in this framework.
	  @param portName The name of a port on the named component.
	  @param kvl The list to append the keys and values to, in
	  key, value, key, value order.
	  @return N, a number of keys >= 0 appended to kvl if all went well;
	  The number of strings appended to kvl is 2*N because
	  there are also values.
      */
      //# sidlpragma flow in in inout
      virtual ParameterList* getConfiguration(ComponentID* cid, 
			  PortInfo* info) throw (CCAException) = 0;

      /** Set strings in a named KeyValue port on an instance.
	  @param cid The ComponentID (from getComponentInstances) of a
	  component in this framework.
	  @param portName The name of a port on the named component.
	  @param kvl The list of alternating key, value pairs of strings
	  to be set on the component and port specified
	  in key, value, key, value order. kvl will not be modified.
	  @param start The position within kvl where the strings to be
	  processed start.
	  @param count The number of keys to be read from kvl, starting 
	  at position start. A total of 2*count strings will
	  be used in setting values.
	  @return N, a number of keys >= 0 and values copied from kvl.
	  Throws an exception for bad input parameters or some other error.
	  The number of strings processed is 2*N because
	  there are always values.
      */
      //# sidlpragma flow in in inout in in
      virtual void setConfiguration(ComponentID* cid, PortInfo* info, 
				   ParameterList* params) 
	throw (CCAException) = 0;


      ///////////////////////////////////////////////////////////////
      //// Composite go ports
      /** Set a named component and GoPort in motion.
       */
      virtual void go(ComponentID* cid, PortInfo* info) 
	throw (CCAException) = 0;
    };

  }; // namespace cca
}; // namespace gov

#endif // __BUILDERSERVICE_H__
