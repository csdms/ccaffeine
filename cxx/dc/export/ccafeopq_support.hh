#ifndef ccafeopq_supports_hh
#define ccafeopq_supports_hh

namespace ccafeopq {

/** default implementation headers of burdensome opq things.
* Actual implementations are in the framework directory.
*/
namespace support {


/** A default implementation so that lazy
binding writers can avoid rewriting it.
*/
class Port : public virtual ::ccafeopq::Port
{

private:
  /* * A derived class can clear supported to set its own default value.
  * The wisdom of this is subject to question.
  * But really we shouldn't be depending on cast to kernelport
  * for logic, we should be checking kind anyway if it matters.
  */
  std::vector< std::string > supported;
  static int next_serial;
  int serial;

public:
  Port();
  Port( const std::string kind );

  virtual ~Port();

  /**
   * N.B.: This function is quite likely to not work
   * during the loading of main(), so static objects
   * that inherit from it should somehow arrange
   * to call it after main is entered, or to avoid calling
   * it at all (possibly by adding a dummy constructor).
   * This seems to be due to stl non-initialization.
   */
  virtual void addSupportedKind(const std::string & s);

  /** return the orginating kind, which may be
    only a subset of the supported types. 
  */
  virtual const std::string getKind();

  /** return true if there is an intersection of
     p->getSupportedKinds and this->getSupportedKinds.
   */
  virtual bool isSameKind( ::ccafeopq::Port *p);

  virtual const std::vector< std::string > getSupportedKinds();

  virtual bool supportsMultipleKinds();

  virtual bool supportsKind( const std::string & k);

};

} ENDSEMI // support
} ENDSEMI // ccafeopq

#endif // ccafeopq_supports_hh
