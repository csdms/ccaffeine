#ifndef NeoPortConverter_Interface_hh_seen
#define NeoPortConverter_Interface_hh_seen

// requires neocca.hh, ccafeopq.hh

/**Interface to translate ccafeopq::Port's to neo::cca::Port's
 */
class NeoPortConverter_Interface
{
private:
// nothing
public:
	virtual ~NeoPortConverter_Interface() {}
	virtual neo::cca::Port *convert( ::ccafeopq::Port * ) = 0;
};

typedef boost::shared_ptr< NeoPortConverter_Interface > NeoPortConverter_shared;

#endif // NeoPortConverter_Interface_hh_seen
