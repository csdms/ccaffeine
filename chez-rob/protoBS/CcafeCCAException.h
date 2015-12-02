#ifndef  __CCAFECCAEXCEPTION_H__
#define __CCAFECCAEXCEPTION_H__

// All things are done in Benmode:

// #include <stdio.h>
// #include <strings.h>
// #include <cca.h>

class CcafeCCAException : public virtual gov::cca::CCAException {
 private:

  int type;
  char* msg;

 public:
  
  /** This constructor allows us to be a little more terse in throwing
   *      these little puppies. It has the same format as the printf
   *      family.*/
  CcafeCCAException(int type, char* fmt, ...);
  
  /** Same as CcafeCCAException(int type, char* fmt, ...) except the
      type is gov::cca::Nonstandard. */
  CcafeCCAException(char* fmt, ...);
  
  virtual ~CcafeCCAException();

  /** returns a member of the enumeration in CCAExceptionType. */
  virtual int getType();

  /** return a  (hopefully) human parseable error. */
  virtual CFREE char* getMessage();

  /** set the type of an exception. */
  virtual void setType(int type);

  /** set the string message in an exception. The method creats a copy
      for its own internal use.*/
  virtual void setMessage(char* message);
};

#endif //  __CCAFECCAEXCEPTION_H__
