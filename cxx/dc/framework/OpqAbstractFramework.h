#ifndef ccafe_AbstractFramework_h_seen
#define ccafe_AbstractFramework_h_seen

namespace ccafe {

/** Private implementation Frame. Not to be seen by
 * anyone through this header or any binding.
 * The idea is that user drivers of ccafe::AbstractFramework
 * shouldn't be burdened by the gajillion crufty headers from
 * ccaffeine v0.3 and earlier or from babel or from whatever.
 */
class Frame;

/**
 * TRANSITIONAL core implementation of AbstractFramework.
 * Which is really a wrapper on extremely private piles
 * of cruft that will be changing heavily soon.
 */
class AbstractFramework : public virtual ::ccafeopq::AbstractFramework
{

private:
	/** don't even think of looking at what f contains. */
	::ccafe::Frame *f; 

	void checkFrame(const char *s);
	int64_t fortranMPIComm;
	bool hasComm;

public:
  AbstractFramework(int64_t fComm, bool useComm);

  /** see base class */
  virtual ~AbstractFramework();

  /**
  * Meant to be something like a commandline arguments for the
  * this Ccaffeine framework object.  Currently supported:
  *
  * --path /a/place/for/components:another/place/for/components:...
  *        Ccaffeine will discover the components in the path.
  * --load a:colon-separated:list:of:components
  *        load specified components into the pallet.
  */
  virtual void initWithString( const ::std::string & arg);

  virtual void initWithArgv( const char **argv, int argc);

  /** see base class */
  virtual ::ccafeopq::TypeMap_shared createTypeMap();

  /** see base class */
  virtual ccafeopq::Services *getServices(const std::string & selfInstanceName, const std::string & selfClassName, ::ccafeopq::TypeMap_shared selfProperties);

  /** convenience method */
  virtual ccafeopq::Services *getServices(const std::string & selfInstanceName, const std::string & selfClassName);

  /** see base class */
  virtual void releaseServices( ::ccafeopq::Services * svc);

  /** see base class */
  virtual void shutdownFramework();

  /** see base class */
  virtual ::ccafeopq::AbstractFramework * createEmptyFramework();

  /** see base class */
  virtual void destroyEmptyFramework( ::ccafeopq::AbstractFramework * subframe);

}; // end class ccafe::AbstractFramework implementation

} ENDSEMI // end namespace ccafe

#endif // ccafe_AbstractFramework_h_seen
