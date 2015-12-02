#ifndef ClassicPortConverter_Interface_hh_seen
#define ClassicPortConverter_Interface_hh_seen

// requires cca.hh, ccafeopq.hh

/**Interface to translate ccafeopq::Port's to classic::gov::cca::Port's
 */
class ClassicPortConverter_Interface
{
private:
// nothing
public:
	virtual ~ClassicPortConverter_Interface() {}
	virtual classic::gov::cca::Port *convert( ::ccafeopq::Port * ) = 0;
};

typedef boost::shared_ptr< ClassicPortConverter_Interface > ClassicPortConverter_shared;

#endif // ClassicPortConverter_Interface_hh_seen
