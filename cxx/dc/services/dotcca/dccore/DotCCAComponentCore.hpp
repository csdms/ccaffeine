#ifndef DotCCAComponentCore_hpp
#define DotCCAComponentCore_hpp

#include <vector>
#include <stdexcept>

/* compilation of this class depends on the preprocessor variable
 * _NO_XML
 * If _NO_XML is defined (-D_NO_XML) then all xml related calls
 * throw exceptions, no xml library need be linked,
 * and only old ccaffeine .cca behavior functions.
 */
namespace ccafe {

/**
 * This class is essentially a factory of ::ccafeopq::ComponentClassDescription.
 * Give it a .cca filename and it gives you the component descriptions 
 * obtainable therefrom. The formats currently supported start with
 * #!ccaffeine or <xml>
 * This class anticipates that it will be wrapped for
 * some other binding consumption, so what it returns are boost pointers
 * and it does not use external cca connections of any kind.
 */
class DotCCAComponentCore 
{

private:
	/** true if file given opens and has # or !.
	 * Note this is not a lot of reassurance, but
	 * at least we know it's not xml. 
	 */ 
	bool isOldFormat(const std::string & filename);
	/** true if file given opens and has <xml */
	bool isXMLCCAFormat(const std::string & filename);
	/** true if file appears to be sidl. */
	bool isSIDLFile(const std::string & filename);

	/** extract descriptions and append to vector. 
	 * @return 0 if ok. */
	int extractOldDescriptions( const std::string & filename, std::vector< ::ccafeopq::ComponentClassDescription_shared > & ccdv);

	/** extract xml descriptions and append to vector. 
	 * @return 0 if ok. */
	int extractXMLDescriptions(  const std::string & filename, std::vector< ::ccafeopq::ComponentClassDescription_shared > & ccdv);

	/** parse a file and return a vector of the ComponentClassDescription
	 * extracted. The empty list is a possible return.
	 * In the event of file operation/parse failure, an exception
	 * may be thrown. Extracts data if xml is babel 1.1 schema.
	 * Will throw an exception if xml support is not compiled in.
	 */
	std::vector< ::ccafeopq::ComponentClassDescription_shared > parseSIDL( const std::string & filename) throw ( std::invalid_argument);

public:
	DotCCAComponentCore();
	~DotCCAComponentCore();

	/** parse a file and return a vector of the ComponentClassDescription
	 * extracted. The empty list is a possible return.
	 * In the event of file operation/parse failure, an exception
	 * may be thrown. handles old .cca and new xml .cca.
	 * Will throw an exception if xml format is given but xml support
	 * is not compiled in.
	 */
	std::vector< ::ccafeopq::ComponentClassDescription_shared > parseDescriptions( const std::string & filename) throw ( std::invalid_argument);

	::ccafeopq::ComponentClassDescription_shared createStaticDescription(
		const ::std::string specBinding,
		const ::std::string componentClassName, 
		const ::std::string deploymentClassAlias);

//===================================================================

	/** test function.  given a filename, calls parse and prints results. */
	int main(int argc, char *argv[]);

}; // end DotCCAComponentCore

} // end namespace ccafe
#endif // DotCCAComponentCore_hpp
