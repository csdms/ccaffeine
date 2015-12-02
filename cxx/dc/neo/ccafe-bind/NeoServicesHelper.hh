#ifndef Neo_ServicesHelper_h_seen
#define Neo_ServicesHelper_h_seen

#include <string>
class NeoServicesHelperPrivate;

/** The neo nasty legacy 'service' ports provider.
 * This should really go away.
 * In the mean time, the interface hides all the implementation
 * details so that other bindings can supply a NeoServicesHelper
 * to their components through their componentwrapper class to opaque.
 */
class NeoServicesHelper : public virtual ::ccafeopq::ServicesHelper
{
private:
	NeoServicesHelperPrivate *hp;

public:
	NeoServicesHelper();
	NeoServicesHelper(int bogon);

	virtual ~NeoServicesHelper();

	virtual ::ccafeopq::Port * checkSupport( const std::string & portName,
		       	const std::string & portType, ::ccafeopq::SvcPortMap & gpm);

	virtual void destroy();

	virtual void initComm(int64_t fComm);
	void addBindingDelegates( ::ccafeopq::Services *os );

	/* Return a  (possibly empty) shared reference
	   to a converter appropriate to the type of opaque port given.

	   Note: this function is defined as it is to keep the code maintenance
	   simple. The lines needed in here are a subset of the lines needed in
	   registerForConversionType.
	*/
	static NeoPortConverter_shared findConversion( ::ccafeopq::Port *);

	/** Return the port type to register with the framework,
	 * which may be different from the portType given if an
	 * adapter is needed. Also adds the converter to the
	 * portConversions map.
	 */
	static std::string registerForConversionType(ccafeopq::ComponentID_shared c,  std::string portName, std::string portType, std::map< std::string, NeoPortConverter_shared > & portConversions);

	/** generate exception if member is null.
	  @param className fully qualified class.
	  @param funcName member function calling checkthrow.
	  @param memberName name of pointer.
	  @param member pointer to check for being null.
	 */
	static void checkthrow(const char * className, const char * memberName, void * member, const char *funcName);

	/** return a special opq wrapper for supported types.
	 * If type is not supported, returns null.
	 * @param nport port from user component.
	 * @param portName port instance name from component.
	 * @param portType port class name from component.
	 * @param portProperties properties from component.
	 * @param supportedType OUTPUT string that will be set to the
	 * 	port type to be registered with the framework if the
	 * 	returned pointer is not null.
	 */
	static ::ccafeopq::Port * createSpecialProvider( neo::cca::Port * nport, const std::string & portName, const std::string & portType, ccafeopq::TypeMap_shared portProperties, std::string & supportedType);

	static neo::cca::Port * translate(const std::string name, ::ccafeopq::Port * op);

};

#endif // Neo_ServicesHelper_h_seen
