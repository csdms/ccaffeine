#ifndef treeparserinternal_hpp_seen
#define treeparserinternal_hpp_seen

#include <boost/smart_ptr.hpp>

#ifndef MDP_DEBUG
// turns on/off spew. 0 = off
#define MDP_DEBUG 0
#endif

#ifndef MDP_ECHO_TEXT
// turns on/off txt sections in display. 0 = off
#define MDP_ECHO_TEXT 0
#endif

namespace ccafe {

class Node;
class XMLNode;

typedef boost::shared_ptr< Node > Node_shared;
typedef boost::shared_ptr< XMLNode > XMLNode_shared;

} // end ccafe namespace

#endif // treeparserinternal_hpp_seen
