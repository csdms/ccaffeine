#include <neocca.hh>
#include <neoports.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueParameterGetListener.hh"

NeoOpaqueParameterGetListener::NeoOpaqueParameterGetListener( ::neo::cca::ports::ParameterGetListener * npgl)
{
	pgl = npgl;
}

NeoOpaqueParameterGetListener::~NeoOpaqueParameterGetListener()
{
	pgl = 0;
}

bool
NeoOpaqueParameterGetListener::updateParameterPort(const std::string & portName)
{
	pgl->updateParameterPort(portName);
	return false;
}
