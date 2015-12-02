#ifndef classic_ClassicGoPortWrap_hh_seen
#define classic_ClassicGoPortWrap_hh_seen

/**
*/
class ClassicGoPortWrap : public virtual classic::gov::cca::GoPort
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
	ccafeopq::ComponentID_shared findOID( classic::gov::cca::ComponentID_shared nid);
	
	/** canonicalize a connectionid. if many, take first found. */
	::ccafeopq::ConnectionID_shared findOConnID( classic::gov::cca::ConnectionID_shared bconn);

	/** canonicalize a connectionid, aware that there may be multiple */
	std::vector< ::ccafeopq::ConnectionID_shared > findOConnIDs( classic::gov::cca::ConnectionID_shared bconn);

#endif

public:

	/** real constructor */
	ClassicGoPortWrap( ccafeopq::GoPort *obs);
	/** qc test dummy */
	ClassicGoPortWrap( int bogon );

	virtual ~ClassicGoPortWrap();

	// inherited bs interface here:

	/** 
	 * Creates an instance of a CCA component of the type defined by the
	 * string className.
	 * Memory lifecycle:
	 * The ComponentID_shared can be dropped on the floor if desired;
	 * that won't cause the component instance to stop existing.
	 */
	virtual int go() ;
};

#endif // classic_ClassicGoPortWrap_hh_seen
