#ifndef __BABELOPAQUEGOPORT_H__
#define __BABELOPAQUEGOPORT_H__


class BabelOpaqueGoPort : public virtual ccafeopq::GoPort, 
			  public virtual BabelOpaquePort ,
			  public virtual KernelPort
{
 private:
  gov::cca::ports::GoPort gp;
 public:
  virtual ~BabelOpaqueGoPort();
  BabelOpaqueGoPort(gov::cca::ports::GoPort gp);
  virtual int go();
};


#endif //__BABELOPAQUEGOPORT_H__
