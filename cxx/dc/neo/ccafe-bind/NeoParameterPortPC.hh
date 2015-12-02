#ifndef __NeoParameterPortPC_hh__
#define __NeoParameterPortPC_hh__

class NeoParameterPortWrap;

class NeoParameterPortPC : public virtual NeoPortConverter_Interface
{
private:

public:
  NeoParameterPortPC();
  NeoParameterPortPC(int bogon) {}
  virtual ~NeoParameterPortPC() ;

  virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

#endif // __NeoParameterPortPC_hh__
