
#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"

class Foo : public virtual vComponent, public virtual vPort , public virtual sPort {
				public:
				~Foo() {
					std::cout << "Foo::DTOR called" << std::endl;
		}

				vPort *getPort () {
					std::cout << "Foo::getPort called" << std::endl;
		 return this; }

				int checkPort (vPort *vp) { 
					std::cout << "Foo::checkPort called" << std::endl;
								sPort *sp = dynamic_cast< sPort * >(vp);
								if (sp == 0) {
												return 0;
								} else {
												std::cout << sp->getCname() << std::endl;
												return 1;
								}
				}

				std::string getCname() { 
					std::cout << "Foo::checkPort called" << std::endl;
		return "Foo"; }
};

extern "C" {
void *create()
{
				void *cp;
				Foo *f = new Foo();
				cp = (void *)f;
				return cp;
}

};
