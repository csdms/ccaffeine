#ifndef __CLASSICOPAQUEPORT_H__
#define __CLASSICOPAQUEPORT_H__


class ClassicOpaquePort : public virtual ccafeopq::support::Port
{
private:
   classic::gov::cca::Port * classic_port;
   int classic_num;
   static int classic_nextNum;

public:
  virtual ~ClassicOpaquePort();

  /** When this constructor is directly used, the CLASSIC string
   * tag gets applied.
   */
  ClassicOpaquePort(classic::gov::cca::Port* p);

  /** This constructor gets used only when COP is as a base
   * inherited. The derived class must call initClassic
   * in its constructor.
   */
  ClassicOpaquePort();
  
  /** Return a wrapped pointer. If inheriting
   * COP into a port *implementation*, then this
   * function must be overridden to return 'this'.
   * Normally the wrapped pointer classic_port
   * is returned.
   */
  virtual ::classic::gov::cca::Port * getClassicPort();

  /** Apply string tag so that opaque layer will recognize
   * us. needed only if COP is used as a base for derived class.
   */
  void initClassic();
  
};

#endif //__CCAFEOPAQUEPORT_H__
