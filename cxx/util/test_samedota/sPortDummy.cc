#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"
#include <string>
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
