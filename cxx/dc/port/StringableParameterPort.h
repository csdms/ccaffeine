#ifndef StringableParameterPort_h_seen
#define StringableParameterPort_h_seen

/**
 * This interface is a tag (And big convenience) such that we
 * can differentiate between us and some other port implementation.
 */
class StringableParameterPort 
{
public:
	virtual ~StringableParameterPort() {}
	virtual std::string getConfigurationString( const std::string & prefix) = 0;
	virtual std::string getConfigurationString( const std::string & prefix, const std::string & key) = 0;
        /** return 0 if ok, <0  if not. */
	virtual int setConfigurationString( const std::string & key, const std::string & value) = 0;

}; // end interface StringableParameterPort

#endif // StringableParameterPort_h_seen
