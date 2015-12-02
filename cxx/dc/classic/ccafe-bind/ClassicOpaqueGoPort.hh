#ifndef __CLASSICOPAQUEGOPORT_H__
#define __CLASSICOPAQUEGOPORT_H__


class ClassicOpaqueGoPort : public virtual ccafeopq::GoPort,
                            public virtual ClassicOpaquePort, 
                            public virtual KernelPort,
                            public virtual classic::gov::cca::Port
{
 private:
  classic::gov::cca::GoPort *gp;
  int goNum;
  static int goNextNum;


 public:
  virtual ~ClassicOpaqueGoPort();
  ClassicOpaqueGoPort(classic::gov::cca::GoPort *gp);
  virtual int go();
};

#endif // __CLASSICOPAQUEGOPORT_H__
