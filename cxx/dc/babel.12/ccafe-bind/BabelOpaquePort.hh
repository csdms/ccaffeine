#ifndef __BABELOPAQUEPORT_H__
#define __BABELOPAQUEPORT_H__


class BabelOpaquePort : public virtual ::ccafeopq::support::Port {

 private:
  gov::cca::Port p;
 protected:
  void setPort(gov::cca::Port p_);
 public:
  virtual ~BabelOpaquePort();

  BabelOpaquePort(gov::cca::Port p_);
  BabelOpaquePort();
  
  gov::cca::Port getBabelPort() ;

  void initBabel();
};


#endif //__BABELOPAQUEPORT_H__
