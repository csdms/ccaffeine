#ifndef __CCA_BLOCK_H__
#define __CCA_BLOCK_H__

#include <assert.h>

/** 1-d mapping of data */
struct CCA_dimenMap {
/** low index of data we own */
  int gLow; 
/** high index of data we own */
  int gHigh; 
/** padding count of data before us. */
  int beginPad; 
/** padding count of data after us */
  int endPad; 
/** total size in global terms of this dimension */
  int gSize; 
/** processor owning our beginPad. -1 -> nobody. */
  int procBefore; 
/** processor owning our endPad. -1 -> nobody. */
  int procAfter; 
};

/**
  On each processor we have gLow-gHigh data to ourself.
  In addition we have beginPad <= gLow and endPad >= gHigh
  data shadowing other processors.

  Conceivably should be rewritten in mpi data_type 
  or Cart terms.

  The Block introspection is separate from the block
  data because the CCA_BlockDescription could be the
  currency for requesting a block from a data manager.
  The block data manager would have the option of
  returning a CCA_DoubleBlock with a different but
  compatible description (i.e. larger, or with more fields)
  depending on how the data manager was queried.
  e.g. getBlockExact(CCA_BlockDescription * bd) {...}
    will do a data copy to create the block matching bd
  while getBlock(CCA_BlockDescription * bd) {...} makes
    sure only that what it returns is a superset of the
    specification in bd.

 */
class CCA_BlockDescription {

private:
  int nDim;
  /** 0 -> strided data, 1 ->stacked data */
  int stored; 
  /** array [nDim] long */
  struct CCA_dimenMap *dim;
  int nFields;
  int capFields;
  /** array [nFields] long */
  int *fieldId;
  /** array [nFields] long */
  char **fieldName;
  int locked;
  int blockId;

public:
  CCA_BlockDescription() ;

  ~CCA_BlockDescription() ;

  void setDimensions(int n) ;

  void setLayout(int dimension, int gLow, int gHigh,
		int beginPad, int endPad, int gSize,
		int blockBefore, int blockAfter, int blockId) ;

  void getLayout(int dimension, int *gLow, int *gHigh,
		int *beginPad, int *endPad, int *gSize,
		int *blockBefore, int *blockAfter, int *blockId) ;

  /** @param fieldTag can be anything but must be unique.
  // @param fieldString must be unique if given; it can
  // be NULL and we'll make something up: field%d. */
  void addField(int fieldTag, char *fieldString) ;

  /** Returns the field layer in stacked data or 
  // the field location in strided data.
  // Returns -1 if field not known. */
  int getFieldOffset(int fieldTag) ;
    
  /** Returns the field layer in stacked data or 
  // the field location in strided data given a string name.
  // Returns -1 if fieldName not known. */
  int getFieldNameOffset(char *name) ;

  void fixDescription() ;

  /** Returns the index of this block. total blocks
  // in a data set are indexed 0 to n-1.
  // Depending on the distributed memory implementation,
  // The blockId may line up with a processor number or not. */
  int getBlockId();

  const struct CCA_dimenMap *getDimensions(int& n) ;
  const char **getFieldNames(int &nf) ;
  const int *getFieldTags(int &nf) ;
  int getNFields() ;

  /** Returns 1 if each field is stored contiguously.
  // Returns 0 if all the fields for a given index in
  // in the block are stored contiguously. */
  int getIsStacked() ;

};

/** Base block structured data interface. */
class CCA_Block
{
 public:
  virtual ~CCA_Block() {}
  virtual CCA_BlockDescription *getDescription()=0;
  virtual double *getData()=0;
};

/** Fancy block data. */
class CCA_DoubleBlock : public virtual CCA_Block {
private:
  double *master;
  double *data;
  double **stack;
  CCA_BlockDescription *bd_;
  int msize;

public:

  CCA_DoubleBlock(CCA_BlockDescription *bd) ;

  virtual ~CCA_DoubleBlock() ;

  virtual CCA_BlockDescription *getDescription() ;

  virtual double *getData() ;

};

/** Fancy block data that provides a different view of an existing block */
class CCA_SharedDoubleBlock : public virtual CCA_Block {
private:
  double *master;
  double *data;
  double **stack;
  CCA_BlockDescription *bd_;
  int msize;

public:

  CCA_SharedDoubleBlock(CCA_BlockDescription *bd, double *sharedData) ;

  virtual ~CCA_SharedDoubleBlock() ;

  virtual CCA_BlockDescription *getDescription() ;

  virtual double *getData() ;

};

#endif // __CCA_BLOCK_H__
