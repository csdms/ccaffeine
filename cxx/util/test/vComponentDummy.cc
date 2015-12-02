#include "vComponent.hh"
namespace {
	class vPortDummy : public virtual vPort {
		public:
		virtual ~vPortDummy(){}
	};

	class vComponentDummy : public virtual vComponent {
		public:
		virtual ~vComponentDummy() {}
		virtual vPort * getPort() { return 0; }
		virtual int checkPort( vPort * p) { return 0; }
	};

}

vPortDummy vPortDummy_global_dummy;
