#ifndef __TIMER_H__
#define __TIMER_H__

/* requires
//#include "parameters/parametersStar.h"
//#include "util/IO.h"
//#include <cca.h>
//#include "port/portInterfaces.h"
//#include <time.h>
*/


/** Gives a time string, implementing TimeProducerPort. */
class Timer :  public virtual classic::gov::cca::Component, public virtual classic::gov::cca::TimeProducerPort {
private:

  classic::gov::cca::Services* myCore;

public:

  Timer(){}
  virtual ~Timer(){}

  void setServices(classic::gov::cca::Services *svc);

  /*CFREE*/ char* getTime();

};
#endif //__TIMER_H__
