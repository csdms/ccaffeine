#ifndef BooleanJC_h_seen
#define BooleanJC_h_seen

namespace jcpp {

// requires
// #include "jc++/jc++.h"
/** Boolean object ala java */
class BooleanJC : public virtual Object { 
private:
  boolean value;

public:

  BooleanJC(char * s);

  BooleanJC(boolean value_);

  /** Returns value. */
  boolean booleanValue();

  /** comparator */
  boolean equals(Object *obj);

  /** Returns TRUE or FALSE */
  char *toString();

  static BooleanJC *valueOf(char * s);
}; // BooleanJC

} ENDSEMI // jcpp

#endif // BooleanJC_h_seen
