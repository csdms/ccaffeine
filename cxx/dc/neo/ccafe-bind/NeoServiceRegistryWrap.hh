#ifndef NeoServiceRegistryWrap_h_seen
#define NeoServiceRegistryWrap_h_seen

/**
 */
class NeoServiceRegistryWrap : public virtual neo::cca::ports::ServiceRegistry
{

private:
	::ccafeopq::ServiceRegistry *oppf;
	ccafeopq::ComponentID_shared cid;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);

	/** ports registered singleton, keyed by neo type. */
	std::map< std::string, ccafeopq::Port * > opqSingletons;

	/** names registered with opq layer, keyed by neo type. */
	std::map< std::string, std::string > opqSingletonCanonical;


public:
	NeoServiceRegistryWrap( ccafeopq::ServiceRegistry *oppf, ccafeopq::ComponentID_shared c);


	ccafeopq::ComponentID_shared getProviderID();

	// never use this constructor. testing only.
	NeoServiceRegistryWrap(int bogon);

	virtual ~NeoServiceRegistryWrap();


	/**
	* Add a ServiceProvider that can be asked to produce service Port's
	* for other components to use subsequently.
	* True means success. False means that for some reason, the
	* provider isn't going to function.
	*/
	virtual bool addService(const std::string & type, neo::cca::ports::ServiceProvider * portProvider);

	/** Add a "reusable" service gov.cca.Port for other components to use 
	* subsequently.
	*/
	virtual bool addSingletonService(const std::string & type, neo::cca::Port * service);

	/** Inform the framework that this service Port is no longer to
	* be used, subsequent to this call. This is likely to
	* cause an exception unless all the ports obtained from the
	* previously added services have been released and disconnected.
	*/
virtual void removeService(const std::string & serviceType);


}; // end class NeoServiceRegistryWrap

extern NeoServiceRegistryWrap NeoServiceRegistryWrap_test;

#endif // NeoServiceRegistryWrap_h_seen
