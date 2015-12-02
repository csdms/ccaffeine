#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"

class Bar : public virtual vComponent, public virtual vPort , public virtual sPort {
public:
	virtual ~Bar() {
		std::cout << "Bar::DTOR called" << std::endl;
	}

	virtual vPort *getPort () {
		std::cout << "Bar::getPort called" << std::endl;
		return this;
	}

	virtual int checkPort (vPort *vp) { 
		// vPort * force  = Global_sPort_dummy;
		std::cout << "Bar::checkPort called" << std::endl;
		sPort *sp = dynamic_cast< sPort * >(vp);
		if (sp == 0) {
			std::cout << "Bar::checkPort dynamic cast failed." << std::endl;
			return 0;
		} else {
			std::cout << "getCname: ";
			std::cout << sp->getCname() << std::endl;
			return 1;
		}
	}

	virtual std::string getCname() {
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

}

