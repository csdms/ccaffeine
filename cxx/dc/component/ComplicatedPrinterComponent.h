#ifndef __COMPLICATEDPRINTERCOMPONENT_H__
#define __COMPLICATEDPRINTERCOMPONENT_H__

/* requires
//#include "parameters/parametersStar.h"
//#include <cca.h>
//#include "port/portInterfaces.h"
//#include "dc/port/portStar.h"
*/

/* 
ComplicatedPrinterComponent
   provides one Port: StringConsumerPort.
   This will take the char* and print it on the local output stream.
*/
class ComplicatedPrinterComponent: public virtual classic::gov::cca::Component, public virtual classic::gov::cca::StringConsumerPort {

private:
  classic::gov::cca::Services* core;
  classic::gov::cca::JPrintfPort* pfp;

public:

  ComplicatedPrinterComponent(){ core = 0; pfp = 0;}

  virtual ~ComplicatedPrinterComponent(){ core = 0; pfp = 0;}

  virtual void setServices(classic::gov::cca::Services *cc);

  /** Sends the string s to PrintfPort. */
  virtual void setString(const char* s);

};
#endif // __COMPLICATEDPRINTERCOMPONENT_H__
