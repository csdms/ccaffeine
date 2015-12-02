#ifndef NeoParameterPortFactoryWrap_h_seen
#define NeoParameterPortFactoryWrap_h_seen

/**
 */
class NeoParameterPortFactoryWrap : public virtual neo::cca::ports::ParameterPortFactory
{

private:
	::ccafeopq::ports::ParameterPortFactory *oppf;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);


public:
	NeoParameterPortFactoryWrap( ccafeopq::ports::ParameterPortFactory *oppf);

	// never use this constructor. testing only.
	NeoParameterPortFactoryWrap(int bogon);

	virtual ~NeoParameterPortFactoryWrap();


// neo binding of the factory interface.
// we are our own wrapper.
	
	virtual void createParameterPort(neo::cca::TypeMap_shared portData, const ::std::string & portName);


	virtual void setBatchTitle(neo::cca::TypeMap_shared portData, const ::std::string & title);

	virtual void setGroupName(neo::cca::TypeMap_shared portData, const std::string & newGroupName);

	virtual void setGroupNameAndTitle(neo::cca::TypeMap_shared portData, const std::string & newGroupName, const std::string & title);

	virtual void addRequestBoolean(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				bool deflt);

	virtual void addRequestInt(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				int deflt,
				int low,
				int high);

	virtual void addRequestLong(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				int64_t deflt,
				int64_t low,
				int64_t high);

	virtual void addRequestFloat(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				float deflt,
				float low,
				float high);

	virtual void addRequestDouble(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				double deflt,
				double low,
				double high);

	virtual void addRequestString(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				const std::string & deflt);

	virtual void addRequestStringChoice(neo::cca::TypeMap_shared portData,
		const std::string & key, const std::string &choice);

	virtual void addStringChoices(neo::cca::TypeMap_shared portData,
	                        const std::string & key,
				std::vector< std::string > choices);

	virtual void addIntChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< int32_t > choices);

	virtual void addIntChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	int32_t choices[], size_t nChoices);

	virtual void addLongChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< int64_t > choices);

	virtual void addLongChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	int64_t choices[], size_t nChoices);

	virtual void addFloatChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< float > choices);

	virtual void addFloatChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	float choices[], size_t nChoices);

	virtual void addDoubleChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< double > choices);

	virtual void addDoubleChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	double choices[], size_t nChoices);

	virtual void addFcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< float > > choices);

	virtual void addFcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::complex< float > choices[], size_t nChoices);

	virtual void addDcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< double > > choices);

	virtual void addDcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::complex< double > choices[], size_t nChoices);


	virtual void clearRequests(neo::cca::TypeMap_shared portData);


	virtual void registerUpdater(neo::cca::TypeMap_shared portData, 
			neo::cca::ports::ParameterGetListener *powner);

	virtual void registerUpdatedListener(neo::cca::TypeMap_shared portData,
			neo::cca::ports::ParameterSetListener *powner);

	virtual void addParameterPort(neo::cca::TypeMap_shared portData, neo::cca::Services * svc);

	virtual void removeParameterPort(neo::cca::TypeMap_shared portData, neo::cca::Services * svc);


}; // end class NeoParameterPortFactoryWrap

extern NeoParameterPortFactoryWrap NeoParameterPortFactoryWrap_test;

#endif // NeoParameterPortFactoryWrap_h_seen
