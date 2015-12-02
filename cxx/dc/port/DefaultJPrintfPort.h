#ifndef __DEFAULTJPRINTFPORT_H__
#define __DEFAULTJPRINTFPORT_H__


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
class DefaultJPrintfPort : 
#ifdef HAVE_CLASSIC
  public virtual ClassicOpaquePort,
  public virtual classic::gov::cca::JPrintfPort,
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
  /// this is a hack. do the adapter and make it go away.
  public virtual NeoOpaquePort,
  public virtual neo::cca::ports::JPrintfPort, 
#endif // HAVE_NEO
  public virtual KernelPort {

public:

  DefaultJPrintfPort();
  DefaultJPrintfPort(int bogon);
  virtual ~DefaultJPrintfPort(){}

#ifdef HAVE_CLASSIC
  virtual classic::gov::cca::Port * getClassicPort();
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
  virtual neo::cca::Port * getNeoPort();
#endif // HAVE_NEO

  /** Output a string on out device */
  virtual void p(char* msg) ;
  virtual void p(char const* msg) ;
  /** Output a string on out device with added \n */
  virtual void pn(char * msg) ;
  virtual void pn(const char * msg) ;

  /** Output a string on err device */
  virtual void e(char* msg) ;
  virtual void e(const char* msg) ;
  /** Output a string on err device with added \n */
  virtual void en(char* msg) ;
  virtual void en(const char* msg) ;

  /** Output a string on log device */
  virtual void l(char* msg) ;
  virtual void l(const char* msg) ;
  /** Output a string on log device with added \n */
  virtual void ln(char* msg) ;
  virtual void ln(const char* msg) ;



  /** Output a string& on out device */
  virtual void p(std::string& msg) ;
  virtual void p(const std::string& msg) ;
  /** Output a string on out device with added \n */
  virtual void pn(std::string& msg) ;
  virtual void pn(const std::string& msg) ;

  /** Output a string on err device */
  virtual void e(std::string& msg) ;
  virtual void e(const std::string& msg) ;
  /** Output a string on err device with added \n */
  virtual void en(std::string& msg) ;
  virtual void en(const std::string& msg) ;

  /** Output a string on log device */
  virtual void l(std::string& msg) ;
  virtual void l(const std::string& msg) ;
  /** Output a string on log device with added \n */
  virtual void ln(std::string& msg) ;
  virtual void ln(const std::string& msg) ;



};

extern DefaultJPrintfPort DefaultJPrintfPort_djpp;

#endif //__DEFAULTJPRINTFPORT_H__
