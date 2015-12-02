#ifndef NeoComponentClassDescription_hh_seen
#define NeoComponentClassDescription_hh_seen

class NeoComponentClassDescription;

typedef boost::shared_ptr< NeoComponentClassDescription > NeoComponentClassDescription_shared;

class NeoComponentClassDescription : 
public virtual neo::cca::ports::ComponentClassDescription
//, public virtual ccafeopq::ComponentClassDescription_Interface can't do this
{

private:
	ccafeopq::ComponentClassDescription_shared fwk_desc;
	bool wrapper;
	std::string name;
	std::string alias;

public:
	/** neo bound description. */
	NeoComponentClassDescription( std::string className, std::string classAlias);

	virtual ~NeoComponentClassDescription();
	virtual ::std::string getComponentClassName() throw (neo::cca::Exception );
	virtual ::std::string getDeploymentClassAlias() throw (neo::cca::Exception );
	virtual ::std::string getCCASpecBinding() throw (neo::cca::Exception );

	// unsupported yet. all below may throw exceptions if called.
	// on a description backed by a neo component.
	virtual ::std::string getIndexFile() throw (neo::cca::Exception);
	virtual ::std::string getConstructorName() throw (neo::cca::Exception);
	virtual ::std::string getLibraryLoading() throw (neo::cca::Exception);
	virtual ::std::string getLibraryName() throw (neo::cca::Exception);
	virtual ::std::string getLibraryLocation() throw (neo::cca::Exception);
	virtual ::std::string getExecScript() throw (neo::cca::Exception);
	virtual void getDOMTree() throw (neo::cca::Exception);

	///////////////////////////////////////////////////////////////////////
	
	/** Causes isWrapper to be true. allows us to export other binding
	 * descriptions to neo space.
	 */
	NeoComponentClassDescription( ccafeopq::ComponentClassDescription_shared opqDesc);

	/** return true if wrapping an opq CCD, false if neo bound. */
	bool isWrapper();

	/** return opq CCD if isWrapper == true, else nil opq CCD */
       	ccafeopq::ComponentClassDescription_shared unwrap();

	/** utility function to reduce shared_ptr screwups */
	static NeoComponentClassDescription_shared wrapOpaque( ccafeopq::ComponentClassDescription_shared opqDesc);
};



#endif // NeoComponentClassDescription_hh_seen
