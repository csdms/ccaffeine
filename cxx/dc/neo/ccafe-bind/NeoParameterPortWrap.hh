#ifndef neo_ParameterPortWrap_hh
#define neo_ParameterPortWrap_hh

/**
*/
class NeoParameterPortWrap : public virtual neo::cca::ports::ParameterPort
{

private:
	::ccafeopq::ports::ParameterPort *opp;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);
	

public:

	/** real constructor */
	NeoParameterPortWrap( ccafeopq::ports::ParameterPort *opp);

	/** qc test constructor */
	NeoParameterPortWrap( int bogon );

	virtual ~NeoParameterPortWrap();


	virtual ::neo::cca::TypeMap_shared readConfigurationMap() throw ( ::neo::cca::Exception);

	virtual void writeConfigurationMap ( neo::cca::TypeMap_shared map) throw ( ::neo::cca::Exception);

	virtual std::vector< ::std::string> readConfigurationKeys() throw ( ::neo::cca::Exception) ;

	//-----------------------
	

	virtual std::string readTitle();
	virtual std::vector< std::string > readGroupNames();
	virtual std::string readGroupTitle( const std::string & groupName);
	virtual std::vector< std::string > readGroupKeys( const std::string & groupName );

	virtual std::string readHelp( const std::string & key);
	virtual std::string readPrompt( const std::string & key);
	virtual bool hasBounds( const std::string & key);
	virtual bool hasChoices( const std::string & key);

	virtual bool readDefaultBoolean( const std::string & key);
	virtual std::string readDefaultString ( const std::string & key);
	virtual int32_t readDefaultInt( const std::string & key);
	virtual int64_t readDefaultLong( const std::string & key);
	virtual float readDefaultFloat ( const std::string & key);
	virtual double readDefaultDouble( const std::string & key);
	virtual std::complex<float> readDefaultFcomplex( const std::string & key);
	virtual std::complex<double> readDefaultDcomplex( const std::string & key);

	virtual std::vector< std::string > readDefaultStringArray( const std::string & key);
	virtual std::vector< bool > readDefaultBooleanArray( const std::string & key);
	virtual std::vector< int32_t > readDefaultIntArray( const std::string & key);
	virtual std::vector< int64_t > readDefaultLongArray( const std::string & key);
	virtual std::vector< float > readDefaultFloatArray( const std::string & key);
	virtual std::vector< double > readDefaultDoubleArray( const std::string & key);
	virtual std::vector< std::complex<float> > readDefaultFcomplexArray( const std::string & key);
	virtual std::vector< std::complex<double> > readDefaultDcomplexArray( const std::string & key);
	
	virtual void readBoundsInt(const std::string & key, int32_t & low, int32_t & high);
	virtual void readBoundsLong(const std::string & key, int64_t & low, int64_t & high);
	virtual void readBoundsFloat(const std::string & key, float & low, float & high);
	virtual void readBoundsDouble(const std::string & key, double & low, double & high);

	virtual std::vector< std::string > readChoicesString(const std::string & key);
	virtual std::vector< int32_t > readChoicesInt(const std::string & key);
	virtual std::vector< int64_t > readChoicesLong(const std::string & key);
	virtual std::vector< float > readChoicesFloat(const std::string & key);
	virtual std::vector< double > readChoicesDouble(const std::string & key);
	virtual std::vector< std::complex<float> > readChoicesFcomplex(const std::string & key);
	virtual std::vector< std::complex<double> > readChoicesDcomplex(const std::string & key);


};  // end class NeoParameterPortWrap

#endif // neo_ParameterPortWrap_hh
