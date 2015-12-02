#ifdef _CCAMPI
#include "mpi.h"
#endif

#include <stdlib.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include <cca.h>
#include "parameters/parametersStar.h"
#include "port/supportInterfaces.h"
//#include "port/portInterfaces.h" // Events ? goes away now?
#include "dc/port/CCA_Block.h"
#include "dc/port/BlockPort.h"
#include "BasicShape.h"
#include "util/IO.h"

//#include <ESI.h>
//#include <ESICCA.h>
//#include <snl-cpp.h>
#include "DataHolder.h"

/**
------------|-----.-------|-----------------------------|----.---|-----
|           |     .       |               		|    .   |    
|           |     .       |               m       	|    .   |    
|           |     .    O  |               y       	|    .   |    
|           |  G  .    v  |               P       	|    .   |    
|       m   |  h  .    e  |               r       	|    .   |    
|       y   |  o  .    r  |               o       	|    .   |    
|       P   |  s  .    l  |               c       	|    .   |    
|       r   |  t  .    a  |               		|    .   |   
|       o   |     .    p  |               		|    .   |   
|       c   |  C  .       |               		|    .   |   
|           |  e  .    C  |               		|    .   |   
|       |   |  l  .    e  |               		|    .   |   
|           |  l  .    l  |               		|    .   |   
|       1   |  s  .    l  |               		|    .   |   
|	    |     .    s  |               		|    .   |   
|	    |     .       |               		|    .   |   
|	    |     .       |               		|    .   |   
------------|-----.-------|-----------------------------|----.---|-----
	    |	  .       |    	        		|    .	 |
	    |	  .       |ghostUB(for myProc - 1)      |    .	 |ghostUB(for myProc)
	    |	  .       |overlapLB(for myProc)	|    .	 |overlapLB(for myProc + 1)
	    |	  .	  				|    .	 		       	 
	    |	  .endCol(for myProc - 1)       	|    .endCol(for myProc)       
	    |	  .beginCol(for myProc) 	        |    .beginCol(for myProc + 1)
	    |	        				|    			  
	    |overlapUB(for myProc - 1)    		|    			  
	    |ghostLB(for myProc)          		|overlapUB(for myProc)    
	               					|ghostLB(for myProc + 1)  
	  	     					
*/	  




CmptInfo::CmptInfo(CCA_Block** b) { 
  this->b = b;
  shape = 0;
}

CmptInfo::~CmptInfo(){
  if(shape != 0) delete shape;
}

CCA_Block** CmptInfo::getBlock() {
  return b;
}

void CmptInfo::setShape(CDELETE Shape* s) {
  if(shape != 0) delete shape;
  shape = s;
}

Shape* CmptInfo::getShape() {
  return shape;
}

DataHolder::DataHolder() {
  debug = TRUE;
  init();
}

DataHolder::~DataHolder() {
  delete blockPtr;
  delete rows;
  delete cols;
 // fixme BUGBUG
}

/** Create the partitioning scheme that is the same on every processor */
void DataHolder::createPartition() {
  if(debug) {
    en("DataHolder::createPartition() entry.");
  }
  partitionInfo = new JCPN(Vector)();
  JCPN(Enumeration)* e = blockPtr->elements();
  // Find the maximum overlap ...
  int maxOlap = 0;
  while(e->hasMoreElements()) {
    JCPN(Object)* o = e->nextElement();
    CmptInfo* ci = dynamic_cast<CmptInfo*>(o);CHECKDC(ci);
    Shape* s = ci->getShape();
    if(s == 0) {
      en("DataHolder::createPartition: shape not set");
      return;
    }
    int olap = s->getOverlapRadius();
    if(olap > maxOlap) maxOlap = olap;
  }
  delete e;
  // Do a banded decomp by cols, real easy ...
  int numCols = cols->value;
  int numRows = rows->value;
  int minColsPerProc = numCols/numProcs;
  int remainder = numCols - minColsPerProc*numProcs;
  int beginCol = 0;
  int endCol;
  for(int proc = 0;proc < numProcs;proc++){
    ProcDomain *pd = new ProcDomain();
    pd->beginCol = beginCol;
    pd->type = oneD_NULL;
    if(remainder-- > 0) {
      endCol = pd->endCol = beginCol + minColsPerProc + 1;
    } else {
      endCol = pd->endCol = beginCol + minColsPerProc;
    }
    if(beginCol == 0) { // first block
      pd->ghostLB = pd->beginCol;
      pd->overlapLB = pd->beginCol;
      pd->type = oneD_LEFTSIDE;
    } else {
      pd->ghostLB = pd->beginCol - maxOlap;
      pd->overlapLB = pd->beginCol + maxOlap;
    }
    if(endCol == cols->value) { //last block
      pd->ghostUB = pd->endCol;
      pd->overlapUB = pd->endCol;
      if(pd->type == oneD_LEFTSIDE) {
	pd->type = oneD_ONEPROC;
      } else {
	pd->type = oneD_RIGHTSIDE;
      }
    } else {
      pd->ghostUB = pd->endCol + maxOlap;
      pd->overlapUB = pd->endCol - maxOlap;
    }
    if(pd->type == oneD_NULL) { // Still unset
      pd->type = oneD_MIDDLE;
    }
    beginCol = pd->endCol; // loop back to the top w this value
    partitionInfo->addElement(pd);
  }
  if(numProcs <= 0) {
    en("numProcs < 1:Have to have at least 1 processor");
    return;
  } else {
    ProcDomain* myDomain = 
      dynamic_cast<ProcDomain*>(partitionInfo->elementAt(myProc)); 
    CHECKDC(myDomain);
    setupBlock(myDomain);
    size = (myDomain->ghostUB - myDomain->ghostLB)*numRows;
    //    data = (double*)malloc(sizeof(double)*size);
  }
  for(int i = 0;i < size;i++) {
    *(data + i) = (double)(-myProc);
  }
}

void DataHolder::setupBlock(ProcDomain* pd) {
  if(debug) {
    en("DataHolder::setupBlock(ProcDomain* pd) entry");
    en("beginCol %d, endCol %d, ghostLB %d, ghostUB %d",
	   pd->beginCol, pd->endCol, pd->ghostLB, pd->ghostUB);
  }
  CCA_BlockDescription* blockDes = new CCA_BlockDescription();
  blockDes->setDimensions(2);
  int beginRow = 0;
  int endRow = rows->value;
  int beginCol = pd->beginCol;
  int endCol = pd->endCol;
  blockDes->setLayout(0, pd->beginCol, pd->endCol, pd->beginCol - pd->ghostLB, 
		   pd->ghostUB - pd->endCol, 
		   cols->value , myProc - 1, myProc + 1, myProc);
  blockDes->setLayout(1, beginRow, endRow, 0, 0, 
		   rows->value , myProc - 1, myProc + 1, myProc);
  blockDes->addField(0, "DATA");

  myDataBlock = new CCA_DoubleBlock(blockDes);
  data = myDataBlock->getData();
//   // ESI Map JCPN(Object) that is of rank = rows->value*cols->value but has
//   // the same decomposition as this DataHolder.  Useful if you want to
//   // create a matrix that has a row for each data value present in
//   // this Dataholder.
//   esi_msg msg;
//   esi_int4 localSize = (endRow - beginRow)*(endCol - beginCol);
//   esi_int4 localOffset = (endRow - beginRow)*beginCol;
//   en("#  DataHolder::setupBlock setting map ls=%d lo=%d",localSize, localOffset);
//   map->setLocalInfo(localSize, localOffset, msg);
}

/** Checks to see if the partitioning is sane. */
boolean DataHolder::sanityCheck() {
  if(numProcs == 1) {
    ProcDomain* a = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(0)); 
    CHECKDC(a);
    if(a->type != oneD_ONEPROC) {
      en(":-( DataHolder::SanityCheck failed: proc only != ONEPROC");
      return FALSE;
    }
    return TRUE;
  }      
  for(int i = 0;i < numProcs - 1;i++) {
    ProcDomain* a = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(i));
    CHECKDC(a);
    ProcDomain* b = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(i + 1));
    CHECKDC(b);
    if(i == 0) {
      if(a->type != oneD_LEFTSIDE) {
	en(":-( DataHolder::SanityCheck failed: proc %d != LEFTSIDE == %d",
	       myProc, a->type);
	return FALSE;
      }
    }
    if(i == numProcs - 2) {
      if(b->type != oneD_RIGHTSIDE) {
	en(":-( DataHolder::SanityCheck failed: proc top != RIGHTSIDE");
	return FALSE;
      }
    }
    boolean ok = (a->overlapUB == b->ghostLB) &&
      (a->endCol == b->beginCol) &&
      (a->ghostUB == b->overlapLB);
    if(!ok) {
      en(":-( DataHolder::SanityCheck failed:");
      en("The following lines should have equal values:");
      en("a->overlapUB = %d, b->ghostLB = %d", a->overlapUB, b->ghostLB);
      en("a->endCol = %d, b->beginCol = %d", a->endCol, b->beginCol);
      en("a->ghostUB = %d, b->overlapLB = %d", a->ghostUB, b->overlapLB);
    }
  }
  return TRUE;
}

void DataHolder::setDebug(boolean tf) {
  debug = tf;
  en("DataHolder: debugging turned on.");
}

void DataHolder::init() {
  /** note this is done before setServices. don't use ports here */
  if(debug) {
    en("DataHolder::init() called");
  }
  numProcs = -1;
  myProc = -1;
#ifdef _CCAMPI
  en("MPI mode enabled");
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myProc);
#else
  numProcs = 1;
  myProc = 0;
#endif
  if(debug) {
    en("numProcs = %d, myProc = %d", numProcs, myProc);
  }

  rows = new IntParameter("rows","Rows of data", "Rows", 0, 0, 10000);
  cols = new IntParameter("cols","Columns of data", "Columns", 0, 0, 10000);

  upTag = 271828;
  downTag = upTag + 1;
  dataCreated = FALSE;
  if(debug) {
    en(" DataHolder::init()");
    if(dataCreated) {
      en("dataCreated = true");
    } else {
      en("dataCreated = false");
    }
  }
  debug = FALSE;
  blockPtr = new HashValue();
}

/** Registers a component using the DataHolder by a suggested name,
      if the name is unique then that name is returned, if not, a
      number is appended to the sugested name that renders it
      unique. */
void DataHolder::registerCmpt(CCA_Block** b) {
  blockPtr->put(new ReferenceObject(b), new CmptInfo(b));
}

/** Shape tells the DataHolder what overlap and ghost data is needed
	required by the calling component, Name is the unique identifier
	for the caller. */
void DataHolder::setShape(Shape *s, CCA_Block** b) {
  dataCreated = FALSE; // Mark it dirty.
  if(debug) {
    en(" DataHolder::setShape()");
    if(dataCreated) {
      en("dataCreated = true");
    } else {
      en("dataCreated = false");
    }
  }
  ReferenceObject* ro = new ReferenceObject(b);
  if (!ro) {
    en("DataHolder::setShape out of memory for ReferenceObject.");
    return;
  }
  if(debug) {
    en("blockPtr: 0x%x, size = %d", blockPtr, blockPtr->size());
  }
  JCPN(Object)* o = blockPtr->getEqual(ro);
  if(o == 0) {
    en("DataHolder::setShape: no such registered component");
    delete ro;
    return;
  }
  CmptInfo* ci = dynamic_cast<CmptInfo*>(o);CHECKDC(ci);
  ci->setShape(s);
  delete ro;
}

  /** Fullfill the Component interface. */
void DataHolder::setServices(gov::cca::Services* svc) {
  this->svc = svc;

  gov::cca::PortInfo* pinfo;

  // Contact the ParameterPortFactoryService
  pinfo = svc->createPortInfo("cSvc", "gov.cca.ParameterPortFactoryService", 0);
  svc->registerUsesPort(pinfo);

  ConfigurableParameterFactory *cpf =
    dynamic_cast<ConfigurableParameterFactory*>(svc->getPort("cSvc"));
  CHECKDC(cpf);
  if(cpf == 0) {
    en("!!! DataHolder::init failed. No ConfigurableParameterFactory.");
    svc->addProvidesPort(this, svc->createPortInfo("DEAD=NoParamService", "Port", 0));
    return;
  }
  pp = cpf->createConfigurableParameterPort();
  svc->releasePort("cSvc");

  pp->setBatchTitle("DataHolder Configuration");
  pp->setGroupName("Global Size");
  pp->addRequest(rows);
  pp->addRequest(cols);

  svc->addProvidesPort(this, 
		       svc->createPortInfo("DATA", "BlockPort",0));
  svc->addProvidesPort(pp, svc->createPortInfo("CONFIG", "ParameterPort", 0));
}

/** Get the data in this DataHolder associated with the name */
double* DataHolder::getData(CCA_Block** b,
			    int& offset, 
			    int& beginRow, 
			    int& endRow, 
			    int& beginCol,
			    int& endCol) {
  if(!dataCreated) {
    createPartition();
    sanityCheck();
    dataCreated = TRUE;
  }
  ProcDomain* pd = dynamic_cast<ProcDomain*>
    (partitionInfo->elementAt(myProc));
  offset = (pd->beginCol - pd->ghostLB)*rows->value;
  beginCol = pd->beginCol;
  endCol = pd->endCol;
  beginRow = 0;
  endRow = rows->value;
  return data;
}

void DataHolder::compute() {
  // does nothing but fill vtable.
}

/** Freshens the ghosts wrt this name. */
void DataHolder::update() {
  if(debug) {
    en("DataHolder::update: called");
  }
  if(debug) {
    en(" DataHolder::update()");
    if(dataCreated) {
      en("dataCreated = true");
    } else {
      en("dataCreated = false");
    }
  }
  if(!dataCreated) {
    createPartition();
    sanityCheck();
    dataCreated = TRUE;
  }
#ifdef _CCAMPI
  if(numProcs == 1) return;
  if(debug) {
    en("About to do sending ...");
  }
  sendOddToEven();
  sendEvenToOdd();
  if(debug) {
    en("sent.");
  }

#else
  return;
#endif
}

void DataHolder::setOverlapUniform(int radius, CCA_Block **b) {
  registerCmpt(b);
  Shape* s = new BasicShape(radius);
  setShape(s, b);
}

void DataHolder::getBlock(CCA_Block** b) {
  if(debug) {
    en("DataHolder::getBlock(CCA_Block** b) called");
  }
  if(debug) {
    en(" DataHolder::getBlock()");
    if(dataCreated) {
      en("dataCreated = true");
    } else {
      en("dataCreated = false");
    }
  }
  if(!dataCreated) {
    createPartition();
    sanityCheck();
    dataCreated = TRUE;
  }
  *b = myDataBlock;
}

#ifdef _CCAMPI

void DataHolder::sendOddToEven() {
  if((myProc % 2) == 0) { // sending
    sendOverlap();      
  } else { // receiving
    rcvOverlap();
  }
}

void DataHolder::sendEvenToOdd() {
  if((myProc % 2) != 0) {// sending
    sendOverlap();
  } else {// receiving
    rcvOverlap();
  }
}

void DataHolder::sendOverlap() {
  ProcDomain* pd = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(myProc));
  CHECKDC(pd);
  int offset = (pd->beginCol - pd->ghostLB)*rows->value;
  int extent = (pd->overlapLB - pd->beginCol)*rows->value;
  if(debug) {
    en("DataHolder::sendOverlap() entry: offset = %d, extent = %d", 
	   offset, extent);
  }
  if(extent > 0) { // not on an edge
    if(debug) {
      en("%d sending to %d", myProc, myProc - 1);
      en("offset = %d, extent = %d, tag = %d", offset, extent, downTag);
    }
    MPI_Send(data + offset, extent, MPI_DOUBLE, myProc - 1, 
	     downTag, MPI_COMM_WORLD);
    if(debug) {
      for(int i = 0;i < extent;i++) {
	en("sent data%i = %g", i, *(data + offset + i));
      }
      en("done.");
    }
  }
  pd = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(myProc));
  CHECKDC(pd);
  offset = (pd->overlapUB - pd->ghostLB)*rows->value;
  extent = (pd->endCol - pd->overlapUB)*rows->value;
  if(debug) {
    en("DataHolder::sendOverlap() 2nd Send : offset = %d, extent = %d", 
	   offset, extent);
  }
  if(extent > 0) { // not on an edge
    if(debug) {
      en("%d sending to %d", myProc, myProc + 1);
      en("offset = %d, extent = %d, tag = %d", offset, extent, upTag);
    }
    MPI_Send(data + offset, extent, MPI_DOUBLE, myProc + 1, 
	     upTag, MPI_COMM_WORLD);
    if(debug) {
      for(int i = 0;i < extent;i++) {
	en("sent data%i = %g", i, *(data + offset + i));
      }
      en("done.");
    }
  }
}

void DataHolder::rcvOverlap() {
  MPI_Status s;
  ProcDomain* pd = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(myProc));
  CHECKDC(pd);
  int offset = 0;
  int extent = (pd->beginCol - pd->ghostLB)*rows->value;
  if(debug) {
    en("DataHolder::rcvOverlap() entry: offset = %d, extent = %d", 
	   offset, extent);
  }
  if(extent > 0) { // not on an edge
    if(debug) {
      en("%d rcving from %d", myProc, myProc - 1);
      en("offset = %d, extent = %d, tag = %d", offset, extent, upTag);
    }
    MPI_Recv(data + offset, extent, MPI_DOUBLE, myProc - 1, 
	     upTag, MPI_COMM_WORLD, &s);
    if(debug) {
      for(int i = 0;i < extent;i++) {
	en("rcv'd data%i = %g", i, *(data + offset + i));
      }
    en("done.");
    }
  }
  pd = dynamic_cast<ProcDomain*>(partitionInfo->elementAt(myProc));
  CHECKDC(pd);
  offset = (pd->endCol - pd->ghostLB)*rows->value;
  extent = (pd->ghostUB - pd->endCol)*rows->value;
  if(debug) {
    en("DataHolder::rcvOverlap() 2nd receive: offset = %d, extent = %d", 
	   offset, extent);
  }
  if(extent > 0) { // not on an edge
    if(debug) {
      en("%d rcving from %d", myProc, myProc + 1);
      en("offset = %d, extent = %d, tag = %d", offset, extent, downTag);
    }
    MPI_Recv(data + offset, extent, MPI_DOUBLE, myProc + 1, 
	     downTag, MPI_COMM_WORLD, &s);
    if(debug) {
      for(int i = 0;i < extent;i++) {
	en("rcv'd data%i = %g", i, *(data + offset + i));
      }
      en("done.");
    }
  }
}

#else //_CCAMPI
void sendOddToEven(){}
void sendEvenToOdd(){}
void sendOverlap(){}
void rcvOverlap(){}

#endif // _CCAMPI

void DataHolder::dumpData() {
  en("dumping all the data:");
  for(int i = 0;i < size;i++) {
    en("data%d = %g", i, data[i]);
  }
}

void DataHolder::releaseBlock(CCA_Block** b) {
  // Who cares?
}

/** A compromise solution to the Data Holder debug output wars. */
void DataHolder::en(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  IO::errn(fmt, ap);
  va_end(ap);
}

void DataHolder::e(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  IO::err(fmt, ap);
  va_end(ap);
}
