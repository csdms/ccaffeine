#include <iostream>
#include "vComponent.hh"
namespace {
	class vPortDummy : public virtual vPort {
		public:
		virtual ~vPortDummy(){
			std::cout << "vPortDummy:DTOR called" << std::endl;
		}
	};

	class vComponentDummy : public virtual vComponent {
		public:
		virtual ~vComponentDummy() {
			std::cout << "vComponentDummy:DTOR called" << std::endl;
		}

		virtual vPort * getPort() {
			std::cout << "vComponentDummy:getPort called" << std::endl;
			return 0; 
		}

		virtual int checkPort( vPort * p) { 
			std::cout << "vComponentDummy:checkPort called" << std::endl;
			return 0;
		}
	};

}

vPortDummy vPortDummy_global_dummy;
