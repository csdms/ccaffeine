#ifndef Classic_ServicesHelper_h_seen
#define Classic_ServicesHelper_h_seen

#include <string>
class ClassicServicesHelperPrivate;

/** The classic nasty legacy 'service' ports provider.
 * This should really go away.
 * In the mean time, the interface hides all the implementation
 * details so that other bindings can supply a ClassicServicesHelper
 * to their components through their componentwrapper class to opaque.
 */
class ClassicServicesHelper : public virtual ::ccafeopq::ServicesHelper
{
private:
	ClassicServicesHelperPrivate *hp;

public:
	ClassicServicesHelper();

	virtual ~ClassicServicesHelper();

	virtual void initComm(int64_t fComm);

	virtual ::ccafeopq::Port * checkSupport( const std::string & portName,
		       	const std::string & portType, ::ccafeopq::SvcPortMap & gpm);

	virtual void destroy();

	void addBindingDelegates( ::ccafeopq::Services *os );

	/** exit with a message. */
	static void checkthrow(const char * className, const char * memberName, void * member, const char *funcName);

	/** a hack to route neo ports to classic if properly tagged . */
	static classic::gov::cca::Port * translate(const std::string name, ::ccafeopq::Port * op);

	/** find out if theres' a canonical opaque port we map to and do that. */
	static std::string registerForConversionType(ccafeopq::ComponentID_shared c,  std::string portName, std::string portType, std::map< std::string, ClassicPortConverter_shared > & portConversions);

};
#endif // Classic_ServicesHelper_h_seen
