/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: Enumeration.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/

#ifndef Enumeration_h_seen
#define Enumeration_h_seen

namespace jcpp {

/** Basic interface for enumerating any object container contents. */
class Enumeration : public virtual Object {

public:

  virtual ~Enumeration(){}
  /** Returns true while enumeration has more elements available */
  virtual boolean hasMoreElements() = 0;
  /** fetches the next element or returns 0 if none left. */
  virtual Object *nextElement() = 0;

};

} ENDSEMI //jcpp
#endif // Enumeration_h_seen
