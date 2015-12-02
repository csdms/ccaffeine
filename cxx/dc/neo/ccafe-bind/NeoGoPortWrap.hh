#ifndef neo_NeoGoPortWrap_hh_seen
#define neo_NeoGoPortWrap_hh_seen

/**
*/
class NeoGoPortWrap : public virtual neo::cca::ports::GoPort
{

private:
	::ccafeopq::GoPort *cbs;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);

#if 0
	/////////// support stuff
	/** canonicalize the componentid. */
	ccafeopq::ComponentID_shared findOID( neo::cca::ComponentID_shared nid);
	
	/** canonicalize a connectionid. if many, take first found. */
	::ccafeopq::ConnectionID_shared findOConnID( neo::cca::ConnectionID_shared bconn);

	/** canonicalize a connectionid, aware that there may be multiple */
	std::vector< ::ccafeopq::ConnectionID_shared > findOConnIDs( neo::cca::ConnectionID_shared bconn);
#endif

public:

	/** real constructor */
	NeoGoPortWrap( ccafeopq::GoPort *obs);
	/** qc test dummy */
	NeoGoPortWrap( int bogon );

	virtual ~NeoGoPortWrap();

	// inherited bs interface here:

	/** 
	 * Creates an instance of a CCA component of the type defined by the
	 * string className.
	 * Memory lifecycle:
	 * The ComponentID_shared can be dropped on the floor if desired;
	 * that won't cause the component instance to stop existing.
	 */
	virtual int go() throw ( ::neo::cca::Exception ); 
};

#endif // neo_NeoGoPortWrap_hh_seen
