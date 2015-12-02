#ifndef OpqParameterPortFactory_h_seen
#define OpqParameterPortFactory_h_seen

/*
 * This port/component implementation could be exposed
 * as a component (one per using client component).
 * Once the factory situation is settled down, this
 * can be ported easily to be a new service component
 * that lives alone and gets dynamically loaded.
 * ----
 * This class supercedes the old ccaffeine ConfigurableParameterPortFactory
 * the parameters library, and all the associated cruft that
 * gunked up a component. The component writer now just needs to
 * use this port and one or more typemaps.
 *
 * Each dialog is defined on a typemap the component owns.
 * A component writer can define more than one dialog for a component,
 * and each dialog will show up as a configuration port in the
 * usual ccaffeine parameter port sense.
 * The component writer can choose to be notified of 
 * changes to the published parameters and requests for
 * the typemap.
 * ------
 *
 */
class OpqParameterPortFactory :
	public virtual ::ccafeopq::ports::ParameterPortFactory,
#ifdef HAVE_CLASSIC
	public virtual ClassicOpaquePort,
#endif // HAVE_CLASSIC
	public virtual KernelPort
#ifdef HAVE_CLASSIC
	,
	public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

private:
	/** This is the map of port names to Parameter
	 * port delegate implementations. noone needs to know
	 * that, however.
	 */
	std::map< std::string, void * > delegates;	

public:
	OpqParameterPortFactory();

	// never use this constructor. testing only.
	OpqParameterPortFactory(int bogon);

	virtual ~OpqParameterPortFactory();

#ifdef HAVE_CLASSIC
	virtual classic::gov::cca::Port * getClassicPort();
#endif

	/** Initialize the portData for use as a parameter dialog port
	 *  with name portName.
	 *  More than one such port can be defined. Each must
	 *  be published before the next can be created.
	 *  The given string portName will appear in the  ::ccafeopq::TypeMap_shared
	 *  as the result of this function and must not be changed
	 *  by the component henceforth. 
	 *  @param portData the typemap associated with the port;
	 *       It is shared between the ParameterPortFactory
	 *       and the component. The ParameterPortFacotry will
	 *       not read or change values in portData except those
	 *       requested via the addRequest functions.
	 *  @param portName The name of a ParameterPort to appear in
	 *       user interface one way or another.
	 *  
	 **/
	virtual void createParameterPort( ::ccafeopq::TypeMap_shared portData, const ::std::string & portName);

	/** Define the window title for the parameter dialog.
	 **/
	virtual void setBatchTitle( ::ccafeopq::TypeMap_shared portData, const ::std::string & title);
	
	/** Define the next tab/group title to use. All
	 * addRequest subsequent calls will add to this group.
	 * Multiple dialog tabs/groups can be defined in this way.
	 */
	virtual void setGroupName( ::ccafeopq::TypeMap_shared portData, const std::string & newGroupName);

	/** Define a boolean parameter and its default state.
	 * The configured value is always available by
	 * portData->getBool(name, ...);
	 */
	virtual void addRequestBoolean( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					bool deflt);

	/** Define a int parameter and its default state.
	 * The configured value is always available by
	 * portData->getInt(name, ...) and it will be
	 * in the range [low, high].
	 */
	virtual void addRequestInt( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					int deflt,
					int low,
					int high);

	/** Define a long parameter and its default state.
	 * The configured value is always available by
	 * portData->getLong(name, ...) and it will be
	 * in the range [low, high].
	 */
	virtual void addRequestLong( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					int64_t deflt,
					int64_t low,
					int64_t high);

	/** Define a float parameter and its default state.
	 * The configured value is always available by
	 * portData->getFloat(name, ...) and it will be
	 * in the range [low, high].
	 */
	virtual void addRequestFloat( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					float deflt,
					float low,
					float high);

	/** Define a double parameter and its default state.
	 * The configured value is always available by
	 * portData->getDouble(name, ...) and it will be
	 * in the range [low, high].
	 */
	virtual void addRequestDouble( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					double deflt,
					double low,
					double high);

	/** Define a string parameter and its default state.
	 * The configured value is always available by
	 * portData->getString(name, ...).
	 * If no addRequestStringChoice calls are made, the
	 * user input may be any string. If addRequestStringChoice
	 * is used, the value will be one among the choices.
	 * If addRequestStringChoice is used, deflt must
	 * be among the choices defined.
	 */
	virtual void addRequestString( ::ccafeopq::TypeMap_shared portData,
					const std::string & name, 
					const std::string & help,
					const std::string & prompt,
					const std::string & deflt);
	/** define a new choice for a string parameter. */
	virtual void addRequestStringChoice( ::ccafeopq::TypeMap_shared portData,
			const std::string & name, const std::string &choice);

	 /** Clear all previously added requests, titles, groups. After
	  *  this call, it is as if the ParameterPort has
	  *  been created but never configured. The values of
	  *  previously defined parameters will, nonethesless,
	  *  remain in the typemap.
	  *  Typically, this is used only by someone implementing
	  *  the updateParameterPort function from
	   *  class ::ccafeopq::ports::ParameterGetListener {
	  */
	virtual void clearRequests( ::ccafeopq::TypeMap_shared portData);

	/** 
	 * Register listener (the component) that wishes to have
	 * a chance to change the contents of its ParameterPort
	 * just before the parameters typemap is used to
	 * render the parameter dialog.
	 * @param powner a pointer to the listener that will be
	 * forgotten when it is no longer needed. 
	 */
	virtual void setUpdater( ::ccafeopq::TypeMap_shared portData, 
				::ccafeopq::ports::ParameterGetListener_shared powner);

	/** Register listener (the component) if it wishes to be
	 * informed when an parameter is set.
	 * Listeners are called after values are set.
	 */
	virtual void setUpdatedListener( ::ccafeopq::TypeMap_shared portData,
				::ccafeopq::ports::ParameterSetListener_shared powner);

	/** Signal that the ParameterPort is fully defined and should
	 * now pop out on the component. The  ::ccafeopq::Services passed here
	 * must be the component's own  ::ccafeopq::Services handle.
	 */
	virtual void publishParameterPort( ::ccafeopq::TypeMap_shared portData,
		      			::ccafeopq::Services * svc);

	/** Cause a previously defined parameter port to go away. */
	virtual void unpublishParameterPort( ::ccafeopq::TypeMap_shared portData,
		      				::ccafeopq::Services * svc);

	virtual void setGroupNameAndTitle(ccafeopq::TypeMap_shared,
		const std::string& groupName, const std::string& title);

	virtual void registerUpdater(ccafeopq::TypeMap_shared tm, ccafeopq::ports::ParameterGetListener_shared pgl);
	virtual void registerUpdatedListener(ccafeopq::TypeMap_shared tm, ccafeopq::ports::ParameterSetListener_shared psl);
	virtual void addParameterPort(ccafeopq::TypeMap_shared tm, ccafeopq::Services* svc);
	virtual void removeParameterPort(ccafeopq::TypeMap_shared tm, ccafeopq::Services* svc);

        /** define more choices for a string parameter. */
        virtual void addStringChoices(ccafeopq::TypeMap_shared portData,
                                        const std::string & key,
                                        std::vector< std::string > choices);
 
        /** define more choices for a int32 parameter. */
        virtual void addIntChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< int32_t > choices);
 
        /** define more choices for a int32 parameter, raw.
         * nChoices is number of int elements in choices, not memory size. */
        virtual void addIntChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                int32_t choices[], size_t nChoices);
 
        /** define more choices for a int64 parameter. */
        virtual void addLongChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< int64_t > choices);
 
        /** define more choices for a int64 parameter, raw.
         * nChoices is number of long elements in choices, not memory size. */
        virtual void addLongChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                int64_t choices[], size_t nChoices);
 
        /** define more choices for a parameter. */
        virtual void addFloatChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< float > choices);
 
        /** define more choices for a parameter, raw.
         * nChoices is number of long elements in choices, not memory size. */
        virtual void addFloatChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                float choices[], size_t nChoices);
 
        /** define more choices for a parameter. */
        virtual void addDoubleChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< double > choices);
 
        /** define more choices for a parameter, raw.
         * nChoices is number of long elements in choices, not memory size. */
        virtual void addDoubleChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                double choices[], size_t nChoices);
 
        /** define more choices for a parameter. */
        virtual void addFcomplexChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< std::complex< float > > choices);
 
        /** define more choices for a parameter, raw.
         * nChoices is number of long elements in choices, not memory size. */
        virtual void addFcomplexChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::complex< float > choices[], size_t nChoices);
 
        /** define more choices for a parameter. */
        virtual void addDcomplexChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::vector< std::complex< double > > choices);
 
        /** define more choices for a parameter, raw.
         * nChoices is number of long elements in choices, not memory size. */
        virtual void addDcomplexChoices(ccafeopq::TypeMap_shared portData,
                const std::string & key,
                std::complex< double > choices[], size_t nChoices);


}; // end interface OpqParameterPortFactory

extern OpqParameterPortFactory OpqParameterPortFactory_test;

#endif // OpqParameterPortFactory_h_seen
