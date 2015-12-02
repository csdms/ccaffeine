#include <iostream>
#include "vComponent.hh"
#include "sPort.hh"

class Bar : public virtual vComponent, public virtual vPort , public virtual sPort {
				public:
				virtual ~Bar() {}

				vPort *getPort () { return this; }

				int checkPort (vPort *vp) { 
								sPort *sp = dynamic_cast< sPort * >(vp);
								if (sp == 0) {
												return 0;
								} else {
												std::cout << sp->getCname() << std::endl;
												return 1;
								}
				}

				std::string getCname() { return "Bar"; }
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

