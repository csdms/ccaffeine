/** interface ala IOVec, a set of buffers all local and 1-D. */
class RawData : public virtual classic::gov::cca::Port {
public:

  /** Name of this set of buffers. */
  virtual const char * getName() = 0;

  /** The total count of buffers encapsulated. */
  virtual int getNumberOfBuffers() = 0;

  /** Buffers are indexed from 0 .. getNumberOfBuffers-1.
      @param bufferIndex Input: the index (from 0) of buffer requested.
      @param elementType Output: enumerated type of the elements in the buffer.
      @param elementCount Output: length of the buffer.
      @param buffer Output: pointer to data buffer.
  */
  virtual getBufferInfo(int bufferIndex, enum RawDataType &elementType, 
                        int & elementCount, void* & buffer) = 0;


  /** An enum over C/Fortran primitives in multiple precisions. finish later */
  enum RawDataType {
    Err =0,
    Byte =1, Char, Wchar, Int1, Int2, Int4, Int8, Float4,
    Complex4,  
    Complex8,  
    Complex16,  
    Complex32,  
    Bool1,
    Etc
  };

}; // RawData

/** LOCAL interface on cartesian dense data that presents
  * a window. This allows for a self-similar interface to
  * a smaller block within the window.
  * <pre>
  * Example:
  * LocalArray Window *awin; // assumed 2D
  * enum RawDataType::RawDataType dataType;
  * int rank;
  * int *lbc, *ubc, *stride, *ld;
  * void * array;
  * awin->getInfo(dataType, rank);
  * awin->getData(lbc, ubc, stride, ld, array);
  * for (int j = lbc[1]; j <= ubc[1] ; j += stride[1]) {
  *     for (int i = lbc[0]; i <= ubc[0] ; i += stride[0]) {
  *      x += array[(j*ld[0])+ i];
  *     }
  * }
  * </pre>
  */
class LocalArrayWindow  : public virtual classic::gov::cca::Port {
public:

  /** Get the name of this object. */
  virtual const char * getName() = 0;
  
 /** Basic info lookup, in case we want a copy version of getData.
  * LocalArray Window *awin; // assumed 2D
  * enum RawDataType::RawDataType dataType;
  * int rank;
  * int *lbc, *ubc, *stride, *ld;
  * void * array;
  * awin->getInfo(dataType, rank);
  * awin->getData(lbc, ubc, stride, ld, array);
  * for (int j = lbc[1]; j <= ubc[1] ; j += stride[1]) {
  *   for (int i = lbc[0]; i <= ubc[0] ; i += stride[0]) {
  *     x += array[(j*ld[0])+ i];
  *   }
  * }
  * @param rank 1d,2d,3d array.
  */
  virtual void getInfo( enum RawDataType::RawDataType &dataType, int & rank) = 0;

  /** Get the info needed for iteration.
      We may want locking(read/write),release.
      We assume Babel will solve the index from 1 problem
      in the FORTRAN binding.
    @param lowerBoundsC 0-indexed array of lower bounds.
    @param upperBoundsC 0-indexed array of upper bounds.
    @param stride step in each dimension.
    @param leadingDimensions size of actual array in each dimension.
    @param array the same pointer regardless of window lowerbounds.
  */
  virtual void getData(
                 const int[] & lowerBoundsC, // 0-indexed
                 const int[] & upperBoundsC, // 0-indexed
                 const int[] & stride, 
                 const int[] & leadingDimensions, // size in each dimension 
                 const void* & data // pointer to beginning of data w/out window
          ) = 0;

   /** piecewise... redundant function */
   virtual const enum RawDataType::RawDataType getType() = 0;
   /** piecewise... redundant function */
   virtual const int getRank() = 0;
   /** piecewise... redundant function */
   virtual const int[] getLeadingDimensions() = 0;
   /** piecewise... redundant function */
   virtual const void * getData() = 0; // maybe want locking flavors& release.
 
   /** Get another subset view on this same data.
     */
   virtual LocalArrayWindow *createWindow(
                 const int[] & lowerBoundsC, // 0-indexed
                 const int[] & upperBoundsC, // 0-indexed
                 const int[] & stride
           ) = 0;

};

/** If a field "temperature" exists in the datamanager,
  then it should be accessible by one or more of the following views.
  Lots more/less should probably go in the data manager, particularly
  there may be general agreement that there be generic support for
  multiple views (raw, array, meshed, etc) of the same data items
  keyed by a string name and a view type. 

  Whether the relatively clue-free datamanager produces these 
  views or just holds them once published there is a question 
  remaining to be discussed.

  In particular, one manager could hold data virtual interfaces to
  concrete objects from from several different factories.
*/
class DataManager : public virtual classic::gov::cca::Port {
  /** We assume this is possible and desirable. */
  virtual LocalArrayWindow *getLocalArrayWindow(char * name) = 0;

  /** We assume this is possible and desirable. */
  virtual RawData *getRawData(char * name) = 0;

  // post-meeting commentary by Ben, ala John's notions
  // but without an intervening OODB literature review.


  /** Add the "native" view of a data item. Mightn't this
      be something other than a Port as data argument?
      particularly, might we want an ObjectCountable
      interface that refines port and then add data to 
      datamanagers in the ObjectCountable form?
  */
  virtual void putDataPort(char *newDataItemName, Port *data) = 0;
      
  /** Add an alternative view on currently known data, e.g. add an
      IOVec view of a 2d array or a mesh topology.
   */
  virtual void addDataPortView(char * existingDataItemName, 
                               char * newViewType,
                               Port * newView) = 0;

  /** Fetch the desired view type on an existing data. It's possible
      that the view is not available and the result will be NULL.
   */
  virtual classic::gov::cca::Port *getDataView(const char * existingDataItemName,
                                      const char * desiredViewType) = 0;
   
};

