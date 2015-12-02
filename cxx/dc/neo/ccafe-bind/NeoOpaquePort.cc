#include <neocca.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"

int NeoOpaquePort::neo_nextNum = 0;

NeoOpaquePort::~NeoOpaquePort()
{
	neo_port = 0;
	neo_num = -neo_num;
	IO_dn2("NeoOpaquePort destroyed %d", neo_num);
}

void
NeoOpaquePort::initNeo()
{
	addSupportedKind(ccafeopq::NEO_PORT);
}

NeoOpaquePort::NeoOpaquePort(neo::cca::Port* p)
{
	neo_nextNum++;
	neo_num = neo_nextNum;
	neo_port = p;
	IO_dn2("NeoOpaquePort created %d", neo_num);
	initNeo();
}

NeoOpaquePort::NeoOpaquePort()
{
	neo_nextNum++;
	neo_num = neo_nextNum;
	neo_port = 0;
	IO_dn2("NeoOpaquePort created by inheritance %d", neo_num);
}

neo::cca::Port * NeoOpaquePort::getNeoPort()
{
	return neo_port;
}

