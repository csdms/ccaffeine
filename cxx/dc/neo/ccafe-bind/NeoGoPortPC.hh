#ifndef __NeoGoPortPC_hh__
#define __NeoGoPortPC_hh__

//class NeoParameterPortWrap;

class NeoGoPortPC : public virtual NeoPortConverter_Interface
{
private:

public:
  NeoGoPortPC();
  NeoGoPortPC(int bogon);
  virtual ~NeoGoPortPC() ;

  virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

extern NeoGoPortPC NeoGoPortPC_test;
#endif // __NeoGoPortPC_hh__
