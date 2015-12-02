#ifndef treeReaderPublic_h_seen
#define treeReaderPublic_h_seen

#include <string>
#include <vector>
#include <boost/smart_ptr.hpp>

namespace ccafe {

class XMLNode;
typedef boost::shared_ptr< XMLNode > XMLNode_shared;

} // end ccafe namespace

#include "dc/services/dotcca/treeReader/XMLNode.hpp"
#include "dc/services/dotcca/treeReader/Parser.hpp"

#endif // treeReaderPublic_h_seen
