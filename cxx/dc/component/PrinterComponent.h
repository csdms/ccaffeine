#ifndef __PRINTERCOMPONENT_H__
#define __PRINTERCOMPONENT_H__

/* requires
//#include "parameters/parametersStar.h"
//#include <cca.h>
//#include "port/portInterfaces.h"
//#include "dc/port/portStar.h"
*/

/* 
PrinterComponent
   provides one Port: StringConsumerPort.
   This will take the char* and print it on the local output stream.
*/
class PrinterComponent: public virtual classic::gov::cca::Component, public virtual classic::gov::cca::StringConsumerPort {

private:
  classic::gov::cca::Services* core;

public:

  PrinterComponent(){ core = 0; }

  virtual ~PrinterComponent(){ core = 0; }

  virtual void setServices(classic::gov::cca::Services *cc);

  /** Sends the string s to PrintfPort. */
  virtual void setString(const char* s);

};
#endif // __PRINTERCOMPONENT_H__
