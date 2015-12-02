#ifndef __NeoParameterPortFactoryPC_hh__
#define __NeoParameterPortFactoryPC_hh__


class NeoParameterPortFactoryPC : public virtual NeoPortConverter_Interface
{
private:

public:
  NeoParameterPortFactoryPC();
  NeoParameterPortFactoryPC(int bogon) {}
  virtual ~NeoParameterPortFactoryPC() ;

  virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

#endif // __NeoParameterPortFactoryPC_hh__
