#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Object.h"
#include "HashKey.h"
#include "String.hh"


jcpp::StringJC::StringJC()
{ 
  buffer_ptr = orig_buffer; 
  buffer_size = 64;       
  buffer_ptr[0] = '\0';
};

jcpp::StringJC::StringJC(const char* str)
{
  buffer_ptr = orig_buffer; buffer_size = 64;
  buffer_ptr[0] = '\0';
  resize(strlen(str)+1);
  strncpy(buffer_ptr, str, strlen(str)+1);
};



jcpp::StringJC::~StringJC()
{
  if (buffer_ptr != orig_buffer)
    delete buffer_ptr;
};


boolean jcpp::StringJC::equals(Object* obj)
{ 
  jcpp::StringJC* otherStr = dynamic_cast<jcpp::StringJC*> (obj); CHECKDC(otherStr);
  printf("comparing strings: %s and %s\n", buffer_ptr, otherStr->buffer_ptr);
  return (strcmp(buffer_ptr, otherStr->buffer_ptr) == 0);
}


int jcpp::StringJC::hashValue() {
  int hashNum = 0;
  int n = strlen(buffer_ptr);
  for (int i = 0; i < n; i++) {
    hashNum += (buffer_ptr[i]*31^(n-1));
  }
  return hashNum;
}


void jcpp::StringJC::append(const char* str)
{
  int origLen = strlen(buffer_ptr);
  int strLen = strlen(str);
  resize (strlen(str) + origLen + 1);
  int copyLen = ((buffer_size - origLen) < strLen) ? (buffer_size - origLen) : strLen;
  strncpy(&(buffer_ptr[origLen]),str, copyLen);
  buffer_ptr[origLen+copyLen] = '\0';
};

int jcpp::StringJC::indexOf(const char *needle)
{
  char *top;
  top = strstr(buffer_ptr,needle);
  if (top != NULL) {
    return top-buffer_ptr;
  }
  return -1;
};


void jcpp::StringJC::setString(const char* string)
{
  resize(strlen(string) +1);
  strncpy(buffer_ptr, string, strlen(string)+1);
}
void jcpp::StringJC::appendSubstring(const char* srcString, int begin, int end)
{
  int origLen = strlen(buffer_ptr);
  if (end == 0)
    end = strlen(srcString);

  resize ((end-begin) + origLen + 1);
  int copyLen = ((buffer_size - origLen) < (end-begin)) ? (buffer_size - origLen) : (end - begin);
  strncpy(&(buffer_ptr[origLen]),&(srcString[begin]), copyLen);
  buffer_ptr[origLen+copyLen] = '\0';
}


void jcpp::StringJC::resize(int newSize)
{
  if (newSize > buffer_size) {
    printf("resizing buffer\n");
    char* new_buffer_ptr = (char*) malloc(newSize);
    strncpy(new_buffer_ptr, buffer_ptr, strlen(buffer_ptr));
    if (buffer_ptr != orig_buffer)
      free (buffer_ptr);
    buffer_ptr = new_buffer_ptr;
    buffer_size = newSize;
  }
}

