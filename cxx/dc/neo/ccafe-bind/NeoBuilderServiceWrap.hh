#ifndef neo_NeoBuilderServiceWrap_hh_seen
#define neo_NeoBuilderServiceWrap_hh_seen

/**
*/
class NeoBuilderServiceWrap : public virtual neo::cca::ports::BuilderService
{

private:
	::ccafeopq::BuilderService *cbs;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);

	/////////// support stuff
	/** canonicalize the componentid. */
	ccafeopq::ComponentID_shared findOID( neo::cca::ComponentID_shared nid);
	
	/** canonicalize a connectionid. if many, take first found. */
	::ccafeopq::ConnectionID_shared findOConnID( neo::cca::ConnectionID_shared bconn);

	/** canonicalize a connectionid, aware that there may be multiple */
	std::vector< ::ccafeopq::ConnectionID_shared > findOConnIDs( neo::cca::ConnectionID_shared bconn);

public:

	/** real constructor */
	NeoBuilderServiceWrap( ccafeopq::BuilderService *obs);
	/** qc test dummy */
	NeoBuilderServiceWrap( int bogon );

	virtual ~NeoBuilderServiceWrap();

	// inherited bs interface here:

	/** 
	 * Creates an instance of a CCA component of the type defined by the
	 * string className.
	 * Memory lifecycle:
	 * The ComponentID_shared can be dropped on the floor if desired;
	 * that won't cause the component instance to stop existing.
	 */
	virtual neo::cca::ComponentID_shared createInstance(const ::std::string & instanceName, const ::std::string & className, ::neo::cca::TypeMap_shared properties) throw ( ::neo::cca::Exception ); 
	/** Convenience function, for those with no interesting properties to
	 * put in. */
	virtual neo::cca::ComponentID_shared createInstance(const ::std::string & instanceName, const ::std::string & className) throw ( ::neo::cca::Exception ) ; 

	/** Get component list.
	 * Memory lifecycle:
	 * The vector is returned on the stack and when it goes out of scope,
	 * all the ComponentID_shared take care of themselves.
	 * @return a ComponentID for each component currently created.
	 */
	virtual ::std::vector< neo::cca::ComponentID_shared > getComponentIDs() throw ( ::neo::cca::Exception ); 

	/** 
	 * Get property map for component.
	 * Memory Lifecycle:
	 * The info is returned on the stack and takes care of itself
	 * per shared_ptr.
	 *  @return the public properties associated with the component 
	 *  referred to by ComponentID.
	 *  @throws a Exception if the ComponentID is invalid.
	*/
	virtual ::neo::cca::TypeMap_shared getComponentProperties( neo::cca::ComponentID_shared cid) throw ( ::neo::cca::Exception );

	/**
	 *  Causes the framework implementation to associate the given properties
	 *  with the component designated by cid.
	 *  @throws Exception if cid is invalid or if there is an attempted
	 *  change to a property locked by the framework implementation.
	 */
	virtual void setComponentProperties( neo::cca::ComponentID_shared cid, ::neo::cca::TypeMap_shared map) throw ( ::neo::cca::Exception );

	/** 
	 * Get component id from stringified reference.
	 * Memory Lifecycle:
	 * The id is returned on the stack and takes care of itself
	 * per shared_ptr.
	 * @return a ComponentID from the string produced by
	 * ComponentID.getSerialization().
	 * @throws Exception if the string does not represent the appropriate
	 * serialization of a ComponentID for the underlying framework.
	*/
	virtual neo::cca::ComponentID_shared getDeserialization( const ::std::string & s) throw ( ::neo::cca::Exception );

	/**
	 *  Get id from name by which it was created.
	 * Memory Lifecycle:
	 * The id is returned on the stack and takes care of itself per shared_ptr.
	 * @return a ComponentID from the instance name of the component
	 * produced by ComponentID.getInstanceName().
	 * @throws Exception if there is no component matching the
	 * given componentInstanceName.
	*/
	virtual neo::cca::ComponentID_shared getComponentID( const ::std::string & componentInstanceName) throw ( ::neo::cca::Exception );

	 /** 
	  *  Eliminate the Component instance, from the scope of the framework.
	  *  Memory lifecycle:
	  *  On return, toDie will still be a valid pointer, but queries
	  *  on it should throw exceptions because the component has been 
	  *  destroyed.
	  *  @param toDie the component to be removed.
	  *  @param timeout the allowable wait; 0 means up to the framework.
	  *  @throws Exception if toDie refers to an invalid component, or
	  *  if the operation takes longer than timeout seconds.
	  */
	virtual void destroyInstance( neo::cca::ComponentID_shared toDie, float timeout ) throw ( ::neo::cca::Exception );

	 /** 
	  *  Get the names of Port instances provided by the identified component.
	  * Memory lifecycle:
	  * The vector is returned on the stack and when it goes out of scope,
	  * all the string take care of themselves.
	  *  @param cid the component.
	  *  @throws Exception if cid refers to an invalid component.
	  */
	virtual ::std::vector< ::std::string > getProvidedPortNames( neo::cca::ComponentID_shared cid) throw ( ::neo::cca::Exception ); 

	 /** 
	  *  Get the names of Port instances used by the identified component.
	  * Memory lifecycle:
	  * The vector is returned on the stack and when it goes out of scope,
	  * all the string take care of themselves.
	  *  @param cid the component.
	  *  @throws Exception if cid refers to an invalid component.
	  */
	virtual ::std::vector< ::std::string > getUsedPortNames( neo::cca::ComponentID_shared cid) throw ( ::neo::cca::Exception ); 

	/**
	 *  Fetch map of Port properties exposed by the framework.
	 *  @return the public properties pertaining to the Port instance
	 *    portname on the component referred to by cid.
	 *  @throws Exception when any one of the following conditions occur:<ul>
	 *    <li>portname is not a registered Port on the component indicated by cid,
	 *    <li>cid refers to an invalid component. </ul>
	 */
	virtual ::neo::cca::TypeMap_shared getPortProperties( neo::cca::ComponentID_shared cid, const ::std::string & portname) throw ( ::neo::cca::Exception );

	/**
	 * Associates the properties given in map with the Port indicated by
	 *  portname. The component must have a Port known by portname.
	 *  @throws Exception if either cid or portname are
	 *  invalid, or if this a changed property is locked by
	 *   the underlying framework or component.
	*/
	virtual void setPortProperties( neo::cca::ComponentID_shared cid, const ::std::string & portname, ::neo::cca::TypeMap_shared map) throw ( ::neo::cca::Exception );

	/**
	 *   Creates a connection between ports on component user and
	 *   component provider. 
	 *   Destroying the ConnectionID does not
	 *   cause a disconnection; for that, see disconnect().
	 *   In anycase, the ConnectionID_shared destroys itself-- that is not
	 *   the user's concern.
	 *   @param user the caller component.
	 *   @param provider the callee component.
	 *   @param usingPortName name of the port in the caller.
	 *   @param providingPortName name of the port in the callee.
	 *   
	 *   @throws Exception when any one of the following conditions occur:<ul>
	 *   <li>If either user or provider refer to an invalid component,
	 *   <li>If either usingPortName or providingPortName refer to a
	 *   nonexistent Port on their respective component,
	 *   <li>If other-- In reality there are a lot of things that can go wrong
	 *   with this operation, especially if the underlying connections
	 *   involve networking.</ul>
	 */
	virtual neo::cca::ConnectionID_shared connect( neo::cca::ComponentID_shared  user, const ::std::string & usingPortName, neo::cca::ComponentID_shared provider, const ::std::string & providingPortName) throw ( ::neo::cca::Exception ); 

	/**
	* Returns a list of connections as an array of
	* handles. This will return all connections involving components
	* in the given componentList of ComponentIDs. This
	* means that ConnectionID's will be returned even if only one
	* of the participants in the connection appears in componentList.
	* Memory lifecycle:
	* The vector returned and ids therein clean themselves up
	* when leaving the calling scope.
	*
	* @throws Exception if any component in componentList is invalid.
	*/
	virtual ::std::vector < neo::cca::ConnectionID_shared > getConnectionIDs( ::std::vector< neo::cca::ComponentID_shared > & componentList) throw ( ::neo::cca::Exception ); 

	/**
	 *   Fetch property map of a connection.
	 *   Memory lifecycle: the map will delete itself when appropriate.
	 *   @returns the properties for the given connection.
	 *   @throws Exception if connID is invalid.
	*/
	virtual ::neo::cca::TypeMap_shared getConnectionProperties( neo::cca::ConnectionID_shared & connID) throw ( ::neo::cca::Exception );

	/**
	 * Associates the properties with the connection.
	 * @param map the source of the properties.
	 *   @param connID connection to receive property values.
	 *   @throws Exception if connID is invalid, or if this changes
	 *   a property locked by the underlying framework.
	 */
	virtual void setConnectionProperties( neo::cca::ConnectionID_shared & connID, ::neo::cca::TypeMap_shared map) throw ( ::neo::cca::Exception );

	/** 
	 * Disconnect the connection indicated by connID before the indicated
	 * timeout in secs. Upon successful completion, connID and the connection
	 * it represents become invalid.
	 * @param timeout the time in seconds to wait for a connection to close; 0
	 * means to use the framework implementation default.
	 * @param connID the one to break.
	 * @throws Exception when any one of the following conditions occur: <ul>
	 * <li>id refers to an invalid ConnectionID,
	 * <li>timeout is exceeded, after which, if id was valid before
	 * disconnect() was invoked, it remains valid
	 * </ul>
	 */
	virtual void disconnect( neo::cca::ConnectionID_shared & connID, float timeout) throw ( ::neo::cca::Exception ); 

	/**
	 * Remove all connections between components id1 and id2 within
	 * the period of timeout secs. If id2 is null, then all connections
	 * to id1 are removed (within the period of timeout secs).
	 * @throws Exception when any one of the following conditions occur:<ul>
	 *  <li>id1 or id2 refer to an invalid ComponentID (other than id2 == null),
	 *  <li>The timeout period is exceeded before the disconnections can be made.
	 *  </ul>
	 */
	virtual void disconnectAll( neo::cca::ComponentID_shared & id1, neo::cca::ComponentID_shared & id2, float timeout) throw ( ::neo::cca::Exception ); 


};  // end class NeoBuilderServiceWrap

extern NeoBuilderServiceWrap NeoBuilderServiceWrap_test;
#endif // neo_NeoBuilderServiceWrap_hh_seen
