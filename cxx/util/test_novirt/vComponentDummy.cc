#include <iostream>
#include "vComponent.hh"
namespace {
	class vPortDummy : public virtual vPort {
		public:
		~vPortDummy(){
					std::cout << "vPortDummy:DTOR called" << std::endl;
		}
	};

	class vComponentDummy : public virtual vComponent {
		public:
		~vComponentDummy() {
					std::cout << "vComponentDummy:DTOR called" << std::endl;
	}

		vPort * getPort() {
					std::cout << "vComponentDummy:getPort called" << std::endl;
	 return 0; }

		int checkPort( vPort * p) { 
					std::cout << "vComponentDummy:checkPort called" << std::endl;
			return 0; }
	};

}

vPortDummy vPortDummy_global_dummy;
