#include <iostream>
#include "dc/services/dotcca/treeReader/treeParser_internal.hpp"
#include <libxml/SAX.h>
#include "dc/services/dotcca/treeReader/XMLNode.hpp"
#include "dc/services/dotcca/treeReader/Node.hpp"

ccafe::Node::Node() {
  name="";
  txt="";
}

ccafe::Node::~Node() {
#if MDP_DEBUG
	std::cout << "destroying node: " << name << std::endl;
#endif
	name = "dead-node";
}


void 
ccafe::Node::appendAttrList(const xmlChar **atts) {
  int i = 0;
  if (atts != NULL) {
    while (atts[i] != NULL) {
      std::string s = reinterpret_cast<const char*>(atts[i]);
      attrlist.push_back(s);
      i++;
    }
  }
}

std::string
ccafe::Node::getAttribute(const std::string & attrName, const std::string & attrDefault)
{
	size_t i = 0;
	for ( ; i < attrlist.size(); i += 2) {
		if (attrlist[i] == attrName) {
			return attrlist[i+1];
		}
	}
	return attrDefault;
}

std::vector< ccafe::XMLNode_shared > 
ccafe::Node::matchChildren( std::string  tag)
{
	std::vector< XMLNode_shared > result;
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i]->name == tag)
		{
			result.push_back(children[i]);
		}
	}
	return result;
}

int ccafe::Node::main(int argc, char *argv[])
{
	Node n;
	return 0;
}

