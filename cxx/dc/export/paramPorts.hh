#ifndef opaque_paramPorts_h_seen
#define opaque_paramPorts_h_seen

/** This is a file wherein we make opaque versions of
 * some services from sidl/babel that are more 
 * sane to babelify than using babel and trying to
 * turn it into virtual interfaces.
 *
 * To Wit:
 * 1 ParameterPortFactory
 * 2 BasicParameterPort
 * 3 ParameterPort
 * 4 ParameterGetListener
 * 5 ParameterSetListener
 *
 * This all lives in the namespace ccafeopq::ports
 * as there is legacy other stuff cluttering the ccafeopq space.
 */
namespace ccafeopq {
namespace ports {


class BasicParameterPort : public virtual ccafeopq::Port
{
public:
	virtual ~BasicParameterPort() {}

	/** return the names of available parameter maps. */
	virtual std::vector< std::string > readConfigurationKeys() = 0;

	/** return a *copy* of the named map, for the caller to modify. */
	// virtual ccafeopq::TypeMap_shared readConfigurationMapOpaque( ) = 0;
	virtual ccafeopq::TypeMap_shared  readConfigurationMap() = 0;

	/** take values from the modifed map, tm, and copy them to the
	 * internal map of the given name. Implementers are free to ignore
	 * irrelevant data given in tm.
	 */
	virtual void writeConfigurationMap( ccafeopq::TypeMap_shared tm) = 0;

}; // end interface BasicParameterPort

class ParameterPort : public virtual BasicParameterPort
{
public:
	virtual ~ParameterPort() {}

	// BasicParameterPort
	
	/** return the names of available parameter maps. */
	virtual std::vector< std::string > readConfigurationKeys() = 0;

	/** return a *copy* of the named map, for the caller to modify. */
	virtual ccafeopq::TypeMap_shared readConfigurationMap() = 0;

	/** take values from the modifed map, tm, and copy them to the
	 * internal map of the given name. Implementers are free to ignore
	 * irrelevant data given in tm.
	 */
	virtual void writeConfigurationMap( ccafeopq::TypeMap_shared tm) = 0;

	virtual std::string readTitle() = 0;
	virtual std::vector< std::string > readGroupNames() = 0;
	virtual std::string readGroupTitle( const std::string & groupName) = 0;
	virtual std::vector< std::string > readGroupKeys( const std::string & groupName ) = 0;

	virtual std::string readHelp( const std::string & key) = 0;
	virtual std::string readPrompt( const std::string & key) = 0;
	virtual bool hasBounds( const std::string & key) = 0;
	virtual bool hasChoices( const std::string & key) = 0;

	virtual bool readDefaultBoolean( const std::string & key) = 0;
	virtual std::string readDefaultString ( const std::string & key) = 0;
	virtual int32_t readDefaultInt( const std::string & key) = 0;
	virtual int64_t readDefaultLong( const std::string & key) = 0;
	virtual float readDefaultFloat ( const std::string & key) = 0;
	virtual double readDefaultDouble( const std::string & key) = 0;
	virtual std::complex<float> readDefaultFcomplex( const std::string & key) = 0;
	virtual std::complex<double> readDefaultDcomplex( const std::string & key) = 0;

	virtual std::vector< std::string > readDefaultStringArray( const std::string & key) = 0;
	virtual std::vector< bool > readDefaultBooleanArray( const std::string & key) = 0;
	virtual std::vector< int32_t > readDefaultIntArray( const std::string & key) = 0;
	virtual std::vector< int64_t > readDefaultLongArray( const std::string & key) = 0;
	virtual std::vector< float > readDefaultFloatArray( const std::string & key) = 0;
	virtual std::vector< double > readDefaultDoubleArray( const std::string & key) = 0;
	virtual std::vector< std::complex<float> > readDefaultFcomplexArray( const std::string & key) = 0;
	virtual std::vector< std::complex<double> > readDefaultDcomplexArray( const std::string & key) = 0;
	
	virtual void readBoundsInt(const std::string & key, int32_t & low, int32_t & high) = 0;
	virtual void readBoundsLong(const std::string & key, int64_t & low, int64_t & high) = 0;
	virtual void readBoundsFloat(const std::string & key, float & low, float & high) = 0;
	virtual void readBoundsDouble(const std::string & key, double & low, double & high) = 0;

	virtual std::vector< std::string > readChoicesString(const std::string & key) = 0;
	virtual std::vector< int32_t > readChoicesInt(const std::string & key) = 0;
	virtual std::vector< int64_t > readChoicesLong(const std::string & key) = 0;
	virtual std::vector< float > readChoicesFloat(const std::string & key) = 0;
	virtual std::vector< double > readChoicesDouble(const std::string & key) = 0;
	virtual std::vector< std::complex<float> > readChoicesFcomplex(const std::string & key) = 0;
	virtual std::vector< std::complex<double> > readChoicesDcomplex(const std::string & key) = 0;

}; // end interface ParameterPort

class ParameterGetListener;
class ParameterSetListener;

typedef boost::shared_ptr< ParameterGetListener > ParameterGetListener_shared;
typedef boost::shared_ptr< ParameterSetListener > ParameterSetListener_shared;

/** This class mostly follows the sidl documentation
 * for the class of the same name in the gov.cca namespace.
 */
class ParameterPortFactory : public virtual ccafeopq::Port
{
public:
	virtual ~ParameterPortFactory() {}

	/** Initialize the portData ...
	 */
	virtual void createParameterPort(TypeMap_shared portData, const ::std::string & portName) = 0;

	/** Define the window title for the parameter dialog.
	 **/
	virtual void setBatchTitle(TypeMap_shared portData, const ::std::string & title) = 0;
	
	/** Define the next tab/group title to use. All
	 * addRequest subsequent calls will add to this group.
	 * Multiple dialog tabs/groups can be defined in this way.
	 */
	virtual void setGroupName(TypeMap_shared portData, const std::string & newGroupName) = 0;
	virtual void setGroupNameAndTitle(TypeMap_shared portData, const std::string & newGroupName, const std::string & title) = 0;

	/** Define a boolean parameter and its default state.
	 */
	virtual void addRequestBoolean(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					bool deflt) = 0;

	/** Define a int parameter and its default state.
	 */
	virtual void addRequestInt(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					int deflt,
					int low,
					int high) = 0;

	/** Define a long parameter and its default state.
	 */
	virtual void addRequestLong(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					int64_t deflt,
					int64_t low,
					int64_t high) = 0;

	/** Define a float parameter and its default state.
	 * The configured value is always available by
	 * portData->getFloat(name, ...) and it will be
	 * in the range [low, high].
	 */
	virtual void addRequestFloat(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					float deflt,
					float low,
					float high) = 0;

	/** Define a double parameter and its default state.
	 */
	virtual void addRequestDouble(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					double deflt,
					double low,
					double high) = 0;

	/** Define a string parameter and its default state.
	 */
	virtual void addRequestString(TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					const std::string & deflt) = 0;
	/** define a new choice for a string parameter. */
	virtual void addRequestStringChoice(TypeMap_shared portData,
			const std::string & key, const std::string &choice) = 0;

	/** define more choices for a string parameter. */
	virtual void addStringChoices(TypeMap_shared portData,
		                        const std::string & key,
					std::vector< std::string > choices) = 0;

	/** define more choices for a int32 parameter. */
	virtual void addIntChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< int32_t > choices) = 0;

	/** define more choices for a int32 parameter, raw.
	 * nChoices is number of int elements in choices, not memory size. */
	virtual void addIntChoices(TypeMap_shared portData,
		const std::string & key,
		int32_t choices[], size_t nChoices) = 0;
	
	/** define more choices for a int64 parameter. */
	virtual void addLongChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< int64_t > choices) = 0;

	/** define more choices for a int64 parameter, raw. 
	 * nChoices is number of long elements in choices, not memory size. */
	virtual void addLongChoices(TypeMap_shared portData,
		const std::string & key,
		int64_t choices[], size_t nChoices) = 0;

	/** define more choices for a parameter. */
	virtual void addFloatChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< float > choices) = 0;

	/** define more choices for a parameter, raw. 
	 * nChoices is number of long elements in choices, not memory size. */
	virtual void addFloatChoices(TypeMap_shared portData,
		const std::string & key,
		float choices[], size_t nChoices) = 0;

	/** define more choices for a parameter. */
	virtual void addDoubleChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< double > choices) = 0;

	/** define more choices for a parameter, raw. 
	 * nChoices is number of long elements in choices, not memory size. */
	virtual void addDoubleChoices(TypeMap_shared portData,
		const std::string & key,
		double choices[], size_t nChoices) = 0;

	/** define more choices for a parameter. */
	virtual void addFcomplexChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< std::complex< float > > choices) = 0;

	/** define more choices for a parameter, raw. 
	 * nChoices is number of long elements in choices, not memory size. */
	virtual void addFcomplexChoices(TypeMap_shared portData,
		const std::string & key,
		std::complex< float > choices[], size_t nChoices) = 0;

	/** define more choices for a parameter. */
	virtual void addDcomplexChoices(TypeMap_shared portData,
		const std::string & key,
		std::vector< std::complex< double > > choices) = 0;

	/** define more choices for a parameter, raw. 
	 * nChoices is number of long elements in choices, not memory size. */
	virtual void addDcomplexChoices(TypeMap_shared portData,
		const std::string & key,
		std::complex< double > choices[], size_t nChoices) = 0;


	 /** Clear all previously added requests, titles, groups. After
	  *  this call, it is as if the ParameterPort has
	  *  been created but never configured. The values of
	  *  previously defined parameters will, nonethesless,
	  *  remain in the typemap. (They may have been in the
	  *  map before it was used as a parameter port, after all.)
	  *  Typically, this is used only by someone implementing
	  *  the updateParameterPort function from
	   *  class ParameterGetListener.
	  */
	virtual void clearRequests(TypeMap_shared portData) = 0;

	/** 
	 * Register listener (the component) that wishes to have
	 * a chance to change the contents of its ParameterPort
	 * just before the parameters typemap is used to
	 * render the parameter dialog.
	 * @param powner a pointer to the listener that will be
	 * deleted (by boost) when it is no longer needed. 
	 * This pointer will be an opaque wrapper around
	 * some binding specific interface.
	 */
	virtual void registerUpdater(TypeMap_shared portData, 
				ParameterGetListener_shared powner) = 0;

	/** Register listener (the component) if it wishes to be
	 * informed when an parameter is set.
	 * Listeners are called after values are set.
	 * @param powner a pointer to the listener that will be
	 * deleted (by boost) when it is no longer needed. 
	 * This pointer will be an opaque wrapper around
	 * some binding specific interface.
	 */
	virtual void registerUpdatedListener(TypeMap_shared portData,
				ParameterSetListener_shared powner) = 0;

	/** Signal that the ParameterPort is fully defined and should
	 * now pop out on the component. The Services passed here
	 * must be the component's own Services handle.
	 */
	virtual void addParameterPort(TypeMap_shared portData, ccafeopq::Services * svc) = 0;

	/** Cause a previously defined parameter port to go away. */
	virtual void removeParameterPort(TypeMap_shared portData, ccafeopq::Services * svc) = 0;


}; // end virtual interface ParameterPortFactory


 /** This interface is typically implemented by a 
   * component using the ParameterPortFactory dynamically.
  */
class ParameterGetListener {
public:
  virtual ~ParameterGetListener() {}
  
  /** Inform the listener that someone is about to fetch their 
   * typemap (well, a copy thereof). 
   * For old ccaffeine components (SC'01 vintage):
   * The return should be true if the listener
   * has changed the ParameterPort definitions.
   * For new components:
   * The return should always be false.
   *
   * The return value is likely to be ignored, but is specified
   * for compatibility with codes based on old ccaffeine parameter ports.
   */
  virtual bool updateParameterPort(const std::string & portName)=0;
}; // end interface ParameterGetListener


/** This interface is typically implemented by a 
  * component using the ParameterPortFactory in a very dynamic
  * fashion.
  */
class ParameterSetListener {
public:
  virtual ~ParameterSetListener() {}

  /** The component wishing to be told after a parameter is changed
   * implements this function.
   * @param portName the name of the port (typemap) on which the
   * value was set.
   * @param fieldName the name of the value in the typemap.
   */
  virtual void updatedParameterValue(std::string portName, std::string fieldName) = 0;

}; // end interface ParameterSetListener

} ENDSEMI // end namespace ports
} ENDSEMI // end namespace ccafeopq
#endif // opaque_paramPorts_h_seen
