#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include "dc/neo/ccafe-bind/NeoConnectionID.hh"
#include "dc/neo/ccafe-bind/NeoComponentID.hh"

#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"

NeoConnectionID::NeoConnectionID( int bogon )
{
}

NeoConnectionID::NeoConnectionID( ccafeopq::ConnectionID_shared cid_) 
{
	cid = cid_;
}

#if 0
bool NeoConnectionID::isSameAs( ::neo::cca::ConnectionID_shared cid_)
{
	// convert arg to our type, if possible.
	NeoConnectionID_shared ncid = boost::shared_dynamic_cast< NeoConnectionID >(cid_);
	// NeoConnectionID::isSameAs FIXME result check the cast.
	// extract opaque cid shared ptr from arg.
	ccafeopq::ConnectionID_shared ocid = ncid->cid;
	// compare our opaque cid with the extracted opaque one canonically.
	return cid->isSameAs(ocid);
}
#endif

NeoConnectionID_shared 
NeoConnectionID::neoWrap( ccafeopq::ConnectionID_shared cid_) 
{
	NeoConnectionID *ccid = 0;
	ccid = new NeoConnectionID(cid_);
	NeoConnectionID_shared ccid_s(ccid);
	return ccid_s;
}

::std::vector< neo::cca::ConnectionID_shared >
NeoConnectionID::convertToVector( std::vector< ::ccafeopq::ConnectionID_shared > & cids)
{
	::std::vector< neo::cca::ConnectionID_shared > res;
	for (size_t i = 0; i < cids.size(); i++) 
	{
		NeoConnectionID_shared nid = neoWrap( cids[i]);
		res.push_back(nid);
	}
	return res;
}

neo::cca::ComponentID_shared 
NeoConnectionID::getProvider() 
throw (neo::cca::Exception )
{
	if (!cid) {
		neo::cca::Exception ex("NeoConnectionID::getProvider() cid uninitialized");
		IO_dn1("NeoConnectionID::getProvider(): cid uninitialized.");
		throw ex;
	}
	::ccafeopq::ComponentID_shared oid;

	try {
		oid = cid->getProvider();
	}
	NEO_RETHROW_PREPEND("NeoConnectionID::getProvider: ");

	neo::cca::ComponentID_shared pcid = NeoComponentID::neoWrap(oid);
	return pcid;
}

neo::cca::ComponentID_shared 
NeoConnectionID::getUser() 
throw (neo::cca::Exception )
{
	if (!cid) {
		neo::cca::Exception ex("NeoConnectionID::getUser() cid uninitialized");
		IO_dn1("NeoConnectionID::getUser(): cid uninitialized.");
		throw ex;
	}
	::ccafeopq::ComponentID_shared oid;
	try {
		oid = cid->getUser();
	}
	NEO_RETHROW_PREPEND("NeoConnectionID::getUser: ");

	neo::cca::ComponentID_shared ucid = NeoComponentID::neoWrap(oid);
	return ucid;
}

std::string 
NeoConnectionID::getProviderPortName() 
throw (neo::cca::Exception )
{
	if (!cid) {
		neo::cca::Exception ex("NeoConnectionID::getProviderPortName() cid uninitialized");
		IO_dn1("NeoConnectionID::getProviderPortName(): cid uninitialized.");
		throw ex;
	}
	std::string result;
	try {
	       result =	cid->getProviderPortName();
	}
	NEO_RETHROW_PREPEND("NeoConnectionID::getProviderPortName: ");

	return result;
}

std::string 
NeoConnectionID::getUserPortName() 
throw (neo::cca::Exception )
{
	if (!cid) {
		neo::cca::Exception ex("NeoConnectionID::getUserPortName() cid uninitialized");
		IO_dn1("NeoConnectionID::getUserPortName(): cid uninitialized.");
		throw ex;
	}
	std::string result;
	try {
		result = cid->getUserPortName();
	}
	NEO_RETHROW_PREPEND("NeoConnectionID::getUserPortName: ");

	return result;

}

// test instance for completeness
NeoConnectionID NeoConnectionID_test(1);
