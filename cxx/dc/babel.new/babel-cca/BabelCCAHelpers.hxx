#ifndef BabelCCAHelpers_hxx_seen
#define BabelCCAHelpers_hxx_seen
namespace ccafe {

/** misc utilities
possibly of general reuse in several impl files.
The function bodies are in the misc section of
ccaffeine_Services.
*/

class BabelCCAHelpers
{

private:

public:

  BabelCCAHelpers() {}
  ~BabelCCAHelpers() {}

  /** generate exception if member is null.
  @param className fully qualified class.
  @param funcName member function calling checkthrow.
  @param memberName name of pointer.
  @param member pointer to check for being null.
  */
  static void checkthrow(const char * className, const char * memberName, void * member, const char *funcName);

  static ::gov::cca::Port convert( ::ccafeopq::Port *);

  /** generate an opaque wrapper on a babel port.
   * handles all special cases like goport.
   */
  static ccafeopq::Port *createSpecialProvider(::gov::cca::Port inPort,
		  const std::string & name, const ::std::string& type,
		  ccafeopq::TypeMap_shared portProperties, ::std::string & supportedType);

} ; // end class BabelCCAHelpers
} ENDSEMI // end namespace ccafe

#endif // BabelCCAHelpers_hxx_seen
