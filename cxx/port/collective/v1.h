#if speculation_rampant
/** Here we have a collection of interfaces designed to capture, or
 *  at least be compatible with, components doing the following tasks
 *  scalably:
 *  <ol>
 *  <li> Move a global set of field data size P from M processors to N processors,
 *       with arbitrary but globally known parallel decompositions.
 *  <li> Migrate data among processors in response to a new decomposition
 *       specification.
 *  <li> Map data locally from one field to another, using an arbitrary
 *       convolution function.
 *  <li> Describe a field variable in sufficient physical detail to allow
 *       reliable scaling to appropriate units.
 *  <li> Bake apple pies.
 *  </ol>
 *  The evergrowing list of
 *  Authors: 
 *  Jim Kohl, Ben Allan,
 *
 */
#define COLLECTIVE_PORT_STRAWMAN 1

class CollectivePort;
class DataField;
class Data;
class UnstructuredData;
class RectangularData;
class RectangularDecomposition;
class RectangularInfo ;
class ProcArray;
class Time;
class Convolution;
class TimeInterpolant;
class SpaceInterpolant;
class TimeQueue;
class Convert;
class Unit;
class Dimensions;

/**
    This interface abstracts the mapping
    operation (copy) from one field to another.
 */
class CollectivePort : Port {
public:
    /** hook up this data field, meaning the collective port keeps the 
        pointer we're passing.
        Why do we have to add and remove if we're passing both into
        the get operation anyway? avoiding redundant overhead?
          Is this a COLLECTIVE call?
     */
    virtual void addDataField(DataField *field ) = 0; 

    /** unhook this data field, meaning the collective port releases 
        the pointer we're passing, after making sure it had it. 
    */
    virtual void removeDataField(DataField *field ) = 0;

    /** Copy one datafield to the other.
        Is this a BLOCKING call?
          Is this a COLLECTIVE call?
        @param dst_field is our data, being copied into.
        @param src_field is someone elses data field. 
     */
    virtual void getDataField(DataField *dst_field, in DataField src_field ) = 0;
};

/**
  DataField encodes Space & Time Information and may be in some
  sort of distributed memory. 
 * Don't we need some get functions for this, too?
 */
class DataField : Port {
public:
    /** Begin the incremental build of a field. 
          Is this a COLLECTIVE call?
       @param name, the logical name of data, is copied, the pointer is not kept.
       @param data, pointer which is kept in the DataField object.
       Data is presumed to encapsulate an array(or equivalent) of
       a single type (eg double) and kind (eg temperature).
       @status
       This interface makes it mighty inconvenient to describe
       and communicate about multi-field problems which store all
       the variables for a given node/element in a single struct ,
       but Jim says this is particles.  We might consider doing a
       similar interface for the MPI_Datatypes or some PVM equivalent,
       assuming that MPI_Alltoallv isn't already an MxN component if
       used correctly with MPI_Datatypes.

     */
    virtual void setField(char *string name, Data *data ) = 0;

    /** Define the process(es)(ors) holding the field. */
    virtual void setProcArray( ProcArray parray ) = 0;

    /** define the units that go on Data. Jim does this as a string;
        Ben and Tom would have it done *much* differently. The arguments
        are copied, not kept.
        @param unitScale is the scale of units, e.g. "meters", "kg"
        @param unitPrefix is the SI prefix e.g. "pico", "deca", "tera"
     */
    virtual void setUnits(char *unitScale, char *unitPrefix ) = 0; 

    /** Describe the regular grid type e.g. "rectangular", "spectral"
      @param gridType is copied, not kept.
     */
    virtual void setGrid(char *gridType ) = 0;

    /** Set current simulation time for data field.
     */
    virtual void setTime(Time time ) = 0; 

    /**  simulated time per iteration. 
     */
    virtual void setPeriod(Time period ) = 0; 

    /** We have a whole bunch of merely nouns, then suddenly a verb.
        data field is ready for collection, just in case anyone has
        or soon will call getDataField.
        Is this a COLLECTIVE call?
     */
    virtual void setReady( in boolean incrTime ) = 0; // increment field time (by period) or not
};

/** A container for any kind of data pointer.
 * Don't we need some get functions for this, too?
 */
class Data : Port {
public:
    /** pointer to actual data storage, which is kept. Should probably
        combine this call and setType(). */
    virtual void setData(void *dataPtr ) = 0;

    /** Type name of data; copied not kept.
       @param dataType must be one of a known set of choices.
        Don't know what these are. Probably 
           int, long, long long, 
           float, double, long double, quad
           fcomplex, dcomplex, ldcomplex, qcomplex.
     */
    virtual void setType(char *dataType ) = 0;

    /** Dimensionality of the array dataptr, which has nothing to
        do with the geometry it represents in the 1-D case.
        @param nDimensions - number of dimensions in data array. For
               unstructured data, it is 1.
        @param dataSize[i] where i=0..nDimensions-1, is the
               cardinality of axis i. If nDimensions > 1, the
               array dataPtr is assumed to be laid out in the
               f77 style.
        @return 0 if ok, -1 if there is an error in the arguments,
                possibly including a mismatch between nDimensions
                and the subtype of Data (structured, unstructured...)
     */
    virtual int setSize(int nDimensions, int *dataSize) = 0;
};

/** Data specialized to irregular geometries using a representation
    that would be grossly inefficient for the structured grid case. 
 * Don't we need some get functions for this, too?
 */
class UnstructuredData :  Data {
public:

    virtual void setData(void *dataPtr) = 0;
    virtual void setType(char *dataType) = 0;

    /** Inherited, with runtime enforced assumption that 
        nDimensions is 1.
        @return 0 if ok, -1 if there is an error in the arguments,
                possibly including a mismatch between nDimensions
                and the subtype of Data (structured, unstructured...)
     */
    virtual int setSize(int nDimensions, int *dataSize) = 0;
    
    /** Identify the ghost items (not locally owned) in the
        dataPtr array. Each item is identified by its offset
        from the beginning of dataPtr.
        @param nGhostValues is the number of nonlocal values.
        @param ghostOffset[i] is the offset of a ghost, where
           0<= i < nGhostValues. */
    virtual void setGhostList(int nGhostValues, int *ghostOffset) = 0;
    
};

/** Data specialized to geometries which match the topology of the
 *  fortran array defined with setSize(), allowing for overlaps.
 *  On the local data, each axis i of the array is laid out so:
 * <pre>
 *    |---- a ---|----------------------- b ----------------|-- c ---|
 *   dataSize[i] = a + b + c;
 *   dataValidOffset[i] = a;
 *   dataValidSize[i] = b;
 *   overlaps = a+c; // This is too restrictive to capture unstructured mesh decomps.
 * </pre>
 * This local data is related to some logically global data
 * and topology by the Decomposition.
 * Don't we need some get functinos for this, too?
 */
class RectangularData : Data {

public:
    virtual void setData(void *dataPtr) = 0;
    virtual void setType(char *dataType) = 0;
    virtual int setSize(int nDimensions, int *dataSize) = 0;

    /** Valid data on each axis, that is offset from the local origin of
        the data we 'own' in our rectangular region. 
        Array is copied, rather than caching the pointers.
        @param dataValidOffset[i] is the offset in dimension i where
             0 <= i < nDimensions. dataOffset is copied, not kept as a pointer.
        @param nDimensions: input.
    */
    virtual void setValidOffset(int nDimensions, int *dataValidOffset) = 0; 

    /**
        Array is copied, rather than caching the pointers.
         @param dataValidSize - locally owned length on each axis.
    */
    virtual void setValidSize(int nDimensions, int *dataValidSize ) = 0;

    /**
      define the global parallel processing map for this Data.
      The pointer is kept.
    */
    virtual void setDecomposition(RectangularDecomposition *decomp ) = 0; 
};

/** Describe the decomposition of data rectangles across processors. 
 * Don't we need some get functinos for this, too?
 */
class RectangularDecomposition : Port {
public:
    /** 
       @param dataDimGlobal partition count and dimension of globalLowerBounds, globalUpperBounds.
        Arrays are copied, rather than caching the pointers.
     */
    virtual void setDecompBounds(int dataDimGlobal, int * globalLowerBounds, int * globalUpperBounds) = 0;

    /** 
       @param axisIndex - index of axis x=0, y=1, z=2, etc.
     */
    virtual void setDecompAxis( int axisIndex, in RectangularInfo * info ) = 0; 
};

/** Describe the properties of a RectangularDecomposition.
    Don't we need some get functions, too? */
class RectangularInfo {
public:
    /** e.g. "Block", "Cyclic" 
        Arg is copied, rather than caching the pointer.
     */
    virtual void setDecompType( char * decompType ) = 0;

    /** e.g. "Block Size", "10"
        Args are copied, rather than caching the pointers.
    */ 
    virtual void setDecompProperty(char * name, char * value ) = 0;

    /** 
      @param numBounds is the # of explicit region bounds and
             the size of lowerBounds and upperBounds arrays.
      @param lowerBounds - don't know what the heck this is.
      @param upperBounds - don't know what the heck this is.
     */
    virtual void addBounds(int numBounds, int * lowerBounds, int * upperBounds ) = 0;
};

/** Have I totally misread this topology description? Can we  have a picture? .
    Don't we need some get functions, too?*/
class ProcArray : Port {
public:
    /** 
       @param procDim dim of process array, number of axes.
       @param procShape[i] processes in axis i. Copied, rather than caching the pointer.
     */
    virtual void setProcShape(int procDim, int * procShape ) = 0; 

    /** huh?
     @param procDim is size of the array procAddress.
     */
    virtual void setProcAddress(int procDim, int * procAddress ) = 0;
};

/** Generic convolution interface. */
class Convolution : Port {
public:

    /** map from srcField to dstField, overwriting dstField. */
    virtual void convolute(DataField *dstField, DataField *srcField) = 0;
};

/** Describe the simulation time..
    Don't we need some get functions, too? */
class Time {
public:
    /** set the time in the simulation. COLLECTIVE call?
       @param timeUnitPrefix e.g. "pico", "giga"
       @param timeUnitScale e.g. "seconds", "minutes"
     */
    virtual void setTime(float timeValue, char * timeUnitScale, char * timeUnitPrefix ) = 0;

    /** bump the clock by the value in the Data::setPeriod() call.
        @param increment time value?? or is the increment the period?
     */
    virtual void incrTime(float timeValue, char * timeUnitScale, char * timeUnitPrefix ) = 0;
};

/** We pass around one or more convolutions, rather than a function pointer. */
class TimeInterpolant : Convolution {
public:
    /** map from TimeQueue and srcField to dstField, overwriting dstField. */
    virtual void convolute(DataField *dstField, DataField *srcField ) = 0;
    virtual void setTimeQueue(TimeQueue *q) = 0;
};

/** We pass around one or more Convolutions, rather than a function pointer. */
class SpaceInterpolant : Convolution {
public:
    /** map from srcField to dstField with some geometric tricks, overwriting dstField. */
    virtual void convolute(DataField *dstField, DataField *srcField ) = 0;
    virtual void setGridTypes( char * dstGridType, char * srcGridType) = 0;
};

/** We need some get functions here, in order to implement TimeInterpolant. */
class TimeQueue : Port {    // circular buffer
public:
    virtual void setTimeQueueLength( int queue_size) = 0;
    virtual void addDataFieldToQueue( DataField *srcField ) = 0;
};

/** mindnumbing scaling computation example.
 */ 
class Convert : Convolution {
public:
    virtual void convolute(DataField *dstField, DataField *srcField) = 0;
    virtual void setConversionFactor(Unit *dstUnits, Unit *srcUnits) = 0;
};

/** A simple, semantically checkable unit representation.
    Functions for an arithmetic of units could be added.
    Don't even think of using silly units like Celsius and
    Farenheit. */
class Unit {
public:
    /** e.g. "pascal" */
    virtual char *getName() = 0;

    /** e.g. "kg/m/s^2" */
    virtual char *getSIName() = 0;

    /** e.g. 1.0 */
    virtual double getSIConversionFactor() = 0;

    /** e.g. double cf;
             int err = u.getConversionFactor("kPa",cf);
          -->   cf = 0.001 && err = 0;
        while int err = u.getConversionFactor("ftLbs",cf);
          --> cf undefined and err = 1;
     */
    virtual int getConversionFactor(char *newUnitString) = 0;

    /** return the fundamentals
    virtual Dimensions *getDimensions() = 0;
};

/** The core of any sane units conversion implementation. */
class Dimensions {
public:
    /** e.g. "kg/m/s^2" --> 
        MASS/DISTANCE/TIME^2 -->
        short[7] = {1,-1,0,0,0,0,-2};
     */
    short exponents[7];
};

#endif // speculation_rampant
