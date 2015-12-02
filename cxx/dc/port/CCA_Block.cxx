#include <stdio.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "dc/export/config.hh"
#include "dc/port/CCA_Block.h"

#define BMAGIC 2.718283141590101
#define EMAGIC -2.718283141590101

namespace {
char * STRDUP(const char *s)
{
	size_t n = strlen(s) +1;
	char *v = (char *)malloc(n);
	strcpy(v,s);
	return v;
}
} ENDSEMI

CCA_BlockDescription::CCA_BlockDescription() 
{
    nDim = -1;
    stored = 1;
    dim = 0;
    nFields = -1;
    capFields = -1;
    fieldId = 0;
    fieldName = 0;
    locked = 0;
    blockId = -1;
}

CCA_BlockDescription::~CCA_BlockDescription() {
    if (nDim >= 0) {
      free(dim);
      dim = 0;
    }
    nDim = -2;

    if (nFields >= 0) {
      free(fieldId);
      fieldId = 0;
      for (int i = 0; i < nFields; i++) {
        free(fieldName[i]);
      }
      free(fieldName);
      fieldName = 0;
    }
    nFields = -2;
    blockId = -2;
}

void CCA_BlockDescription::setDimensions(int n) {
    if (n!=0 && nDim != -1) {
      assert(0);//improper resizing of block.
    }
    nDim = n;
    dim = (struct CCA_dimenMap *)malloc(nDim*sizeof(struct CCA_dimenMap));
    for (int i = 0; i < nDim; i++) {
      dim[i].gLow =
        dim[i].gHigh =
        dim[i].beginPad =
        dim[i].endPad =
        dim[i].gSize = 
        dim[i].procBefore = 
        dim[i].procAfter = -1;
    }
}

void CCA_BlockDescription::setLayout(int dimension, int gLow, int gHigh, int beginPad, int endPad,
int gSize, int procBefore, int procAfter, int bid) {
    assert(gSize > 0);
    assert(gLow >= 0);
    assert(beginPad >= 0);
    assert(endPad >= 0);
    assert(gHigh <= gSize);
    assert(gLow < gHigh);
    assert(procBefore >= 0 || beginPad == 0);
    assert(procAfter >= 0 || endPad == 0);
    assert(bid >= 0);
    int i = dimension;
    dim[i].gLow = gLow;
    dim[i].gHigh = gHigh;
    dim[i].beginPad = beginPad;
    dim[i].endPad = endPad;
    dim[i].gSize = gSize;
    dim[i].procBefore = procBefore;
    dim[i].procAfter = procAfter;
    blockId = bid;
}

void CCA_BlockDescription::getLayout(int dimension, int *gLow, int *gHigh, int *beginPad, int *endPad,
int *gSize, int *procBefore, int *procAfter, int *bid) {
  int i = dimension;
    *gLow = dim[i].gLow;
    *gHigh = dim[i].gHigh;
    *beginPad = dim[i].beginPad;
    *endPad = dim[i].endPad;
    *gSize = dim[i].gSize;
    *procBefore = dim[i].procBefore;
    *procAfter = dim[i].procAfter;
    *bid = blockId;
}

  // fieldTag can be anything but must be unique.
  // fieldString must be unique if given; it can
  // be NULL and we'll make something up: field%d.
void CCA_BlockDescription::addField(int fieldTag, char *fieldString) {
    if (nFields == -1) {
      capFields = 10;
      nFields = 0;
      fieldName = (char **)malloc(capFields*sizeof(char *));
      fieldId = (int *)malloc(capFields*sizeof(int));
    }
    if (nFields == capFields) {
      assert(0); // need to add expansion code here later.
    }

    // fixme
    // assert(fieldString != existing strings);

    fieldId[nFields] = fieldTag;
    char def[40];
    sprintf(def,"field%d",nFields);
    fieldName[nFields] = STRDUP((fieldString!=0)?fieldString:def);
    assert(fieldName[nFields]!=0);
    nFields++;
}

  // Returns the field layer in stacked data or 
  // the field location in strided data.
  // Returns -1 if field not known.
int CCA_BlockDescription::getFieldOffset(int fieldTag) {
    for (int i = 0; i < nFields; i++) {
      if (fieldId[i] == fieldTag) {
         return i;
      }
    }
    return -1;
}
    
  // Returns the field layer in stacked data or 
  // the field location in strided data given a string name.
  // Returns -1 if fieldName not known.
int CCA_BlockDescription::getFieldNameOffset(char *name) {
    if (name == 0) {
      return -1;
    }
    for (int i = 0; i < nFields; i++) {
      if (strcmp(fieldName[i],name) == 0) {
         return i;
      }
    }
    return -1;
}

void CCA_BlockDescription::fixDescription() {
    locked = 1;
}

const struct CCA_dimenMap *CCA_BlockDescription::getDimensions(int& n) {
    n = nDim;
    return dim;
}

int CCA_BlockDescription::getBlockId() {
    return blockId;
};

const char **CCA_BlockDescription::getFieldNames(int &nf) {
    nf = nFields;
    return (const char**)fieldName;
}
const int *CCA_BlockDescription::getFieldTags(int &nf) {
    nf = nFields;
    return fieldId;
}
int CCA_BlockDescription::getNFields() {
    return nFields;
}

  // returns 1 if each field is stored contiguously.
  // returns 0 if all the fields for a given index in
  // in the block are stored contiguously.
int CCA_BlockDescription::getIsStacked() {
    return stored;
}

CCA_DoubleBlock::CCA_DoubleBlock(CCA_BlockDescription *bd) {

    int fieldSize;
    int nf;
    int nd;
    const struct CCA_dimenMap *dim;

    assert(bd!=0);
    bd->fixDescription();
    bd_ = bd;
    dim = bd->getDimensions(nd);

    fieldSize = 1;
    for (int i = 0; i < nd; i++) {
      fieldSize *= (dim[i].beginPad + dim[i].endPad + 
                    dim[i].gHigh - dim[i].gLow + 1);
    }
    assert(fieldSize >= 0);

    // allocate storage
    nf = bd->getNFields();
    msize = fieldSize*nf+2; // guard of 2.

    master= (double *)malloc(msize*sizeof(double)); // guard of 2.
    assert(master!=0);
    master[0] = BMAGIC;
    master[msize-1] = EMAGIC;
    data = &(master[1]);

    stack = 0;
    if (bd->getIsStacked()) {
      stack = (double **)malloc(sizeof(double *)*nf);
      for (int i = 0; i < nf; i++) {
        stack[i] = &(data[fieldSize*i]);
      }
    }
      
}

CCA_DoubleBlock::~CCA_DoubleBlock() {
    if (master != 0) {
      assert(master[0] == BMAGIC);
      assert(master[msize-1] == EMAGIC);
      bd_ = 0;
      free(master);
    }
}

CCA_BlockDescription *CCA_DoubleBlock::getDescription() {
    return bd_;
}

double *CCA_DoubleBlock::getData() {
    return data;
}


// This is a "fake" CCA_Block which exists to provide a different view
// of an existing (real) CCA_Block.  It takes a pointer to the data of
// interest in the constructor and neither creates nor deletes this data.

CCA_SharedDoubleBlock::CCA_SharedDoubleBlock(CCA_BlockDescription *bd,
					     double *sharedData ) {

    int fieldSize;
    int nf;
    int nd;
    const struct CCA_dimenMap *dim;

    assert(bd!=0);
    bd->fixDescription();
    bd_ = bd;
    dim = bd->getDimensions(nd);

    fieldSize = 1;
    for (int i = 0; i < nd; i++) {
      fieldSize *= (dim[i].beginPad + dim[i].endPad + 
                    dim[i].gHigh - dim[i].gLow + 1);
    }
    assert(fieldSize >= 0);

    data = sharedData;

    nf = bd->getNFields();
    stack = 0;
    if (bd->getIsStacked()) {
       stack = (double **)malloc(sizeof(double *)*nf);
       for (int i = 0; i < nf; i++) {
 	stack[i] = &(data[fieldSize*i]);
       }
     }
}

CCA_SharedDoubleBlock::~CCA_SharedDoubleBlock() {
  bd_ = 0;
}

CCA_BlockDescription *CCA_SharedDoubleBlock::getDescription() {
    return bd_;
}

double *CCA_SharedDoubleBlock::getData() {
    return data;
}

