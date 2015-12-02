#ifndef __DATAHOLDER_H__
#define __DATAHOLDER_H__
//#ifdef _CCAMPI

/**
 * NOTE: no serial implementation of this exists, so the whole
 * file disappears unless mpi is present
 **/

/* #include <stdlib.h> */
/* #include "jc++/jc++.h" */
/* #include "jc++/util/jc++util.h" */
/* #include <cca.h> */
/* #include "util/IO.h" */
/* #include "parameters/parametersStar.h" */
/* #include "port/portInterfaces.h" */
/* #include "port/supportInterfaces.h" */
/* #include "dc/port/portStar.h" */
/* #include "BasicShape.h" */

	  
/** Used specify ProcDomain instances completely. */
enum oneDDomainClass {
  oneD_NULL,
  oneD_LEFTSIDE,
  oneD_RIGHTSIDE,
  oneD_MIDDLE,
  oneD_ONEPROC
};

/* An JCPN(Object) that can contain something who's value can be compared. */
class EqObject : public JCPN(Object) {
public:
  virtual ~EqObject() {}
  virtual boolean equals(EqObject* o)=0;
};

/** A class to deal with JCPN(Object)s that represent non-objects, i.e. base
    types that can be known only by their values. */
class HashValue : public JCPN(Hashtable) {
private:
  /** Returns the key in the table that equals the given key. */
  EqObject* findKeyMatchEqualTo(EqObject* key) {
    JCPN(Enumeration)* e = keys();
    while(e->hasMoreElements()) {
      EqObject* k2 = dynamic_cast<EqObject*>(e->nextElement());
      if(k2->equals(key)) {
	delete e;
	return k2;
      }
    }
    return 0;
  }
  /** Returns the key in the table that equals the given key. */
  EqObject* findKeyMatchEqual(EqObject* key) {
    JCPN(Enumeration)* e = keys();
    while(e->hasMoreElements()) {
      EqObject* k2 = dynamic_cast<EqObject*>(e->nextElement());
      if(key->equals(k2)) {
	delete e;
	return k2;
      }
    }
    return 0;
  }
  /** Returns the key in the table that equals the given key. */
  EqObject* findKeyMatchEqualEqual(EqObject* key) {
    JCPN(Enumeration)* e = keys();
    while(e->hasMoreElements()) {
      EqObject* k2 = dynamic_cast<EqObject*>(e->nextElement());
      if(k2->equals(key) && key->equals(k2)) {
	delete e;
	return k2;
      }
    }
    return 0;
  }

public:
  HashValue() : JCPN(Hashtable)(){}
  virtual ~HashValue(){}
  
  JCPN(Object)* putEqualTo(EqObject* key, JCPN(Object)* value) {
    EqObject* kInHash = findKeyMatchEqualTo(key);
    if(kInHash != 0) {
      put(key, value);
      return remove(kInHash);
    } else {
      put(key, value);
      return 0;
    }
  }
  /** The first candidate that is equal to the calling argument is
      returned. */
  JCPN(Object)* getEqualTo(EqObject* key) {
    EqObject* k2 = findKeyMatchEqualTo(key);
    if(k2 != 0) {
      return get(k2);
    } else {
      return 0;
    }
  }
  JCPN(Object)* putEqual(EqObject* key, JCPN(Object)* value) {
    EqObject* kInHash = findKeyMatchEqual(key);
    if(kInHash != 0) {
      put(key, value);
      return remove(kInHash);
    } else {
      put(key, value);
      return 0;
    }
  }
  /** The first candidate that the calling argument thinks is equal is
      returned. */
  JCPN(Object)* getEqual(EqObject* key) {
    EqObject* k2 = findKeyMatchEqual(key);
    if(k2 != 0) {
      return get(k2);
    } else {
      return 0;
    }
  }
  JCPN(Object)* putEqualEqual(EqObject* key, JCPN(Object)* value) {
    EqObject* kInHash = findKeyMatchEqualEqual(key);
    if(kInHash != 0) {
      put(key, value);
      return remove(kInHash);
    } else {
      put(key, value);
      return 0;
    }
  }
  /*** Both EqObject's have to agree that they are equal before a
       candidate is returned. */
  JCPN(Object)* getEqualEqual(EqObject* key) {
    EqObject* k2 = findKeyMatchEqualEqual(key);
    if(k2 != 0) {
      return get(k2);
    } else {
      return 0;
    }
  }
};

/** A class to deal with JCPN(Object)s that represent scalars, i.e. base
    types that can be known only by their values. */
class VectorValue : public JCPN(Vector) {
public:
  VectorValue() : JCPN(Vector)(){}
  virtual ~VectorValue(){}
  /** The first candidate that is equal to the calling argument is
      returned. */
  EqObject* getEqualTo(EqObject* o) {
    JCPN(Enumeration)* e = elements();
    while(e->hasMoreElements()) {
      EqObject* o2 = dynamic_cast<EqObject*>(e->nextElement());
      if(o2->equals(o)) {
	delete e;
	return o2;
      }
    }
    delete e;
    return 0;
  }
  /** The first candidate that the calling argument thinks is equal is
      returned. */
  EqObject* getEqual(EqObject* o) {
    JCPN(Enumeration)* e = elements();
    while(e->hasMoreElements()) {
      EqObject* o2 = dynamic_cast<EqObject*>(e->nextElement());
      if(o->equals(o2)) {
	delete e;
	return o2;
      }
    }
    delete e;
    return 0;
  }
  /** Both EqObject's have to agree that they are equal before a
       candidate is returned. */
  EqObject* getEqualEqual(EqObject* o) {
    JCPN(Enumeration)* e = elements();
    while(e->hasMoreElements()) {
      EqObject* o2 = dynamic_cast<EqObject*>(e->nextElement());
      if(o->equals(o2) && o2->equals(o)) {
	delete e;
	return o2;
      }
    }
    delete e;
    return 0;
  }
};

/** ReferenceObject is a container for void pointers. */
class ReferenceObject : public virtual EqObject {
private: 
  void* reference;
public:
  ReferenceObject(void* reference) {
    this->reference = reference;
  }
  virtual ~ReferenceObject(){}
  virtual boolean equals(EqObject* o) {
    ReferenceObject* ro = dynamic_cast<ReferenceObject*>(o);
    if(ro == 0) { return FALSE; }
    if(reference == ro->reference) {
      return TRUE;
    } else {
      return FALSE;
    }
  }
};  

/** A wrapper for simple description of the domain on a single Proc. */
class ProcDomain : public JCPN(Object) {
public:
  ProcDomain() : JCPN(Object)() {
    type = oneD_NULL;
  }
  virtual ~ProcDomain(){}
  int beginCol;
  int endCol;
  int ghostLB;
  int ghostUB;
  int overlapLB;
  int overlapUB;
  oneDDomainClass type;
};

class CmptInfo : public JCPN(Object) {
private:
  CCA_Block** b;
  Shape* shape;
public:
  /** Create with a block that we are interested in. */
  CmptInfo(CCA_Block** b);
  virtual ~CmptInfo();
  CCA_Block** getBlock();
  void setShape(CDELETE Shape* s);
  Shape* getShape();
};
  

/** Uses a one-dimensional decomposition. A picture identifying the
different pieces follows.  Overlap is defined as the portion of a
block that a neighbor needs. Ghosts are defined as the portion of a
block that has been rendered stale by a neighbor.  The rest of the
block is local to the processor and does not need to be touched.


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
class DataHolder : public virtual BlockPort, public virtual gov::cca::Component         {
private:
  /** Information on what processor has what block. */
  JCPN(Vector)* partitionInfo;
  /** number of rows of data. */
  IntParameter* rows; 
  /** number of columns of data. */
  IntParameter* cols; 
  /** number of participating processors */
  int numProcs; 
  /** i.e. MPI rank */
  int myProc; 
  /** the local raw data block. */
  double* data; 
  /** size of data (# of doubles). */
  int size; 
  /** upwind sending tag. */
  int upTag; 
  /** downwind sending tag. */
  int downTag; 
  /** true if we have already created the data. */
  boolean dataCreated; 
  /** debug flag for lots of printing. */
  boolean debug; 
  /** Components talking to this DataHolder */
  HashValue* blockPtr;
  CCA_Block* myDataBlock;
  ConfigurableParameterPort* pp;
  gov::cca::Services* svc;


  /** Create the partitioning scheme that is the same on every processor */
  void createPartition();
  void setupBlock(ProcDomain* pd);
  /** Checks to see if the partitioning is sane. */
  boolean sanityCheck();
  void dumpData();
  void init();
  void sendOddToEven();
  void sendEvenToOdd();
  void sendOverlap();
  void rcvOverlap();
  void registerCmpt(CCA_Block** b);

public:
  DataHolder();

  virtual ~DataHolder();

  /** Set true for lots of possibly helpful debug info. */
  void setDebug(boolean tf);

  /** Fullfill the Component interface. */
  virtual void setServices(gov::cca::Services* svc);

  /** Get the data in this DataHolder associated with the name */
  double* getData(CCA_Block** b,
		  int& offset, 
		  int& beginRow, 
		  int& endRow, 
		  int& beginCol,
		  int& endCol);

  /** Shape tells the DataHolder what overlap and ghost data is needed
      required by the calling component, Name is the unique identifier
      for the caller. */
  void setShape(Shape *s, CCA_Block** b);

  /** Get the data in this DataHolder associated with the name */
  double* getData(char* name, 
		  int& offset, 
		  int& beginRow, 
		  int& endRow, 
		  int& beginCol,
		  int& endCol);
  // Implements BlockPort:

  /** Freshens any ghosts that have become dirty. */
  virtual void update();

  /** Does nothing. */
  virtual void compute();

  /** A method Rob is using under duress. The radius is the distance
      in any dimension that contains all the dependencies necessary
      to advance the solution for the block of data returned by
      getBlock().  The update() method will make sure that the ghost
      and overlap cells are freshened from the adjoining
      processors.*/
  virtual void setOverlapUniform(int radius, CCA_Block **b);

  /** Return the block on this processor to the calling program. */
  virtual void getBlock(CCA_Block **b);

  /** Signal that the component is done using the block. */
  virtual void releaseBlock(CCA_Block** b);

private:

/** A compromise solution to the Data Holder debug output wars; you
    can put whatever output style you like in this function. */
  void en(const char* fmt, ...);
/** A compromise solution to the Data Holder debug output wars; you
    can put whatever output style you like in this function. */
  void e(const char* fmt, ...);
  

/*   class ESI_MapAlgebraic_Port : public virtual SNL_Map, public virtual gov::cca::Port { */
/*   public: */
/*     ESI_MapAlgebraic_Port() : SNL_Map() {} */
/*     virtual ~ESI_MapAlgebraic_Port(){} */
/*   }; */
  /** A map that has the same rank as all the data in this DataHolder
   and the same processor decomposition. */
  //  ESI_MapAlgebraic_Port* map; 
};

//#else // _CCAMPI
// serial implementation
//#endif // _CCAMPI
#endif // __DATAHOLDER_H__
