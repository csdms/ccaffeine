#ifndef NeoOpaqueParameterGetListener_hh_seen
#define NeoOpaqueParameterGetListener_hh_seen
class NeoOpaqueParameterGetListener : public virtual ccafeopq::ports::ParameterGetListener
{
private:
	::neo::cca::ports::ParameterGetListener * pgl;

public:
	NeoOpaqueParameterGetListener( ::neo::cca::ports::ParameterGetListener * npgl);
	NeoOpaqueParameterGetListener( int bogon ) : pgl(0) {}

	virtual ~NeoOpaqueParameterGetListener();
	virtual bool updateParameterPort(const std::string & portName);
};

#endif // NeoOpaqueParameterGetListener_hh_seen
