#ifndef __NeoServiceRegistryPC_hh__
#define __NeoServiceRegistryPC_hh__


class NeoServiceRegistryPC : public virtual NeoPortConverter_Interface
{
private:
	ccafeopq::ComponentID_shared cid;

public:
	NeoServiceRegistryPC(ccafeopq::ComponentID_shared c);
	NeoServiceRegistryPC(int bogon) {}
	virtual ~NeoServiceRegistryPC() ;

	virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

#endif // __NeoServiceRegistryPC_hh__
