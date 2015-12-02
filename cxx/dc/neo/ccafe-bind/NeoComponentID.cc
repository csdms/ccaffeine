#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include "dc/neo/ccafe-bind/NeoComponentID.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"

NeoComponentID::NeoComponentID( ccafeopq::ComponentID_shared cid_) 
{
	cid = cid_;
}

::std::string NeoComponentID::getInstanceName() throw ( neo::cca::Exception ) 
{
	std::string result;
	try {
		result = cid->getInstanceName();
	}
	NEO_RETHROW_PREPEND("NeoComponentID::getInstanceName: ");

	return result;
}

::std::string NeoComponentID::getSerialization() throw ( neo::cca::Exception ) 
{
	std::string result;
	try {
		result = cid->getSerialization();
	}
	NEO_RETHROW_PREPEND("NeoComponentID::getInstanceName: ");

	return result;
}

bool NeoComponentID::isSameAs( ::neo::cca::ComponentID_shared cid_)
{
	// convert arg to our type, if possible.
	NeoComponentID_shared ncid = boost::shared_dynamic_cast< NeoComponentID >(cid_);
	if ( ncid == 0) { return false; }
	// extract opaque cid shared ptr from arg.
	ccafeopq::ComponentID_shared ocid = ncid->cid;
	// compare our opaque cid with the extracted opaque one canonically.
	return cid->isSameAs(ocid);
}

NeoComponentID_shared 
NeoComponentID::neoWrap( ccafeopq::ComponentID_shared cid_) 
{
	NeoComponentID *ccid = 0;
	ccid = new NeoComponentID(cid_);
	NeoComponentID_shared ccid_s(ccid);
	return ccid_s;
}

::std::vector< neo::cca::ComponentID_shared >
NeoComponentID::convertToVector( std::vector< ::ccafeopq::ComponentID_shared > & cids)
{
	::std::vector< neo::cca::ComponentID_shared > res;
	for (size_t i = 0; i < cids.size(); i++) 
	{
		NeoComponentID_shared nid = neoWrap( cids[i]);
		res.push_back(nid);
	}
	return res;
}

NeoComponentID NeoComponentID_test(1);
