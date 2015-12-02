#ifndef __MetaDataParser_hpp
#define __MetaDataParser_hpp

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <libxml/SAX.h>    // libxml2 header, usually in /usr/include/libxml2
#if LIBXML_VERSION >= 20600
#define INITHANDLER xmlSAX2InitDefaultSAXHandler
#define CCAFE_SAX2 1
#else
#define CCAFE_SAX2 0
#define INITHANDLER initxmlDefaultSAXHandler
#endif // vers
#include <boost/smart_ptr.hpp>
#include <complex>
#include <dc/export/ccafeopq.hh>

namespace ccafe {

/** This is a sax parser that builds a c++ dumb tree
 * rather than a java DOM tree.
 */
class MetaDataParser {
public:
  MetaDataParser();
  ~MetaDataParser();

  void parse(const std::string & file);
  void displayAll();

  std::vector< XMLNode_shared > findNodes(const std::string & tag);

private:
  void initialize();
  Node_shared rootNode; // a null node pointer.
  Node_shared current; // active element node
  std::string fname;


  xmlSAXHandler handler;


  // SAX function callbacks
  static void startElement    (void *ctx, const xmlChar *name, const xmlChar **atts);
  static void endElement      (void *ctx, const xmlChar *name);

  // assign chars to current node.
  static void characters      (void *ctx, const xmlChar *ch, int len);

  // print comment 
  static void comment         (void *ctx, const xmlChar *val);

  // just print msg.
  static void warning	      (void *ctx, const char *msg, ...);

  // do nothing
  static void cdataBlock      (void *ctx, const xmlChar *value, int len);

  // do relatively nothing . could change to handle multiple files.
  static void startDocument     (void *ctx);
  static void endDocument     (void *ctx);

  static std::string xmlChar2String(const xmlChar *value);
  static std::string xmlChar2String(const xmlChar *value, int len);

  void displayNode(Node_shared & n, int depth, int tabwidth);

  void searchNode(Node_shared & r, const std::string & tag, std::vector< XMLNode_shared > & results);
}; // end class metadataparser

} // end namespace ccafe

#endif // __MetaDataParser_hpp
