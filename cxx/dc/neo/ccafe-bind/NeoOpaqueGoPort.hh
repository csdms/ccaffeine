#ifndef __NEOOPAQUEGOPORT_H__
#define __NEOOPAQUEGOPORT_H__

class NeoOpaqueGoPort :
                        public virtual NeoOpaquePort, 
                        public virtual ccafeopq::GoPort,
                        public virtual KernelPort,
                        public virtual neo::cca::Port
{
 private:
  neo::cca::ports::GoPort *gp;
  int goNum;
  static int goNextNum;


 public:
  virtual ~NeoOpaqueGoPort();
  NeoOpaqueGoPort(neo::cca::ports::GoPort *gp);
  NeoOpaqueGoPort(int bogon) : gp(0), goNum(0) {}
  virtual int go();
};

#endif // __NEOOPAQUEGOPORT_H__
