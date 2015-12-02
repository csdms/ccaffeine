#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"

class Bar : public virtual vComponent, public virtual vPort , public virtual sPort {
				public:
				~Bar() {
					std::cout << "Bar::DTOR called" << std::endl;
				}

				vPort *getPort () {
					std::cout << "Bar::getPort called" << std::endl;
					 return this;
 }

				int checkPort (vPort *vp) { 
					std::cout << "Bar::checkPort called" << std::endl;
								sPort *sp = dynamic_cast< sPort * >(vp);
								if (sp == 0) {
												return 0;
								} else {
												std::cout << sp->getCname() << std::endl;
												return 1;
								}
				}

				std::string getCname() {
					std::cout << "Bar::getPort called" << std::endl;
					return "Bar"; 
				}
};

extern "C" {
void *create()
{
	void *cp;
	Bar *f = new Bar();
	cp = (void *)f;
	return cp;
}

};

