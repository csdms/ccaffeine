#ifndef dc_fwk_kernelport_h_seen
#define dc_fwk_kernelport_h_seen
/** Basic  kernel port version of ccafeopq::Port
 * that can be inherited in all kernel-tied port implementations
 * to satisfy vtable requirements.
 * Kernel supplied services that exist in multiple bindings
 * may make additional calls to addSupportedKind.
 *
 * The taxonomy is:
 * ccafeopq::Port
 *   ccafeopq::support::Port
 *     BabelOpaquePort <-- tags for a babel port
 *     KernelPort <-- tags for opaque inheriting port
 *     ClassicOpaquePort <-- tags for a classic inheriting port
 *     NeoOpaquePort <-- tags for a neo inheriting port
 * Support services supplied by the framework may inherit multiple
 * of these interfaces. In any case where it is done by inheritance,
 * the final derived class must call the init[Kernel,Classic,Babel]
 * function(s) inherited to set up the string table that indicates
 * which bindings are supported.
 * 
 * Bugs: this class really belongs in the export support directory, not
 * in the framework.
 */
class KernelPort : public virtual ::ccafeopq::Port, public virtual ::ccafeopq::support::Port
{
private:
  int kernel_num;
  static int kernel_nextNum;

public:
  KernelPort(); 

  virtual ~KernelPort();

  virtual void initKernel();
};
#endif // dc_fwk_kernelport_h_seen
