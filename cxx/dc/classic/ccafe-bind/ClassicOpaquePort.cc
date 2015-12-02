#include <cca.h>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"

int ClassicOpaquePort::classic_nextNum = 0;

ClassicOpaquePort::~ClassicOpaquePort()
{
  classic_port = 0;
  classic_num = -classic_num;
  IO_dn2("ClassicOpaquePort destroyed %d", classic_num);
}

ClassicOpaquePort::ClassicOpaquePort( ::classic::gov::cca::Port* p)
{
  classic_nextNum++;
  classic_num = classic_nextNum;
  classic_port = p;
  IO_dn2("ClassicOpaquePort created %d", classic_num);
  initClassic();
}

void
ClassicOpaquePort::initClassic()
{
  addSupportedKind(::ccafeopq::CLASSIC_PORT);
}

ClassicOpaquePort::ClassicOpaquePort()
{
  classic_nextNum++;
  classic_num = classic_nextNum;
  classic_port = 0;
  IO_dn2("ClassicOpaquePort created by inheritance %d", classic_num);
}

classic::gov::cca::Port * ClassicOpaquePort::getClassicPort()
{
  return classic_port;
}

