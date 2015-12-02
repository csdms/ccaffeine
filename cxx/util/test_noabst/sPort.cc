#if USEPRAG
#pragma implementation
#endif
#include "vComponent.hh"
#include <string>
#include "sPort.hh"

#if USEPV
// then build a dummy stub class

#include <iostream>
namespace {
	class sPortDummy : public virtual sPort {
	public:
	sPortDummy() { 
		std::cout <<"sPortDummy CTOR called" << std::endl;

	}
	virtual ~sPortDummy() {
		std::cout <<"sPortDummy DTOR called" << std::endl;
	}

	virtual std::string getCname() { 
		return "sPortDummy";
	}
};

}

// the following is required, or no symbols emitted in .so
// the following cannot be static.
sPortDummy sPortDummy_global_dummy;

#if 0
sPort *Global_sPort_dummy = 0;
#endif

#else
// build the functions for the nonabstract base
sPort::~sPort() { std::cout <<"sPort destructor" << std::endl; }

std::string sPort::getCname() {
	std::cout <<"sPort::getCname called" << std::endl;
	exit(1);
}
#endif
