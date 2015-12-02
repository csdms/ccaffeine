#include <neocca.hh>
#include <neoports.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueParameterSetListener.hh"

NeoOpaqueParameterSetListener::NeoOpaqueParameterSetListener( ::neo::cca::ports::ParameterSetListener * npsl)
{
	psl = npsl;
}

NeoOpaqueParameterSetListener::~NeoOpaqueParameterSetListener()
{
	psl = 0;
}

void 
NeoOpaqueParameterSetListener::updatedParameterValue(std::string portName, std::string fieldName)
{
	psl->updatedParameterValue(portName, fieldName);
}
