#include "vComponent.hh"
#include <string>

#if USEPRAG
#pragma interface
#endif

//#define USEPV 1 comes from command line or not.
// if defined, this class is virtual but not abstract
// note under gcc 3.1, results vary from those under 3.2
// at link time, although with the smae linkers.

class sPort : public virtual vPort {
	public:

	virtual ~sPort()
#if USEPV
	{}
#else
	;
#endif

	virtual std::string getCname()
#if USEPV
	= 0;
#else
	;
#endif

};

#if 0
extern sPort * Global_sPort_dummy;
#endif
