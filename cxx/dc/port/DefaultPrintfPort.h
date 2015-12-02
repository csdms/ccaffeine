#ifndef __DEFAULTPRINTFPORT_H__
#define __DEFAULTPRINTFPORT_H__

/** if no virtual varargs supported by
 * cca-spec-classic, this is a donothing class.
 */
#ifndef HAVE_PRINTFPORT
#define HAVE_PRINTFPORT 0
#else
#if (HAVE_PRINTFPORT+1)==1
#undef HAVE_PRINTFPORT
#define HAVE_PRINTFPORT 0
#endif
#endif // HAVE_PRINTFPORT init

/** A just-print-it port implementation.  Tremendously buggy.
The implementation of this port here merges log and err
channels.

It is good practice for components implementing this
interface to return immediately (minimizing cost) if
noone is listening even though the component insists
on talking.

The const versions of the member functions exist to
shut up the Solaris compilers.
*/
class DefaultPrintfPort
#ifdef HAVE_CLASSIC
#if HAVE_PRINTFPORT
: public virtual classic::gov::cca::PrintfPort 
#else
: public virtual classic::gov::cca::Port
#endif // HAVE_PRINTFPORT
#endif // HAVE_CLASSIC
{

public:

  DefaultPrintfPort();
  virtual ~DefaultPrintfPort(){}

#if HAVE_PRINTFPORT
  /** Output a string on out device ... ala printf */
  virtual void p(char* fmt, ...) ;
  virtual void p(char const* fmt, ...) ;
  /** Output a string on out device with added \n ... ala printf */
  virtual void pn(char * fmt, ...) ;
  virtual void pn(const char * fmt, ...) ;

  /** Output a string on err device ... ala printf */
  virtual void e(char* fmt, ...) ;
  virtual void e(const char* fmt, ...) ;
  /** Output a string on err device with added \n ... ala printf */
  virtual void en(char* fmt, ...) ;
  virtual void en(const char* fmt, ...) ;

  /** Output a string on log device ... ala printf */
  virtual void l(char* fmt, ...) ;
  virtual void l(const char* fmt, ...) ;
  /** Output a string on log device with added \n ... ala printf */
  virtual void ln(char* fmt, ...) ;
  virtual void ln(const char* fmt, ...) ;
#endif

};


#endif //__DEFAULTPRINTFPORT_H__
