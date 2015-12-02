#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"
#include <string>
namespace {
	class sPortDummy : public virtual sPort {
		public:
		sPortDummy() { 
			std::cout <<"sPortDummy constructor called by loader" << std::endl;}
		~sPortDummy() {
			std::cout <<"sPortDummy destructor called by loader" << std::endl;}
		std::string getCname() { return "sPortDummy"; }
	};
}

// the following is required, or no symbols emitted in .so
// the following cannot be static.
sPortDummy sPortDummy_global_dummy;
