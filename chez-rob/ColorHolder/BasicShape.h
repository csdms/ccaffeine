#ifndef ___BASICSHAPE_H__
#define ___BASICSHAPE_H__

#include "Shape.h"

/** Simplest shape (1-d overlap) */
class BasicShape : public virtual Shape {
 private:
  /** Overlap count */
  int radius;
 public:
  BasicShape(int overlapRadius) {
    this->radius = overlapRadius;
  }
  virtual ~BasicShape(){}
  /** Fetch overlap count */
  virtual int getOverlapRadius() {
    return radius;
  }
};

#endif // ___BASICSHAPE_H__
