#ifndef __ParameterPort_h_seen__
#define __ParameterPort_h_seen__

/** ParameterPort for use in user interfaces.
   @author Ben Allan, 9/30/1999, Sandia National Laboratories.
   $Id: ParameterPort.h,v 1.8 2005/02/01 00:14:31 baallan Exp $
 */

/** ParameterPort implements a protocol for
    extracting input from a user. This interface supports the
    fundamental information for forms, text prompts, GUIs, and
    sanity checking.

    @see BaseParameter
    @see DefaultParameterPort

    In a reasonable framework, each component advertising a
    provides port of this type will implement that provides
    port with a local instance of the ParameterPort obtained
    from a cca std factory uses interface supported by the
    framework, as implementing the port directly would be a 
    monumental waste of time.

 */
class ParameterPort 
#ifdef HAVE_CLASSIC
: public virtual classic::gov::cca::Port
#endif
{ 

public:

  virtual ~ParameterPort() {}

  /** Return stringified form of all known requests, with
      embedded title/tab information.  If bogus request, returns null. 
      The string is likely to contain carriage returns.
      Currently it is an ad hoc format. Eventually it may be
      an xml string.
   */
  /* CFREE */ virtual char * getConfigurationString(char *infix)=0;

  /** Return the stringified form of the request with name "fieldName".
      If fieldName unknown, returns null. */
  /* CFREE */virtual char * getConfigurationString(char *infix, char * fieldName)=0;

  /** Store the value for stringified form of answer (value) 
      into one request (fieldname). There is no massed setConfig function. */
  virtual int setConfigurationString(char * fieldName, char * value) =0;

  /** Returns the actual parameter object named. */
  virtual BaseParameter *getParameter(char *fieldName)=0;

};

#endif //__ParameterPort_h_seen__
