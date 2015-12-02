
#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"

class Foo : public virtual vComponent, public virtual vPort , public virtual sPort {
public:
	virtual ~Foo() {
		std::cout << "Foo::DTOR called" << std::endl;
	}

	virtual vPort *getPort () {
		std::cout << "Foo::getPort called" << std::endl;
		return this; 
	}

	virtual int checkPort (vPort *vp) { 
		std::cout << "Foo::checkPort called" << std::endl;
		sPort *sp = dynamic_cast< sPort * >(vp);
		if (sp == 0) {
			std::cout << "Bar::checkPort dynamic cast failed." << std::endl;
			return 0;
		} else {
			std::cout << sp->getCname() << std::endl;
			return 1;
		}
	}

	virtual std::string getCname() { 
		std::cout << "Foo::checkPort called" << std::endl;
		return "Foo"; 
	}
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
