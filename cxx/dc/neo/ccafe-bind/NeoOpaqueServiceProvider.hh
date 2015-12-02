#ifndef  NeoOpaqueServiceProvider_hh_seen
#define  NeoOpaqueServiceProvider_hh_seen


 /** wrapper for opq from neo.
 */
class NeoOpaqueServiceProvider : public virtual ccafeopq::ServiceProvider,
	public virtual NeoOpaquePort
{
private:
	neo::cca::ports::ServiceProvider * sp;
	ccafeopq::ComponentID_shared cid;

public:
	NeoOpaqueServiceProvider( neo::cca::ports::ServiceProvider * nsp, ccafeopq::ComponentID_shared c);

	virtual ~NeoOpaqueServiceProvider();

	static ccafeopq::ServiceProvider_shared createWrap(neo::cca::ports::ServiceProvider * nsp, ccafeopq::ComponentID_shared c);

	virtual ccafeopq::ComponentID_shared getProviderID();



	/**
	* Create the Port for the Service, informing the framework through
	* "addProvidesPort()" on the originating component.
	* @return the name of the port created.
	*/
	virtual const std::string createService(const std::string & portType);

	/** Informs the originating component that the instance of the
	* provided service is no longer needed. The NeoOpaqueServiceProvider
	* can now safely removePort on the named port.
	*/
	virtual void destroyService(const std::string & portName);   


	/** override this if you inherit this base into a neo port
	* implementation.
	*/
	virtual ::neo::cca::Port * getNeoPort();

}; // end class NeoOpaqueServiceProvider

typedef boost::shared_ptr< NeoOpaqueServiceProvider > NeoOpaqueServiceProvider_shared;

#endif // NeoOpaqueServiceProvider_hh_seen
