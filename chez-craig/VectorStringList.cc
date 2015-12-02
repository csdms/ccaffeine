#include <stdio.h>
#include <stdlib.h>
#include "VectorStringList.h"

VectorStringList::VectorStringList() : charList(0), charListAllocated(false)
{
  strVec = new std::vector<std::string>();
}

VectorStringList::VectorStringList(char** argv)
                 : charList(0), charListAllocated(false)
{
  strVec = new std::vector<std::string>();

  char* cptr = *argv;
  while (cptr != NULL) {
    strVec->push_back(cptr);
    cptr = *(++argv);
  }
}

VectorStringList::~VectorStringList()
{
  delete strVec;
  strVec = 0;
  if (charListAllocated) {
    delete[] charList;
    charList = 0;
  }
}
  
char** VectorStringList::argvList()
{
  charList = new char*[1 + strVec->size()];
  for (int i = 0; i < strVec->size(); i++) {
    charList[i] = (char*) (*strVec)[i].c_str();
  }
  charList[strVec->size()] = 0;

  return charList;
}

void
VectorStringList::clear()
{
  while ( strVec->empty() == false ) {
    strVec->pop_back();
  }
}

void
VectorStringList::dump()
{
  for (int i = 0; i < strVec->size(); i++) {
    fprintf(stderr, "list[%d] = %s\n", i, (*strVec)[i].c_str());
  }
}
