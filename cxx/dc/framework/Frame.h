#ifdef CCAFE_FRAME_PRIVATE_OK // invisible by default
#ifndef ccafe_Frame_h_seen
#define ccafe_Frame_h_seen

#include <map>
#include <string>

namespace ccafe {
/** private implementation that is *highly* volatile
 * and *highly* opaque because of massive header contamination
 * that DefaultBuilderModel causes.
 */
class Frame {

private:

  /** This (DefaultBuilderModel is a total booger
  // it screws up *everything*, from a dependency point of view
  // as it has so much crap in it.
  // We keep it as void* in the header and cast it
  // in all places used in the implementation.
	// It is in fact not even necessary, because
	// having external components appear in the pallet
	// doesn't make sense-- they may or may not exist
	// in the instantiable space (a second copy of
	// main() is what?). They are only in the instance
	// space by default (arena).
	// One could discover non-pulldown-able classes by querying
	// the arena and then getting type data per instance.
	// On the off chance that someone creates a component
	// instance from the driver that is *also* a pallet
	// class, so what? The driver is still responsible
	// for shutting down external components regardless
	// of type known internally or not.
  */
  void * bm; 

public:

  /** fComm is a fortran mpi communicator if we're supporting mpi
   * in the frame created, or ignored if useComm is false.
   */
  Frame(int64_t fComm,  bool useComm);
  /*
   * If the frame is a child frame derived from a parent, 
   * it will need to be destroyed before the parent when
   * there is a shared mpi resource.
   */
  ~Frame();

  /**
  * Meant to be something like a commandline arguments for the
  * this Ccaffeine framework object.  Currently supported:
  *
  * --path /a/place/for/components:another/place/for/components:...
  *        Ccaffeine will discover the components in the path.
  * --load a:colon-separated:list:of:components
  *        load specified components into the pallet.
  */
  void initialize (  const ::std::string & args /* not needed here: 
	, int64_t fComm, bool useComm */ ) ;

  ::ccafeopq::Services * getServices ( const ::std::string& selfInstanceName, const ::std::string& selfClassName, ::ccafeopq::TypeMap_shared selfProperties);

  void releaseServices ( ::ccafeopq::Services *svc);

  void shutdownFramework();
  
  ccafeopq::TypeMap_shared createTypeMap();

  bool isShutdown();

}; // end class Frame

} ENDSEMI // end ccafe namespace
#endif // ccafe_Frame_h_seen
#endif // CCAFE_FRAME_PRIVATE_OK
