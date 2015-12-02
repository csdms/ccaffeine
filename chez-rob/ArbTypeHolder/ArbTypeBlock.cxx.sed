// This file should be named CCA_@@TypeName@@Block.h for it to work
// with class ArbTypeHolder.

#include <stdio.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "jc++/lang/Object.h"
#include "jc++/util/jc++util.h"
#include "dc/port/CCA_Block.h"
#include "Arb_Type_CCA_Block.cxx"
#include "@@TypeName@@.h"

#define BMAGIC 0xc2
#define EMAGIC 0xc3

CCA_@@TypeName@@Block::CCA_@@TypeName@@Block(CCA_BlockDescription *bd) {

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

    master= (@@Type@@ *)malloc(msize*sizeof(@@Type@@)); // guard of 2.
    assert(master!=0);
    unsigned char* tmpB = (unsigned char*) &bmagic;
    unsigned char* tmpE = (unsigned char*) &emagic;
    for(int i = 0;i < sizeof(bmagic);i++) {
      tmpB[i] = BMAGIC;
      tmpE[i] = EMAGIC;
    }
    master[0] = bmagic;
    master[msize-1] = emagic;
    data = &(master[1]);

    stack = 0;
    if (bd->getIsStacked()) {
      stack = (@@Type@@ **)malloc(sizeof(@@Type@@ *)*nf);
      for (int i = 0; i < nf; i++) {
        stack[i] = &(data[fieldSize*i]);
      }
    }
      
}

CCA_@@TypeName@@Block::~CCA_@@TypeName@@Block() {
    if (master != 0) {
      assert(master[0] == bmagic);
      assert(master[msize-1] == emagic);
      bd_ = 0;
      free(master);
    }
}

CCA_BlockDescription *CCA_@@TypeName@@Block::getDescription() {
    return bd_;
}

@@Type@@ *CCA_@@TypeName@@Block::getData() {
    return data;
}

int CCA_@@TypeName@@Block::isBeginMagicNumberOK(@@Type@@ magicTest) {
    unsigned char* tmp = (unsigned char*) &magicTest;
    for(int i = 0;i < sizeof(@@Type@@);i++) {
      if(tmp[i] != BMAGIC) return 0;
    }
    return 1;
}
int CCA_@@TypeName@@Block::isEndMagicNumberOK(@@Type@@ magicTest) {
    unsigned char* tmp = (unsigned char*) &magicTest;
    for(int i = 0;i < sizeof(@@Type@@);i++) {
      if(tmp[i] != EMAGIC) return 0;
    }
    return 1;
}

