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
 * <p>CHANGES</P>
 * <p>9/11/2000: added error returns per David, Jim suggestion. Tightened
 *               definition of several calls. Combined setData and setUnits
 *               on DataField. Removed header questions that have been
 *               answered. Moved Unit conversion to a new ConvolveInPlace
 *               interface. Specified locality of convolutions.
 * </p>
 */
#define COLLECTIVE_PORT_STRAWMAN 1

class CollectivePort;
class CouplingPort;
class CollectiveManager;
class DataField;
class DataFieldQuery;
class Data;
class UnstructuredData;
class RectangularData;
class RectangularDecomposition;
class RectangularInfo ;
class ProcArray;
class Convolution;
class Time;
class TimeInterpolant;
class SpaceInterpolant;
class TimeQueue;
class ConvolutionInPlace;
class ConvertUnits;
class Unit;
class MultiplicativeUnit;
class NonmultiplicativeUnit;
class Dimensions;
class MeasuresFactory;


//=================================================================
/** Theoretically, an mxn data mover interface starting point.
 * <p>
 * Round 4:
 * </p><p>
 *     Incorporated comments for restrictions and error handling.
 *     This is distinctly an interface *Just* for redistributing
 *     data into an alternative memory distribution by network COPY,
 *     leaving the structures of both src and dst fields intact.
 *     As such, it is probably inappropriate for redistributing
 *     data for load balance purposes where no 2nd copy is desired.
 *     This is a one-off copy, where the full overhead of the
 *     transfer is incurred at every call.
 * </p>
 * <p>
 * Round 3:
 * </p><p>
 *     Throwing the whole out to the peanut gallery
 *     for correction and enlightenment.
 * </p>
 * <p>
 * Round 2:
 * </p><p>
 *     Or maybe it does something else. it's all
 *     too illdefined to tell at this point.
 *     So wait a minute, isn't this getDataField the
 *     same as convolve() in Convolution? With the
 *     addition that there are only changes in
 *     distribution (none in global semantics)?
 * </p>
 * <p>
 * Round 1:
 * </p><p>
 *     This interface abstracts the mapping
 *     operation (copy) from one field to another.
 * </p>
 * @see CouplingPort. For amortizing overhead of periodic MxN. 
 * @see Convolution. For local data transform from source to target.
 * @see ConvolutionInPlace. For data transform overwriting source.
 */
class CollectivePort : Port { /* clientport */
public:
    /** Hook up this data field, meaning the collective port keeps the 
        pointer we're passing in.
        Why do we have to add and remove if we're passing both into
        the get operation anyway? 
     */
    virtual void addDataField(DataField *field ) = 0; 

    /** Unhook this data field, meaning the collective port releases 
        the pointer we're passing, after making sure it had it. 
        @return 0 if ok, -1 if it doesn't have it.
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
        @return 0 if ok, -1 if fields are incompatible (grid size, units, type
         of grid) for the transfer, -2 if internal failure.
     */
    virtual int getDataField(DataField *dst_field, DataField *src_field ) = 0;
};

//=================================================================
/**
 * <p>Persistently coupled port, to amortize translation overheads.
 * O.K., so Jim discussed this with the LANL folks at the 8/2000 cca meeting.
 * There are a few more things that need to go
 * along with the getDataField() method to complete the set.
 * </p>
 * <p>
 * Another method that needs to be added is for "persistent" data
 * connections, something like:
 * </p>
 * <p>
 *         void coupleDataFields(
 *                 in DataField *dst_field, in DataField *src_field,
 *                 in Time frequency, in int sync_flag,
 *                 in int static_flag );
 * </p>
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

    /** Set up a persistent connection. Should we move some of
     *  these arguments into separate set functions?
     * @return 0 if ok, -1 if fields are incompatible (grid size, units, type
     *       of grid) for the transfer, -2 if internal failure.
     */
    virtual int coupleDataFields( DataField *dst_field,  DataField *src_field, Time *frequency, int sync_flag, int static_flag ) = 0;

};

//=================================================================
/**
 * <p>
 * This is needed by a Puller needs who wants to pick from a 
 * list of src_fields before creating dst_field and making a getDataField call.
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
  
  /** Return an array of references to DataFields the collective
      component knows about. The contents of the list will vary
      (what is proxy buffer vs what is a pointer to the real
       DataField) depending on which process the call is made in.
      The length of the list should be the same on all processes
      where this instance of the CollectiveManager exists,
      unless there are synchronization problems.
      @return The length may be 0 and the reference NULL if none exist.
  */
  virtual void getDataFields(DataField *&, int & length) = 0;
  
};

//=================================================================
//=================================================================
/**
 * <p> DataField encodes Space & Time dependent Information and may be in some
 *  sort of distributed memory. There is one Data per DataField.
 *  We separate data definition
 *  from the functions needed by the collective component to manipulate it.
 * </p>
 * <p> The DataField interface is for an application writer who wants to
 *     describe data to a CouplingPort/CollectivePort/etc.
 *     It is presumed the apps writer isn't going to need to ask
 *     back they told the DataField with set functions.
 * </p>
 * <p>
 *     The writer fetches a component implementing
 *     DataField from a FieldFactory of some sort and
 *     configures the datafield with the remaining information needed.
 *     The fetched component can then pop out a DataFieldQuery Port.
 *     The writer doesn't need to understand all the query
 *     functions -- they are there so that a Collective
 *     implementer can manipulate the data as needed.
 * </p>
 * <p>
 * Should we split DataField into two kinds of interface:
 * DataField and DataFieldNonblocking? Instead we split
 * the behavior with setReady and setReadyNonBlocking.
 * </p>
 */
class DataField : Port {
public:
    /**@Data definition. */
    //@{
    /** <p>Begin the incremental build of a field. 
     *    This not a collective call, but at some point
     *    a collective call will be made which bombs if this call
     *    has not been made everywhere that the DataField instance exists.
     * </p>
     * <p>
     * <b>@status</b> This interface makes it mighty inconvenient to describe
     * and communicate about multi-field problems which store all
     * the variables for a given node/element in a single struct ,
     * but Jim says this is particles.  We might consider doing a
     * similar interface for the MPI_Datatypes or some PVM equivalent,
     * assuming that MPI_Alltoallv isn't already an MxN component if
     * used correctly with MPI_Datatypes. By morphing Data
     * appropriately, we could fix this problem for 80% of cases.
     *
     * @param name, the logical name of data, is copied, the 
     *              pointer is not kept.
     * @param data, pointer which is kept in the DataField object.
     * @param u Defines the units that go on Data. The units design is
     * per Ben and Tom. This call is not optional, as all
     * interfaces which use DataFields specify that unit consistency
     * shall be checked.
     * Data is presumed to encapsulate an array(or equivalent) of
     * a single type (eg double) and kind (eg temperature).
     * @return 0 on the first call with string and data.
     *         0 on the second call if given string and data
     *           is NULL/0. This informs the Datafield to forget
     *           the Data it currently knows and be ready for recycle.
     *         -1 (and no action taken) if called with another set
     *            of name and data while still possessing the last data.
     *         -2 if there is some other internal failure.
     * @see MeasuresFactory::getUnits to obtain the Unit.
     * @see DataFactory to obtain the Data.
     */
    virtual int setField(char *string name, Data *data, Unit *u ) = 0;

    /** Define the process(es)(ors) holding the field. */
    virtual void setProcArray( ProcArray parray ) = 0;

    /** Describe the regular grid type eg "rectangular", "spectral"
      @param gridType is copied, not kept.
     */
    virtual void setGridType(char *gridType ) = 0;

    /** Set current simulation time for data field.
     */
    virtual void setTime(Time *time ) = 0; 

    /**  Simulated time per iteration. 
     */
    virtual void setPeriod(Time *period ) = 0; 

    /** Get the introspection interface for the data field.
        The queries are kept in a separate interface to keep
        the complexity of DataField (which is bad enough already)
        down.
        @return output info is NULL if setField has not been called.
     */
    virtual void getDataFieldInfo(DataFieldQuery * & info) = 0;
    //@}

    /**@Data scribbling control. */
    //@{
    /** We have a whole bunch of merely nouns, then suddenly a verb.
        data field is ready for collection, just in case anyone has
        or soon will call getDataField.
        This is a BLOCKING call.
       @param incrTime Increment field time (by period) or not.
     */
    virtual void setReady(boolean incrTime ) = 0;

    /**<p> So the idea here is that there are two ways to call setReady(),
     * "block until everyone has been serviced"  or "my data
     * field is ready to be read/written now, so do it at your leisure"
     * setReadyNonblocking();.
     * </p>
     * <p>
     * In the nonblocking case what you're really doing is
     * setting up for an asynchronous connection, so like if you know
     * the data is ready to be accessed for a while, you can let everyone
     * else know it and they can come get it when they need it, etc.
     * </p>
     * <p>
     * Clearly, you need another method:
     * <p>
     *         void waitData();
     * </p>
     * which you can call later to make sure that everybody has serviced
     * their requests before you go forward to read or scribble on your
     * DataField again...
     * </p>
     * @param incrTime Increment field time (by period) or not.
     */
    virtual void setReadyNonblocking(boolean incrTime ) = 0;

    /** the other half of setReadyNonblocking. */
    void waitData() = 0;

    //@}
};

//=================================================================
/**
 * <p>Function for accessing items configured in the DataField interface.
 * Of course if the mxn component is also the datafield
 * factory component, then we don't need get functions for the mxn to use.
 * We would still need get functions to support other convolutions,
 * however.
 * </p>
 */
class DataFieldQuery : Port {

  /** Inverse DataField::setData().
      @return d,u NULL on output if field unset.*/
  void getField(Data * &d, Unit * & u) = 0;

  /** Return the name of this field, or NULL if field unset. */
  char *getName() = 0;

  /** Inverse DataField::setTime.
      @return t NULL on output if unset. */
  void getTime(Time * & t) =0;

  /** Inverse DataField::setGridType. 
      @return NULL if unset. */
  char *getGridType() =0;

  /** Inverse DataField::setProcArray.
      @return NULL if pa unset. */
  void getProcArray(ProcArray * & pa) =0;
};

//=================================================================
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

    /** Dimensionality of the array dataptr, which has NOTHING to
        do with the geometry it represents.
        @param nDimensions - number of dimensions in data array. For
               unstructured data, it is 1.
        @param dataSize[i] where i=0..nDimensions-1, is the
               cardinality of axis i.
        @param layout If nDimensions > 1, then:
               <b>layout = 1</b> -->
               array dataPtr is assumed to be laid out in the
               column major f77 style.
               <b>layout = 2</b> -->
               array dataPtr is assumed to be laid out in the
               row major contiguous (transpose f77) style.
	       <b>layout = 0</b> -->
               array dataPtr is assumed to be laid out C style,
               i.e. an array of pointers, not a pointer to contiguous
               memory.
        @return 0 if ok, -1 if there is an error in the arguments,
                possibly including a mismatch between nDimensions
                and the subtype of Data (structured, unstructured...)
     */
    virtual int setSize(int nDimensions, int *dataSize, int layout) = 0;
};

//=================================================================
/** Data specialized to irregular geometries using a representation
 *  that would be grossly inefficient for the RectangularData case. 
 * Don't we need some get functions for this, too? In this interface
 * or elsewhere?
 * Probably want additional definition functions.
 * This is mainly a placeholder until we hear from the FEM heavyweights.
 */
class UnstructuredData :  Data {
public:

    /** @see Data::setData. */
    virtual void setData(void *dataPtr) = 0;
    /** @see Data::setType. */
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

//=================================================================
/** <p>Data specialized to geometries which match the topology of the
 *  fortran array defined with setSize(), allowing for overlaps.
 *  On the local data, each axis i of the array is laid out so:
 * </p><p>
 *    |---- a ---|----------------------- b ----------------|-- c ---|
 * </p><p>
 *   dataSize[i] = a + b + c;
 * </p><p>
 *   dataValidOffset[i] = a;
 * </p><p>
 *   dataValidSize[i] = b;
 * </p><p>
 *   overlaps = a+c; // This is too restrictive to capture
 *                    unstructured mesh decomps. See UnstructureData.
 * </p><p>
 * This local data is related to some logically global data
 * and topology by the Decomposition.
 * Don't we need some get functions for this, too? In this interface
 * or better elsewhere?
 * </p>
 */
class RectangularData : Data {

public:
    /** @see Data::setData */
    virtual void setData(void *dataPtr) = 0;
    /** @see Data::setType */
    virtual void setType(char *dataType) = 0;
    /** @see Data::setSize */
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

//=================================================================
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

//=================================================================
/** Describe the properties of a RectangularDecomposition.
    Don't we need some get functions, too, perhaps in another
    interface? 
*/
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

    /** <p>
     * This thingy is used for "explicit" data decompositions, i.e. ones
     * that won't fit into "standard" block/cyclic definitions.  If I'm
     * a component that stores several random sub-arrays of some big global
     * array, I can set the bounds along each axis for each sub-array:
     * </p><p>
     *    Global array is Foo[100][100][100];
     * </p><p>
     *    I have Foo[10:20][20:30][30:40] and Foo[71:73][50:90][80:99]
     * </p><p>
     *    So I describe these regions via:
     * </p><p>
     *          XInfo->addBounds( 2, { 10, 71 }, { 20, 73 } );
     * </p><p>
     *          YInfo->addBounds( 2, { 20, 50 }, { 30, 90 } );
     * </p><p>
     *          ZInfo->addBounds( 2, { 30, 80 }, { 40, 99 } );
     * </p><p>
     * Those bounds define the global context of the two sub-array regions
     * stored locally.
     * </p>
     * @param numBounds is the # of explicit region bounds and
     *       the size of lowerBounds and upperBounds arrays.
     */
    virtual void addBounds(int numBounds, int * lowerBounds, int * upperBounds ) = 0;
};

//=================================================================
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

//=================================================================
//===============================================================

/** Generic convolution interfaces that do source-preserving local operations.
  *<P>
  * An implementation shall do exactly one thing, so as not to confuse
  * the application developer who expects it to do exactly one thing
  * when it in fact does three. Examples of 'thing' include:
  * <ul><li> mapping (in the multi-grid sense) data from grid A to alternate
  *    resolution grid B.</li>
  * <li> computing a gradient of grid A and storing it with similar units in
  *    grid B.</li>
  * </ul></p>
  * <p>We expect that eventually "one thing" will get defined with more
  *    complexity as people drift toward highly optimized, mono-application
  *    implementations of low reusability.</p>
  * @see CollectivePort for global data redistributive copy.
  * @see CouplingPort for repeated global data redistributive copy.
  * @see ConvolutionInPlace for local data transformation in place. 
  */
class Convolution : Port {
public:

    /** Map from srcField to dstField, overwriting dstField.
        This is a collective call, usually.
        @param srcField is NOT changed by the convolution.
        @param dstField is changed by the convolution.
        @return 0 if ok, -1 if something about the fields
                  is incompatible, -2 if other internal failure. 
                  Example of incompatible includes inappropriate
                  units, grid info, etc.*/
    virtual int convolve(DataField *dstField, DataField *srcField) = 0;
};

//=================================================================
/** Describe the simulation time. Could use a timeValue and Unit as below
    instead.
    Don't we need some get functions, too? In this interface
    or a separate one?
 */
class Time {
public:
    /** set the time (locally) in the simulation.
       @param timeValue it the time. perhaps it should be double or
              long long or something like that...
       @param u, a Unit as defined elsewhere.
     */
    virtual void setTime(float timeValue, Unit *u) = 0;

    /** Bump the time by the value given in the units given,
        and do the right thing even if the clock is in a different unit.
       @param bumpValue is the time increment.
       @param u, a Unit as defined elsewhere.
     */
    virtual void advanceTime(float bumpValue, Unit *u ) = 0;

};

//=================================================================
/** We pass around one or more convolutions, rather than a function pointer.  
 */
class TimeInterpolant : Convolution {
public:
    /** map from TimeQueue and srcField to dstField, overwriting dstField. */
    virtual void convolve(DataField *dstField, DataField *srcField ) = 0;

    /** Configure time slices. */
    virtual void setTimeQueue(TimeQueue *q) = 0;
};

//=================================================================
/** We pass around one or more Convolutions, rather than a function pointer. */
class SpaceInterpolant : Convolution {
public:
    /** map from srcField to dstField with some geometric tricks,
        overwriting dstField. */
    virtual void convolve(DataField *dstField, DataField *srcField ) = 0;

    /** some geometric tricks. obviously this is a placeholder. */
    virtual void setGridTypes( char * dstGridType, char * srcGridType) = 0;
};

//=================================================================
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

//===============================================================
//===============================================================

/** Generic global convolution of data in place.
 *  The component that provides this interface will no doubt
 *  need other parameters. This can be achieved by deriving
 *  an interface from it (such as ConvertUnits) or by
 *  providing a separate configuration interface on the same
 *  component that implements this interface.
 * @see CollectivePort for global data redistributive copy.
 * @see CouplingPort for repeated global data redistributive copy.
 * @see Convolution for source preserving local data transformations. 
 */ 
class ConvolutionInPlace : Port {
public:
    /** Transform data, writing result over input data.
        @return 0 if successful, -1 if field is incompatible,
          with details of the convolution, -2 if other 
          internal bogosity occurs.
     */
    virtual int convolveInPlace(DataField *field) = 0;
};

//=================================================================

/** If you want a copy of an original field but in different units, 
 * copy it first and then use this to change the units on the copy.
 * Mindnumbing scaling computation example.
 */ 
class ConvertUnits : ConvolutionInPlace {
public:
    /** Convert units in place.
     *  @return 0 if successful, -1 if fields incompatible,
     *    -2 if other bogosity occurs.
     */
    virtual int convolveInPlace(DataField *field) = 0;

    /** Set the new Unit desired for a conversion in place.  */
    virtual void setConversionFactor(Unit *dstUnits) = 0;
};

//===============================================================
//===============================================================

/**
 * <p>
 *  A simple, semantically checkable unit description.
 *  Functions for an arithmetic of units could be added.
 *  This includes any conversion, even silly things like
 *  Farenheit to Celsius conversions.
 * </p><p>
 *  The truly insane things, like API octane rating,
 *  probably just won't ever be useful enough to bother
 *  with here; pretend they are dimensionless.
 * </p><p>
 *  We can define an arithmetic of units/dimensionalities
 *  compatible with this interface, but any sane implementation
 *  thereof will require (for intermediate processing)
 *  a Dimensions subclass that supports both numerator and denominator
 *  in each exponent. Not difficult, but potentially confusing
 *  to a user that just wants to characterize data, not algebraic
 *  expressions.
 * </p>
 * @see Dimensions
 * @see MeasuresFactory.
 */
class Unit {
public:
    /** Get the name of this unit, eg "pascal".*/
    virtual void getName(char * & name) = 0;

    /** Get the fundamental dimensionality of this unit. */
    virtual void getDimensions(Dimensions * & d) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValueFromSI(double SIvalue, double & value) = 0;

    /** Get the corresponding SI value, given a value. This lets us
        map every unit conversion, no matter how bizarre (Farenheit???)
        via an SI intermediate.
        @param value - the value (in units of getName() to be converted to SI.
        @param SIvalue - an output, the value converted to SI.
     */
    virtual void getSIValueFromUnit(double value, double & SIvalue) = 0;

    /** Return the corresponding SI unit. We could generalize
        this function by taking a "system name" (CGS,SI,...),
        and returning the appropriate unit, but that would
        require all implementations to know about all systems.
        We'd rather require only 1 alternate-system mapping.
        @param si - an output, the equivalent SI unit.
     */
    virtual void getSIUnit(Unit * & si) = 0;

};

//===============================================================

/** A simple, semantically checkable unit representation.
    Functions for an arithmetic of MultiplicativeUnits could be added.
    This covers any unit that is a conversion by multiplication
    from the SI units.  The eg throughout is for a pressure unit.
    @see NonmultiplicativeUnit.
  */
class MultiplicativeUnit : Unit {
public:
    /** Get the name of this unit, eg "pascal". */
    virtual void getName(char * & name) = 0;

    /** Get the fundamental dimensionality of this unit. */
    virtual void getDimensions(Dimensions * & d) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValueFromSI(double SIvalue, double & value) = 0;

    /** Get the corresponding SI value, given a value. This lets us
        map every unit conversion, no matter how bizarre (Farenheit???)
        via an SI intermediate.
        @param value - the value (in units of getName() to be converted to SI.
        @param SIvalue - an output, the value converted to SI.
     */
    virtual void getSIValueFromUnit(double value, double & SIvalue) = 0;

    /** Return the corresponding SI unit. We could generalize
        this function by taking a "system name" (CGS,SI,...),
        and returning the appropriate unit, but that would
        require all implementations to know about all systems.
        We'd rather require only 1 alternate-system mapping.
        @param si - an output, the equivalent SI unit.
     */
    virtual void getSIUnit(Unit * & si) = 0;

    /** eg 1.0. 
        <p>
        double cf = getSIConversionFactor();
        </p><p>
        is equivalent to
        </p><p>
        Unit *si; double cf;
        </p><p>
        getSIValue(1, cf);
        </p><p>
        Another example: unit with name "millimeter" --> cf = 0.001;
        </p>
        @return the scaling factor needed to bring a value
        in units of getName() to SI units.
      */
    virtual double getSIConversionFactor() = 0;

    /** eg "kg/m/s^2".
        <p>Could be implemented as 
        </p><p>
        Unit *si;
        </p><p>
        getSIUnit(si);
        </p><p>
        si->getName();
        </p><p>
        but is more easily implemented using Dimensions directly.
        </p>
      */
    virtual void getSIUnitName(char * & sn) = 0;

    /** eg double cf;
        <p>
             int err = u.getConversionFactor("kPa",cf);
        </p><p>
          -->   cf = 0.001 && err = 0;
        </p><p>
        while int err = u.getConversionFactor("ftLbs",cf);
        </p><p>
          --> cf undefined and err = 1;
        </p>
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

//===============================================================

/** A messy, semantically checkable unit representation.
    Functions for an arithmetic of NonmultiplicativeUnits would
    be insanely hard to add.
    This covers any unit that is NOT a conversion by multiplication
    from the SI units.
    @see MultiplicativeUnit.
 */
class NonmultiplicativeUnit : Unit {
public:

    /** eg "Fahrenheit" */
    virtual void getName(char * & n) = 0;

    /** return the fundamental dimensions. */
    virtual void getDimensions(Dimensions * & d) = 0;

    /** Convert an SI value to this particular unit. */
    virtual void getUnitValueFromSI(double SIvalue, double & value) = 0;

    /** Get the corresponding SI value, given a value. This lets us
        map every unit conversion, no matter how bizarre (Farenheit???)
        via an SI intermediate.
        @param value - the value (in units of getName() to be converted to SI.
        @param SIvalue - an output, the value converted to SI.
     */
    virtual void getSIValueFromUnit(double value, double & SIvalue) = 0;

    /** Return the corresponding SI unit. We could generalize
        this function by taking a "system name" (CGS,SI,...),
        and returning the appropriate unit, but that would
        require all implementations to know about all systems.
        We'd rather require only 1 alternate-system mapping.
        @param si - an output, the equivalent SI unit.
     */
    virtual void getSIUnit(Unit * & si) = 0;
};

//===============================================================

/** The core of any sane units conversion implementation.
  * To cover sensible physical and economic systems there are
  * 7 SI defined dimensions, 2 supplementary dimensions, and
  * the human dimension. String theory may suggest a few more
  * dimensions, but those aren't directly sensible (yet).
  * <p>
  * We suggest using an array of ints (could be shorts)
  * indexed like so:
  * <ul>
  * <li>       (description)                     (type)         (index)
  * <li> index for mass dimension.               MASS               = 0;
  * <li> index for quantity dimension, eg. mole. QUANTITY           = 1;
  * <li> index for distance dimension.           LENGTH             = 2;
  * <li> index for time (4th) dimension.         TIME               = 3; 
  * <li> index for temperature dimension.        TEMPERATURE        = 4;
  * <li> index for the human value dimension.    CURRENCY           = 5;
  * <li> index for electric current dimension.   ELECTRIC_CURRENT   = 6;
  * <li> index for luminous intensity dimension. LUMINOUS_INTENSITY = 7;
  * <li> index for plane angle dimension.        PLANE_ANGLE        = 8;
  * <li> index for solid angle dimension.        SOLID_ANGLE        = 9; 
  * </ul>
  * </p><p>
  *   This may be controversial, as some purists insist
  *   that the angle types are DIMENSIONLESS. For practical
  *   purposes, we do want to convert safe from degrees to
  *   radians to grad. Applications can always choose to
  *   describe angle data as dimensionless and take their
  *   chances. Scientists may have no values with money,
  *   but engineers certainly do.
  * </p>
  * <p>
  * It is a trivial matter to add one more layer of interfaces
  * (a UnitSystem) to support alternate system conveniences such as
  * USEngineering, CGS, and so forth.
  * We'll do this if demand supports it.
  * </p>
  * <p>We don't anticipate fortran clients ever using this interface
  *    directly.</p>
  * @see MeasuresFactory.
  */
class Dimensions {
public:
  /** The exponents that define this dimensionality. E.g. 
   * <p>
   *  MASS/DISTANCE/TIME^2 -->
   * </p><p>
   *  "kg/m/s^2" --> 
   * </p><p>
   *  int[10] = {1,0,-1,-2,0,0,0,0,0,0};
   * </p>
   *  @return An array of shorts numDimensions long.
   */
  virtual int *getExponents() = 0;

  /** @return the SI units for this dimensionality, eg "kg/m/s^2" */
  virtual const char *getSIUnits() = 0;


  // generic functions for describing this dimension scheme.
  /**  
      @return Number of dimensions in our ontology, 10.
   */
  virtual int getNumDimensions() = 0;

  /** Map the exponent to convenient PHYSICS_TERM. 
      int dim = 0..getNumDimensions().
   */
  virtual const char *getDimensionType(int d) = 0;

  /** map DimensionType to number. Handy for parsers. */
  virtual const char *getDimensionNumber(char *dimensionName) = 0;

  /** Return a string with the SI unit name associated with the
      dimension. */
  virtual const char *getDimensionSIUnitName(int dimensionNumber) = 0;

};

//===============================================================

/** A class for defining and getting units and dimensions. */
class MeasuresFactory : Port {

  /** Get the unit description corresponding to
      a combination of known units and the operators *,/,^.
      @param unitString is an input unit expression, e.g.
             "furlong^2/fortnight*slug".
      @param u is on return a Unit matching the string description. 
      @return u will be 0 if the string description is unparsable.
   */
  virtual void getUnits(char *unitString, Unit * &u);

  /** Get a Dimensions corresponding to the exponents given.
      @param dimString is a string made up of the results of getDimensionType,
             e.g. "MASS/DISTANCE/TIME^2", with no parens allowed.
      @param dim is a pointer to the Dimensions result. 
      @return dim is 0 on return if the input string is bogus.
   */
  virtual void getDimensions(char *dimString, Dimensions * &dim) = 0;

  /** Define a new unit name, e.g. "atmosphere", for a multiplicative
      unit. After "atmosphere" has been added to the factory with
      defineMultiplicativeUnit, it can be used successfully in getUnits()
      calls.
      @param unitName is a simple string (no arithmetic operators in it).
      @param dim is the Dimensions associated with the unit.
      @param SIfactor is the conversion factor needed to convert 1.0
             of the new unit to SI units (kilogram,meter,second,...).
             For "atmosphere", SIFactor would be 101325 (roughly).
   */
  virtual void defineMultiplicativeUnit(char *unitName, Dimensions *dim, double SIfactor) = 0;

  /** Define a new unit name, e.g. "atmosphere", for a nonmultiplicative
      unit. Once defined, its name can be used successfully in 
      simple getUnits() calls.
      @param nu has a separate implementation for every non-multiplicative
             unit, so defineNonmultiplicativeUnit is just called with
             a pointer to that implementation. A good factory implementation
             will come with a number of these built-in.
   */
  virtual void defineNonmultiplicativeUnit(NonmultiplicativeUnit *nu) = 0;

};

#endif // speculation_rampant
