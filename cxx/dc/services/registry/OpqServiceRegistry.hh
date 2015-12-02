#ifndef opq_service_registry_hh_seen
#define opq_service_registry_hh_seen

/**
 * ServiceRegistry is a Port that is primordially provided by the framework
 * and can be fished out by a component wishing to provide service Ports. 
 * Each binding has to provide a wrapping of this Service.
 * In the bindings (eg. neo and classic) the component space version
 * of this port will have a raw pointer instead of a shared one.
 */
class OpqServiceRegistry : public virtual ccafeopq::ServiceRegistry,
public virtual KernelPort
{
private:
	/** type and port */
	std::map< std::string, ccafeopq::Port *> singletons;
	/** type and portname */
	std::map< std::string, std::string > singletonNames;
	/** type and server */
	std::map< std::string, ccafeopq::ServiceProvider_shared > servers;
	/** wall of the frame, which is the provider of all the
	singleton services */
	ccafeopq::Services *wall;

public:
  OpqServiceRegistry();
  virtual ~OpqServiceRegistry();
//---------------------------------------------------------
// -------- the framework used interface.
    void startup(ccafeopq::Services *wall);
    void shutdown();
    /** Lookup what should be connected, if a service has been provided.
	@param serviceType port class name (input)
	@param serverName component instance name (output)
	@param serverPort port instance name (output)
      */
    bool serverAvailable(const std::string & serviceType, std::string &serverName, std::string & serverPort);


//---------------------------------------------------------
// ------ the public port used by component writers.
    /**
     * Add a ServiceProvider that can be asked to produce service Port's
     * for other components to use subsequently.
     * True means success. False means that for some reason, the
     * provider isn't going to function.
     */
    virtual bool addService(const std::string & type, ccafeopq::ServiceProvider_shared portProvider);

    /** Add a "reusable" service gov.cca.Port for other components to use 
     * subsequently.
     */
    virtual bool addSingletonService(const std::string & type, ccafeopq::Port * service);

    /** Inform the framework that this service Port is no longer to
     * be used, subsequent to this call. This is likely to
     * cause an exception unless all the ports obtained from the
     * previously added services have been released and disconnected.
     */
    virtual void removeService(const std::string & serviceType);


}; // class ServiceRegistry

#endif //opq_service_registry_hh_seen
