#ifndef __ccafeXmlNode_hpp
#define __ccafeXmlNode_hpp

#include <string>
#include <vector>

namespace ccafe {

class XMLNode {
public:
	virtual ~XMLNode() {}

	virtual XMLNode_shared getParent() = 0;
	virtual std::vector< XMLNode_shared > getChildren() = 0;

	virtual std::string getName() = 0;
	virtual std::string getText() = 0;
	virtual const std::vector< std::string > & getAttrList() = 0;

        virtual std::vector< XMLNode_shared > matchChildren( std::string tag) = 0;
	
	virtual std::string getAttribute(const std::string & attrName, const std::string & attrDefault) = 0;

}; // end class XMLNode

} // end namespace ccafe

#endif // __ccafeXmlNode_hpp
