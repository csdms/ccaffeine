#include <neocca.hh>
#include <neoports.hh>
#include "dc/export/AllExport.hh"

#include "ccafeTypeMap.hh"
#include "NeoHelper.hh"
#include "NeoMacros.hh"
#include "NeoOpaquePort.hh"
#include "NeoPortConverter.hh"
#include "NeoOpaqueGoPort.hh"
#include "NeoServices.hh"
#include "NeoServicesHelper.hh"
#include "NeoComponentWrapper.hh"
#include "NeoOpaqueTypeMap.hh"
#include "NeoOpaqueParameterGetListener.hh"
#include "NeoOpaqueParameterSetListener.hh"

#include "NeoParameterPortFactoryPC.hh"
#include "NeoParameterPortFactoryWrap.hh"
#include "NeoBasicParameterPortPC.hh"
#include "NeoBasicParameterPortWrap.hh"
#include "NeoBuilderServicePC.hh"
#include "NeoBuilderServiceWrap.hh"
#include "NeoComponentID.hh"
#include "NeoConnectionID.hh"
#include "NeoParameterPortPC.hh"
#include "NeoParameterPortWrap.hh"


/** all this driver does is test for instantiability,
 * meaning that all the functions headered or inherited
 * are actually implemented or stubbed at least.
 *
 * It does not (duh) automagically add classes.
 */
int main()
{

	ccafe::TypeMap TypeMap_dummy(1);
	NeoBasicParameterPortPC NeoBasicParameterPortPC_dummy(1);
	NeoBasicParameterPortWrap NeoBasicParameterPortWrap_dummy(1);
	NeoBuilderServicePC NeoBuilderServicePC_dummy(1);
	NeoBuilderServiceWrap NeoBuilderServiceWrap_dummy(1);
	NeoComponentID NeoComponentID_dummy(1);
	NeoComponentWrapper NeoComponentWrapper_dummy(1);
	NeoConnectionID NeoConnectionID_dummy(1);
	
	// no object in this helper.
	// NeoHelper NeoHelper_dummy(1);
	
	NeoOpaqueGoPort NeoOpaqueGoPort_dummy(1);
	NeoOpaqueParameterGetListener NeoOpaqueParameterGetListener_dummy(1);
	NeoOpaqueParameterSetListener NeoOpaqueParameterSetListener_dummy(1);
	NeoOpaquePort NeoOpaquePort_dummy(1);
	NeoOpaqueTypeMap NeoOpaqueTypeMap_dummy(1);
	NeoParameterPortPC NeoParameterPortPC_dummy(1);
	NeoParameterPortWrap NeoParameterPortWrap_dummy(1);
	NeoParameterPortFactoryPC NeoParameterPortFactoryPC_dummy(1);
	NeoParameterPortFactoryWrap NeoParameterPortFactoryWrap_dummy(1);

	// just an interface. no class.
	// NeoPortConverter NeoPortConverter_dummy(1);

	NeoServicesHelper NeoServicesHelper_dummy(1);
	NeoServices NeoServices_dummy(1);

return 0;
}
