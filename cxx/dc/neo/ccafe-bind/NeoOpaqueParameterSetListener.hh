#ifndef NeoOpaqueParameterSetListener_hh_seen
#define NeoOpaqueParameterSetListener_hh_seen
class NeoOpaqueParameterSetListener : public virtual ccafeopq::ports::ParameterSetListener
{
private:
	::neo::cca::ports::ParameterSetListener * psl;

public:
	NeoOpaqueParameterSetListener( ::neo::cca::ports::ParameterSetListener * npsl);
	NeoOpaqueParameterSetListener( int bogon ) : psl(0) {}

	virtual ~NeoOpaqueParameterSetListener();
	virtual void updatedParameterValue(std::string portName, std::string fieldName);
};

#endif // NeoOpaqueParameterSetListener_hh_seen
