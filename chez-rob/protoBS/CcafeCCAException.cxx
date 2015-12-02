#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cca.h>
#include "CCAException.h"
#include "CcafeCCAException.h"


CcafeCCAException::CcafeCCAException(int type, char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  this->type = type;
  msg = (char*)malloc(1024*sizeof(char*));
  /* Boy , would I feel better about using vnsprintf here. */
  vsprintf(msg, fmt, ap);
}
  
CcafeCCAException::CcafeCCAException(char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  this->type = gov::cca::Nonstandard;
  msg = (char*)malloc(1024*sizeof(char*));
  /* Boy , would I feel better about using vnsprintf here. But Ben
     will have a fit. */
  vsprintf(msg, fmt, ap);
}
  
CcafeCCAException::~CcafeCCAException() {
  free(msg);
}

/** returns a member of the enumeration in CCAExceptionType. */
int
CcafeCCAException::getType() {
  return type;
}

/** return a  (hopefully) human parseable error. */
CFREE char* 
CcafeCCAException::getMessage() {
  return strdup(msg);
}

/** set the type of an exception. */
void
CcafeCCAException::setType(int type) {
  this->type = type;
}

/** set the string message in an exception. The method creats a copy
      for its own internal use.*/
void 
CcafeCCAException::setMessage(char* message) {
  msg = strdup(message);
}
