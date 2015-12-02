#ifndef __ClassicGoPortPC_hh__
#define __ClassicGoPortPC_hh__

//class ClassicParameterPortWrap;

class ClassicGoPortPC : public virtual ClassicPortConverter_Interface
{
private:

public:
  ClassicGoPortPC();
  ClassicGoPortPC(int bogon);
  virtual ~ClassicGoPortPC() ;

  virtual classic::gov::cca::Port * convert(::ccafeopq::Port * op);

};

extern ClassicGoPortPC ClassicGoPortPC_test;
#endif // __ClassicGoPortPC_hh__
