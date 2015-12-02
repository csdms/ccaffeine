#ifndef __NeoBasicParameterPortPC_hh__
#define __NeoBasicParameterPortPC_hh__

class NeoBasicParameterPortWrap;

class NeoBasicParameterPortPC : public virtual NeoPortConverter_Interface
{
private:

public:
  NeoBasicParameterPortPC();
  NeoBasicParameterPortPC(int bogon);
  virtual ~NeoBasicParameterPortPC();

  virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

#endif // __NeoBasicParameterPortPC_hh__
