#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <boost/smart_ptr.hpp>
#include <libxml/SAX.h>    // libxml2 header, usually in /usr/include/libxml2

#include "dc/services/dotcca/treeReader/treeParser_internal.hpp"
#include "dc/services/dotcca/treeReader/XMLNode.hpp"
#include "dc/services/dotcca/treeReader/Node.hpp"
#include "dc/services/dotcca/treeReader/MetaDataParser.hpp"
#include "dc/services/dotcca/treeReader/Parser.hpp"

ccafe::Parser::Parser()
{
	p = new ccafe::MetaDataParser();
}

ccafe::Parser::~Parser()
{
	delete p;
	p = 0;
}

void
ccafe::Parser::parse(const std::string & file)
{
	p->parse(file);
}

void 
ccafe::Parser::displayAll()
{
	p->displayAll();
}

std::vector< ccafe::XMLNode_shared > 
ccafe::Parser::findNodes(const std::string & tag)
{
	return p->findNodes( tag );
}
