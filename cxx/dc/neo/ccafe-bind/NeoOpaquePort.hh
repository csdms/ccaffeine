#ifndef __NEOOPAQUEPORT_H__
#define __NEOOPAQUEPORT_H__


class NeoOpaquePort : public virtual ccafeopq::support::Port {
private:
   neo::cca::Port * neo_port;
   int neo_num;
   static int neo_nextNum;

public:
  virtual ~NeoOpaquePort();

  NeoOpaquePort(neo::cca::Port* p);
  NeoOpaquePort(int bogon) : neo_port(0), neo_num(0) {}
  // call this only by inheritance, not directly.
  NeoOpaquePort();
  
  /** override this if you inherit this base into a neo port
   * implementation.
   */
  virtual ::neo::cca::Port * getNeoPort();

  /** call this in your ctor if ou inherit this base into a neo port
   * implementation.
   */
  void initNeo();

};

#endif //__CCAFEOPAQUEPORT_H__
