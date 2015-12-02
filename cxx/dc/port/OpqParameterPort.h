#ifndef ParameterPort_Impl_h_seen
#define ParameterPort_Impl_h_seen
////////////////////////////////////////////////////////////
// private port implementation
// it supports kernel, classic.

namespace ccafe {

class ParameterPort_Impl : 
#ifdef HAVE_CLASSIC
	public virtual classic::gov::cca::Port,
#endif // HAVE_CLASSIC
			public virtual ccafeopq::ports::ParameterPort,
#ifdef HAVE_CLASSIC
			public virtual ClassicOpaquePort,
#endif // HAVE_CLASSIC
			public virtual StringableParameterPort,
			public virtual KernelPort
{
private:

	std::vector< ::ccafeopq::ports::ParameterGetListener_shared > glv;
	std::vector< ::ccafeopq::ports::ParameterSetListener_shared > slv;
	ccafeopq::TypeMap_shared portData;
	bool published;
	bool basiconly; // transient wrapper.
	// true if key given is the name of a parameter 
	bool hasKey( const std::string & key);

public:
	ParameterPort_Impl( ccafeopq::TypeMap_shared data, bool basic=false);
	virtual ~ParameterPort_Impl();

#ifdef HAVE_CLASSIC
	virtual classic::gov::cca::Port * getClassicPort();
#endif


	// Stringable interface
	virtual std::string getConfigurationString( const std::string & prefix);
	virtual std::string getConfigurationString( const std::string & prefix, const std::string & key);
	virtual int setConfigurationString( const std::string & key, const std::string & value);

	// used by factory only.
	void addSetListener( ::ccafeopq::ports::ParameterSetListener_shared sl);
	void addGetListener( ::ccafeopq::ports::ParameterGetListener_shared gl);
	void clearListeners();
	bool getPublished();
	void setPublished(bool tf);
	std::string toString( const std::string & prefix, ::ccafeopq::TypeMap_shared d, const std::string &key);
	std::string toStringArray( const std::string & prefix, ::ccafeopq::TypeMap_shared d, const std::string &key);

  // opaque version of SIDL ParameterPort interface
	// adjusted for the fact of multiple bindings.
	virtual std::vector< std::string > readConfigurationKeys();
	virtual ccafeopq::TypeMap_shared  readConfigurationMap();
	virtual void writeConfigurationMap( ccafeopq::TypeMap_shared tm);
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
	virtual std::vector< int32_t > readDefaultIntArray( const std::string &
	key);
	virtual std::vector< int64_t > readDefaultLongArray( const std::string & key);
	virtual std::vector< float > readDefaultFloatArray( const std::string &
	key);
	virtual std::vector< double > readDefaultDoubleArray( const std::string
	& key);
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

	static const std::string & k_PORTNAME() ;
	static const std::string & k_PUBPORTNAME();
	static const std::string & k_TITLE();
	static const std::string & k_ALLKEYS();
	static const std::string & k_GROUPS() ;
	static const std::string & k_CURGROUP() ;
	static const std::string & k_GROUPKEYS() ;
	static const std::string & k_DEFAULT() ;
	static const std::string & k_BOUNDS() ;
	static const std::string & k_BOUNDED() ;
	static const std::string & k_CHOICES() ;
	static const std::string & k_HELP();
	static const std::string & k_PROMPT();
	static const std::string & k_HASKEY();

}; // end implementation ParameterPort_Impl

} ENDSEMI // namespace ccafe

#endif // ParameterPort_Impl_h_seen

