#ifndef __NeoLoaderPC_hh__
#define __NeoLoaderPC_hh__


class NeoLoaderPC : public virtual NeoPortConverter_Interface
{
private:
	ccafeopq::ComponentID_shared cid;

public:
	NeoLoaderPC();
	NeoLoaderPC(int bogon) {}
	virtual ~NeoLoaderPC() ;

	virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

#endif // __NeoLoaderPC_hh__
