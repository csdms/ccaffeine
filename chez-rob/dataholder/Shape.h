#ifndef __SHAPE_H__
#define __SHAPE_H__
/** Basic interface for determining overlap in block decomposition
of structured grid data. */
class Shape {
 public:
  virtual ~Shape(){}
  /** The radius in any dimension of the system that will contain all
      the overlap necessary to do the computation. */
  virtual int getOverlapRadius() = 0;
};


#endif // __SHAPE_H__
