#define speculation_rampant 1
#if speculation_rampant
/** Here we have a collection of interfaces designed to capture, or
 *  at least be compatible with, components doing the following tasks
 *  scalably:
 *  <ol>
 *  <li> Move a global set of field data size P from M processors to 
 *       N processors, with arbitrary but globally known parallel 
 *       decompositions.
 *  <li> Migrate data among processors in response to a new decomposition
 *       specification.
 *  <li> Map data locally from one field to another, using an arbitrary
 *       convolution function.
 *  <li> Describe a field variable in sufficient physical detail to allow
 *       reliable conversion to appropriate units.
 *  <li> Bake apple pies.
 *  </ol>
 * </p>
 * <p>This might restated as "We are working in a larger context where
 *    we expect to define interfaces and/or components which handle
 *    four distinguishable tasks:"
 *  <ol><li>In-core storage, retrieval, description, and introspection 
 *          of parallel data.
 *   <li>Computation of a new data distribution for load balance purposes,
 *       given architecture, performance information, and a minimalist
 *       description of the data.
 *   <li>Motion of distributed data among processors, given a description
 *       of the current and desired distributions and of the data.
 *   <li>Mapping (convolution, transformation) of data from one object
 *       into another (one-off and periodically), given the data.
 *   </ol>
 * </p><p>It is desired to make these tasks and interfaces as orthogonal
 *     as practical, but not more so. Unfortunately, motion and mapping
 *     seem to inevitably get tangled up in discussions. 
 *     A self-consistent, implementable set of *interfaces* covering 
 *     this design space is sought, so that the various factions can
 *     compete on performance and features rather than on how things
 *     are named.
 * </p><p>
 *  The evergrowing list of
 *  Authors: 
 *  Jim Kohl, Ben Allan,
 *
 * </p>
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
class MultiplicativeUnit;
class NonmultiplicativeUnit;
class Dimensions;

/**
Round 1:
    This interface abstracts the mapping
    operation (copy) from one field to another.

Round 2:
    Or maybe it does something else. it's all
    too illdefined to tell at this point.
    So wait a minute, isn't this getDataField the
    same as convolve() in Convolution? With the
    addition that there are only changes in
    distribution (none in global semantics)?

 */
class CollectivePort : Port { /* clientport */
public:
    /** Hook up this data field, meaning the collective port keeps the 
        pointer we're passing.
        Why do we have to add and remove if we're passing both into
        the get operation anyway? avoiding redundant overhead?
     */
    virtual void addDataField(DataField *field ) = 0; 

    /** unhook this data field, meaning the collective port releases 
        the pointer we're passing, after making sure it had it. 
    */
    virtual void removeDataField(DataField *field ) = 0;

    /** Copy one datafield to the other.
        This a BLOCKING, COLLECTIVE call.
        All the overhead computations that manage communication
        are discarded at the end of the call.
        @param dst_field is our data, being copied into.
        @param src_field is someone elses data field,
         or a proxy for it that was supplied from elsewhere,
         in the MxN case. 
     */
    virtual void getDataField(DataField *dst_field, DataField *src_field ) = 0;
};

/**
 * <p>
 * O.K., so Jim discussed this with the LANL folks on Friday
 * afternoon.  There are a few more things that need to go
 * along with the getDataField() method to complete the set.
 * </p>
 * <p>
 * Another method that needs to be added is for "persistent" data
 * connections, something like:
 * </p>
 * <pre>
 *         void coupleDataFields(
 *                 in DataField *dst_field, in DataField *src_field,
 *                 in Time frequency, in int sync_flag,
 *                 in int static_flag );
 * </pre>
 * <p>
 * The idea here is way-cool - you set up a persistent connection
 * between the 2 parallel components, so that whenever the
 * DataField.setReady() method is called (locally by each parallel
 * task), then each respective piece of the distributed data field
 * will be either collected from the source or deposited into the
 * destination data field storage.
 * </p>
 * <p>
 * Note that this means setReady() is called at both ends of the
 * connection, so when src_field.setReady() is called the data
 * can be extracted, and when dst_field.setReady() is called the
 * munged data can be deposited.
 * </p>
 * <p>
 * Behaviorally, this is rather complex. Probably need more
 * functions to complete this interface.
 * </p>
 */
class CouplingPort : Port {

    /** set up a persistent connection. Should we move some of
        these arguments into separate set functions?
        Is this in fact another peculiar convolution -- guess not.
     */
    virtual void coupleDataFields( DataField *dst_field,  DataField *src_field, Time *frequency, int sync_flag, int static_flag ) = 0;

};

/**
 * <p>
 * This is needed by a Puller needs who wants to pick from a 
 * list of src_fields before a getDataField calls.
 * </p><p>
 * The simpler case, which doesn't require this interface, is
 * for a component using CollectivePort to simply be wired to the 
 * proxy DataField *src_field Port directly. It would be a Collective
 * component that provides such a proxy port, one for each field
 * that gets added to it.
 * </p><p>
 * Probably there are other functions that we might want to have
 * when introspecting a Collective component via the CollectiveManager
 * interface, such as what the total logical process(or) space
 * the component spans. This could be independent of all the
 * individual DataFields the Collective component knows about.
 * Might want to know the total buffer overhead the collective
 * is sucking up as well, for example.
 * </p>
 */
class CollectiveManager : Port {
  
  /** return a list of references to DataFields the collective
      component knows about. The contents of the list will vary
      (what is proxy buffer vs what is a pointer to the real
       DataField) depending on which process the call is made in.
      The length of the list should be the same on all processes,
      unless there are synchronization problems.
  */
  virtual void *getDataFields(DataField *&, int & length) = 0;
  
};

/**
 *  DataField encodes Space & Time Information and may be in some
 *  sort of distributed memory. 
 * Should we split DataField into two kinds of interface:
 * DataField and DataFieldNonblocking? They do behave a fair
 * bit differently. DataFieldNonblocking might derive from DataField
 * or not.
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
        @param unitScale is the scale of units, eg "meters", "kg"
        @param unitPrefix is the SI prefix eg "pico", "deca", "tera"
     */
    virtual void setUnits(char *unitScale, char *unitPrefix ) = 0; 

    /** Describe the regular grid type eg "rectangular", "spectral"
      @param gridType is copied, not kept.
     */
    virtual void setGridType(char *gridType ) = 0;

    /** Set current simulation time for data field.
     */
    virtual void setTime(Time *time ) = 0; 

    /**  simulated time per iteration. 
     */
    virtual void setPeriod(Time *period ) = 0; 

    /** We have a whole bunch of merely nouns, then suddenly a verb.
        data field is ready for collection, just in case anyone has
        or soon will call getDataField.
        This is a BLOCKING call. Is this a COLLECTIVE call?
       @param incrTime Increment field time (by period) or not.
     */
    virtual void setReady(boolean incrTime ) = 0;

    /** So the idea here is that there are two ways to call setReady(),
       "block until everyone has been serviced"  or "my data
       field is ready to be read/written now, so do it at your leisure"
       setReadyNonblocking();.

       In the nonblocking case what you're really doing is
       setting up for an asynchronous connection, so like if you know
       the data is ready to be accessed for a while, you can let everyone
       else know it and they can come get it when they need it, etc.

       Clearly, you need another method:

               void waitData();

       which you can call later to make sure that everybody has serviced
       their requests before you go forward to read or scribble on your
       DataField again...

       @param incrTime Increment field time (by period) or not.
     */
    virtual void setReadyNonblocking(boolean incrTime ) = 0;

    /** the other half of setReadyNonblocking. */
    void waitData();
};

/**
 * <p>
 * Don't we need some get functions for DataField, too?
 * Probably should add a DataFieldQuery *getFieldInfo() method
 * to DataField interface so that we don't overwhelm the poor
 * guy who just wants to use this interface. DataFieldQuery
 * would define all the get methods needed on DataField.
 * </p><p>
 * Of course if the mxn component is also the datafield
 * factory, then we don't need get functions for the mxn to use.
 * We would still need get functions to support other convolutions,
 * however.
 * </p>
 * Probably should say more here about what not to do with
 * the answers from the queries.
 */
class DataFieldQuery {
  /** inverse setUnits. */
  void getUnits(Unit * & u);
  /** inverse setTime. */
  void getTime(Time * & t);
  /** inverse setGridType. */
  char *getGridType();
  /** inverse setProcArray. */
  void getProcArray(ProcArray * & pa);
};

//=================================================================

/** A container for any kind of data pointer.
 * Don't we need some get functions for this, too?
 */
class Data : Port {
public:
    /** pointer to actual data storage, which is kept. Should probably
        combine this call and setType(). 
       @param dataType must be one of a known set of choices.
        Don't know what these are. Probably 
           int, long, long long, 
           float, double, long double, quad
           fcomplex, dcomplex, ldcomplex, qcomplex.
        In effect, the string is copied, not kept.
     */
    virtual void setData(void *dataPtr, char *dataType  ) = 0;

    /** Dimensionality of the array dataptr, which has nothing to
        do with the geometry it represents in the 1-D case.
        @param nDimensions - number of dimensions in data array. For
               unstructured data, it is 1.
        @param dataSize[i] where i=0..nDimensions-1, is the
               cardinality of axis i.
        @param layout If nDimensions > 1, then:
               layout = 1 -->
               array dataPtr is assumed to be laid out in the
               column major f77 style.
               layout = 2 -->
               array dataPtr is assumed to be laid out in the
               row major contiguous (transpose f77) style.
	       layout = 0 -->
               array dataPtr is assumed to be laid out C style,
               i.e. an array of pointers, not a pointer to contiguous
               memory.
        @return 0 if ok, -1 if there is an error in the arguments,
                possibly including a mismatch between nDimensions
                and the subtype of Data (structured, unstructured...)
     */
    virtual int setSize(int nDimensions, int *dataSize, int layout) = 0;
};

/** Data specialized to irregular geometries using a representation
 *  that would be grossly inefficient for the RectangularData case. 
 * Don't we need some get functions for this, too? In this interface
 * or elsewhere?
 * Probably want additional definition functions.
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
    
    /** Identify the ghost items (items not locally owned) in the
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
 *   overlaps = a+c; // This is too restrictive to capture
 *                   // unstructured mesh decomps. See UnstructureData.
 * </pre>
 * This local data is related to some logically global data
 * and topology by the Decomposition.
 * Don't we need some get functions for this, too? In this interface
 * or elsewhere?
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
 * Can we handle degenerate x-tangles, e.g. a 2d slice of a 3d array?
 * Don't we need some get functinos for this, too? In this interface
 * or elsewhere?
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
    virtual void setDecompAxis(int axisIndex, RectangularInfo * info ) = 0; 
};

/** Describe the properties of a RectangularDecomposition.
    Don't we need some get functions, too? */
class RectangularInfo {
public:
    /** eg "Block", "Cyclic" 
      Arg is copied, rather than caching the pointer.
     */
    virtual void setDecompType( char * decompType ) = 0;

    /** eg "Block Size", "10"
        Args are copied, rather than caching the pointers.
     */ 
    virtual void setDecompProperty(char * name, char * value ) = 0;

    /** 
     * This thingy is used for "explicit" data decompositions, i.e. ones
     * that won't fit into "standard" block/cyclic definitions.  If I'm
     * a component that stores several random sub-arrays of some big global
     * array, I can set the bounds along each axis for each sub-array:
     * <pre>
     *    Global array is Foo[100][100][100];
     *    I have Foo[10:20][20:30][30:40] and Foo[71:73][50:90][80:99]
     *    So I describe these regions via:
     *          XInfo->addBounds( 2, { 10, 71 }, { 20, 73 } );
     *          YInfo->addBounds( 2, { 20, 50 }, { 30, 90 } );
     *          ZInfo->addBounds( 2, { 30, 80 }, { 40, 99 } );
     * Those bounds define the global context of the two sub-array regions
     * stored locally.
     * </pre>
     * @param numBounds is the # of explicit region bounds and
     *       the size of lowerBounds and upperBounds arrays.
     */
    virtual void addBounds(int numBounds, int * lowerBounds, int * upperBounds ) = 0;
};

/** <p>
 * The idea here is that setProcShape() defines the process topology,
 * and setProcAddress() is a local call which says where
 * the caller/this object resides in the given process topology.
 * </p><p>
 *  E.g., if there are 6 processes in a 2x3 array, and I'm the instance
 *  that has the decomposition for row 1 and column 2, my ProcAddress
 *  would be { 0, 1 } out of ProcShape { 2, 3 }.
 * </p><p>
 * Maybe setProcIndex() would be a better name?
 * </p>
 *  Don't we need some get functions, too? In this interface
 *  or a separate one?
 */
class ProcArray : Port {
public:
    /** Define what the world is.
       @param procDim dim of process array, number of axes.
       @param procShape[i] processes in axis i. Copied, rather 
              than caching the pointer.
     */
    virtual void setProcShape(int procDim, int * procShape ) = 0; 

    /** define where our process is.
     @param procDim is size of the array procAddress.
     */
    virtual void setProcAddress(int procDim, int * procAddress ) = 0;
};

//===============================================================

/** Generic convolution interfaces that do global operations.
    We could use the units defined at bottom of file instead
    of arbitrary scale strings and standard scaling prefix strings,
    if we want to support arbitrary conversions like Celsius.
  */
class Convolution : Port {
public:

    /** Map from srcField to dstField, overwriting dstField.
        This is a collective call, usually. */
    virtual void convolve(DataField *dstField, DataField *srcField) = 0;
};

/** Describe the simulation time. Could use a timeValue and Unit as below
    instead.
    Don't we need some get functions, too? In this interface
    or a separate one?
 */
class Time {
public:
    /** set the time (locally) in the simulation.
       @param timeUnitPrefix eg "pico", "giga". Agents interacting
              with this Time are expected to know what magnitudes
              the SI prefixes are, even if they don't "know"
              the base timeUnitScale.
       @param timeUnitScale eg "seconds", "minutes"
     */
    virtual void setTime(float timeValue, char * timeUnitScale, char * timeUnitPrefix ) = 0;

    /** Bump the time by the value given in the units given,
        and do the right thing even if the clock is in a different 
        timeUnitPrefix.
        @param increment time value?? or is the increment the period?
     */
    virtual void incrTime(float timeValue, char * timeUnitScale, char * timeUnitPrefix ) = 0;

};

/** We pass around one or more convolutions, rather than a function pointer.  
 */
class TimeInterpolant : Convolution {
public:
    /** map from TimeQueue and srcField to dstField, overwriting dstField. */
    virtual void convolve(DataField *dstField, DataField *srcField ) = 0;

    /** Configure time slices. */
    virtual void setTimeQueue(TimeQueue *q) = 0;
};

/** We pass around one or more Convolutions, rather than a function pointer. */
class SpaceInterpolant : Convolution {
public:
    /** map from srcField to dstField with some geometric tricks,
        overwriting dstField. */
    virtual void convolve(DataField *dstField, DataField *srcField ) = 0;
    virtual void setGridTypes( char * dstGridType, char * srcGridType) = 0;
};

/** We need some get functions here, in order to implement TimeInterpolant.
 * circular buffer
 */
class TimeQueue : Port { 
public:
    /** @param queue_size Number of field instances to keep. */
    virtual void setTimeQueueLength( int queue_size) = 0;

    /** Pop new instance on top of queue. What happens to the
        one bumped off, if anything? Should we return its pointer?
     */
    virtual void addDataFieldToQueue( DataField *srcField ) = 0;
};

/** mindnumbing scaling computation example.
 */ 
class Convert : Convolution {
public:
    virtual void convolve(DataField *dstField, DataField *srcField) = 0;
    /** returns 0 if ok, 1 if conversion is impossible. */
    virtual int setConversionFactor(Unit *dstUnits, Unit *srcUnits) = 0;
};

//===============================================================

/** A simple, semantically checkable unit representation.
    Functions for an arithmetic of units could be added.
    Don't even think of using silly units like Celsius and
    Farenheit. 
    This includes any conversion, even demented things like
    Farenheit to Celsius conversions.
 */
class Unit {
public:
    /** eg "pascal" */
    virtual char *getName() = 0;

    /** return the fundamentals */
    virtual Dimensions *getDimensions() = 0;

    /** Return the corresponding SI unit and value. This lets us
        map every unit conversion, no matter how bizarre (Farenheit???)
        via an SI intermediate.
        @param value - the value (in units of getName() to be converted to SI.
        @param si - an output, the equivalent SI unit.
        @param SIvalue - an output, the value converted to SI.
     */
    virtual void getSIUnitValue(double value, Unit * & si, double & SIvalue) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValue(double SIvalue, double & value) = 0;

};

/** A simple, semantically checkable unit representation.
    Functions for an arithmetic of MultiplicativeUnits could be added.
    This covers any unit that is a conversion by multiplication
    from the SI units.  The eg throughout is for a pressure example. */
class MultiplicativeUnit {
public:
    /** eg "pascal" */
    virtual char *getName() = 0;

    /** return the fundamentals */
    virtual Dimensions *getDimensions() = 0;

    /** Return the corresponding SI unit and value.
        @param value - the value (in units of getName() to be converted to SI.
        @param si - an output, the equivalent SI unit.
        @param SIvalue - the value converted to SI.
     */
    virtual void getSIUnitValue(double value, Unit * & si, double & SIvalue) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValue(double SIvalue, double & value) = 0;

    /** eg "kg/m/s^2".
        Could be implemented as 
        Unit *si; double dummy;
        getSIUnitValue(1,si,dummy);
        si->getName();
        but is more easily implemented using Dimensions directly.
      */
    virtual char *getSIUnitName() = 0;

    /** eg 1.0. 
        double cf = getSIConversionFactor();
        is equivalent to
        Unit *si; double cf;
        getSIUnitValue(1, si, cf);
        Another example: unit with name "millimeter" --> cf = 0.001;
        @return the scaling factor needed to bring a value
        in units of getName() to SI units.
      */
    virtual double getSIConversionFactor() = 0;

    /** eg double cf;
             int err = u.getConversionFactor("kPa",cf);
          -->   cf = 0.001 && err = 0;
        while int err = u.getConversionFactor("ftLbs",cf);
          --> cf undefined and err = 1;
       @param cf The value to multiply a number in units of
                 getName() by to get a number in units of
                 newMultiplicativeUnitString.
       @param newMultiplicativeUnitString A string containing
              an expression in terms existing multiplicative
              unit names. The implies the existence of a
              central piece of implementation that knows
              all the multiplicative names, sigh.
     */
    virtual int getConversionFactor(char *newMultiplicativeUnitString, double &cf) = 0;
};

/** A messy, semantically checkable unit representation.
    Functions for an arithmetic of NonmultiplicativeUnits would
    be insanely hard to add.
    This covers any unit that is NOT a conversion by multiplication
    from the SI units.
 */
class NonmultiplicativeUnit {
public:

    /** eg "Fahrenheit" */
    virtual char *getName() = 0;

    /** return the fundamental dimensions. */
    virtual Dimensions *getDimensions() = 0;

    /** Return the corresponding SI unit and value. This lets us
     *  map every unit conversion, no matter how bizarre (Farenheit???)
     *  via an SI intermediate.
     *  @param value - the value (in units of getName() to be converted to SI.
     *  @param si - an output, the equivalent SI unit.
     *  @param SIvalue - the value converted to SI.
     */
    virtual void getSIUnitValue(double value, Unit * & si, double & SIvalue) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValue(double SIvalue, double & value) = 0;

};


/** The core of any sane units conversion implementation.
  * To cover sensible physical and economic systems there are
  * 7 SI defined dimensions, 2 supplementary dimensions, and
  * the human dimension. String theory may suggest a few more
  * dimensions, but those aren't directly sensible (yet).
  * <pre>
  * We suggest using an array of ints (could be shorts)
  * indexed like so:
  *       (description)                     (type)         (index)
  * index for mass dimension.               MASS               = 0;
  * index for quantity dimension, eg. mole. QUANTITY           = 1;
  * index for distance dimension.           LENGTH             = 2;
  * index for time (4th) dimension.         TIME               = 3; 
  * index for temperature dimension.        TEMPERATURE        = 4;
  * index for the human value dimension.    CURRENCY           = 5;
  * index for electric current dimension.   ELECTRIC_CURRENT   = 6;
  * index for luminous intensity dimension. LUMINOUS_INTENSITY = 7;
  * index for plane angle dimension.        PLANE_ANGLE        = 8;
  * index for solid angle dimension.        SOLID_ANGLE        = 9; 
  * </pre>
  *   This may be controversial, as some purists insist
  *   that the angle types are DIMENSIONLESS. For practical
  *   purposes, we do want to convert safe from degrees to
  *   radians to grad. Applications can always choose to
  *   describe angle data as DIMENSIONLESS and take their
  *   chances. Scientists may have no values with money,
  *   but engineers certainly do.
  */
class Dimensions {
public:
  /** The exponents that define this dimensionality. E.g. 
   *  MASS/DISTANCE/TIME^2 -->
   *  "kg/m/s^2" --> 
   *  short[10] = {1,0,-1,-2,0,0,0,0,0,0};
   *  @return An array of shorts numDimensions long.
   */
  virtual short *getExponents() = 0;

  /** @return the SI units for this dimensionality, eg "kg/m/s^2" */
  virtual const char *getSIUnits() = 0;


  // generic functions for describing this dimension scheme.
  /**  
      @return Number of dimensions in our ontology, 10.
   */
  virtual int getNumDimensions() = 0;

  /** Map the exponents to convenient strings. 
      int dim = 0..getNumDimensions().
   */
  virtual const char *getDimensionType(int d) = 0;

  /** map DimensionName to number. Handy for parsers. */
  virtual const char *getDimensionNumber(char *dimensionName) = 0;

  /** Return a string with the SI unit name associated with the
      dimension. */
  virtual const char *getDimensionSIUnitName(int dimensionNumber) = 0;

};

#endif // speculation_rampant
