#ifndef __DATAHOLDERH__
#define __DATAHOLDERH__

//requires:
// #include <cca.h>

extern "C" {

  /** Construct and return a DataHolder instance as a pointer to a CCA
      component. */
  gov::cca::Component *create_DataHolder();

};

#endif //__DATAHOLDERH__
