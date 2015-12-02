#ifndef  BabelOpaqueServiceProvider_hh_seen
#define  BabelOpaqueServiceProvider_hh_seen


 /** wrapper for opq from neo.
 */
class BabelOpaqueServiceProvider : public virtual ccafeopq::ServiceProvider,
	public virtual BabelOpaquePort
{
private:
	gov::cca::ports::ServiceProvider sp;
	ccafeopq::ComponentID_shared cid;

public:
	BabelOpaqueServiceProvider( gov::cca::ports::ServiceProvider nsp, ccafeopq::ComponentID_shared c);

	virtual ~BabelOpaqueServiceProvider();

	static ccafeopq::ServiceProvider_shared createWrap(gov::cca::ports::ServiceProvider nsp, ccafeopq::ComponentID_shared c);

	virtual ccafeopq::ComponentID_shared getProviderID();



	/**
	* Create the Port for the Service, informing the framework through
	* "addProvidesPort()" on the originating component.
	* @return the name of the port created.
	*/
	virtual const std::string createService(const std::string & portType);

	/** Informs the originating component that the instance of the
	* provided service is no longer needed. The BabelOpaqueServiceProvider
	* can now safely removePort on the named port.
	*/
	virtual void destroyService(const std::string & portName);   


	/** override this if you inherit this base into a neo port
	* implementation.
	*/
	virtual ::gov::cca::Port getBabelPort();

}; // end class BabelOpaqueServiceProvider

typedef boost::shared_ptr< BabelOpaqueServiceProvider > BabelOpaqueServiceProvider_shared;

#endif // BabelOpaqueServiceProvider_hh_seen
