#ifndef __ccafeXMLParser_hpp
#define __ccafeXMLParser_hpp

#include <string>
#include <vector>
#include <boost/smart_ptr.hpp>

namespace ccafe {

class MetaDataParser;

/** This is a sax parser wrapper that keeps
 * all the implementation headers invisible
 * to the outside clients.
 */
class Parser {
public:
  Parser();
  ~Parser();

  /** load up a tree attached to this parser instance
   * using a file.
   */
  void parse(const std::string & file);
  void displayAll();

  std::vector< XMLNode_shared > findNodes(const std::string & tag);

private:
  MetaDataParser *p;

}; // end parser

} // end namespace ccafe

#endif // __ccafeXMLParser_hpp
