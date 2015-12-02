#include <neocca.hh>
#include <neoports.hh>
#include "dc/export/ccafeopq.hh"
#include "dc/neo/ccafe-bind/NeoComponentClassDescription.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"

NeoComponentClassDescription::NeoComponentClassDescription(std::string className, std::string classAlias)
{
	wrapper = false;
	name = className;
	alias = classAlias;
}

NeoComponentClassDescription::~NeoComponentClassDescription()
{
	name += "_DEAD";
	alias += "_DEAD";
}

#define DO_WRAPPER(x)  \
try { \
	if (wrapper) fwk_desc->x(); \
} \
NEO_RETHROW_PREPEND("NeoComponentClassDescription: ")

::std::string 
NeoComponentClassDescription::getComponentClassName() 
throw (neo::cca::Exception )
{
	DO_WRAPPER(getComponentClassName);
	return name;
}

::std::string 
NeoComponentClassDescription::getDeploymentClassAlias() 
throw (neo::cca::Exception )
{
	DO_WRAPPER(getDeploymentClassAlias);
	return alias;
}

::std::string 
NeoComponentClassDescription::getCCASpecBinding()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getCCASpecBinding);
	return "neo";
}

::std::string 
NeoComponentClassDescription::getIndexFile() 
throw (neo::cca::Exception )
{
	DO_WRAPPER(getIndexFile);
	throw neo::cca::Exception("getIndexFile still unsupported for neo components");
}
::std::string 
NeoComponentClassDescription::getConstructorName()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getConstructorName);
	throw neo::cca::Exception("getConstructorName still unsupported for neo components");
}
::std::string 
NeoComponentClassDescription::getLibraryLoading()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getLibraryLoading);
	throw neo::cca::Exception("getLibraryLoading still unsupported for neo components");
}
::std::string 
NeoComponentClassDescription::getLibraryName()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getLibraryName);
	throw neo::cca::Exception("getLibraryName still unsupported for neo components");
}
::std::string 
NeoComponentClassDescription::getLibraryLocation()
throw (neo::cca::Exception)
{
	DO_WRAPPER(getLibraryLocation);
	throw neo::cca::Exception("getLibraryLocation still unsupported for neo components");
}
::std::string 
NeoComponentClassDescription::getExecScript()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getExecScript);
	throw neo::cca::Exception("getExecScript still unsupported for neo components");
}

void 
NeoComponentClassDescription::getDOMTree()
throw (neo::cca::Exception )
{
	DO_WRAPPER(getDOMTree);
}

NeoComponentClassDescription::NeoComponentClassDescription( ccafeopq::ComponentClassDescription_shared opqDesc)
{
	fwk_desc = opqDesc;
	wrapper = true;
}

bool 
NeoComponentClassDescription::isWrapper()
{
	return wrapper;
}

ccafeopq::ComponentClassDescription_shared
NeoComponentClassDescription::unwrap()
{
	if (!wrapper) {
		throw neo::cca::Exception("NeoComponentClassDescription::unwrap called on non-wrapper.");
	}
	return fwk_desc;
}


NeoComponentClassDescription_shared 
NeoComponentClassDescription::wrapOpaque( ccafeopq::ComponentClassDescription_shared opqDesc)
{
	NeoComponentClassDescription *nccd = new NeoComponentClassDescription( opqDesc);
	NeoComponentClassDescription_shared nccds(nccd);
	return nccds;
}
