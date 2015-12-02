#ifndef __NeoBuilderServicePC_hh__
#define __NeoBuilderServicePC_hh__

//class NeoParameterPortWrap;

class NeoBuilderServicePC : public virtual NeoPortConverter_Interface
{
private:

public:
  NeoBuilderServicePC();
  NeoBuilderServicePC(int bogon);
  virtual ~NeoBuilderServicePC() ;

  virtual neo::cca::Port * convert(::ccafeopq::Port * op);

};

extern NeoBuilderServicePC NeoBuilderServicePC_test;
#endif // __NeoBuilderServicePC_hh__
