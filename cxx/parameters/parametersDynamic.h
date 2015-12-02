#ifndef parameters_dynamic_h_seen
#define parameters_dynamic_h_seen
/** requires
// parameters.h
*/
class parameters_DynamicLink {

public:

  /** To force the link of the parameters classes, construct and
   destroy 1 of these somewhere in your statically linked
   code (main() might be appropriate). Thus all the symbols
   will be required and the link editor will do the right
   thing.
	@argument int i -- if 0 (what you want) the member
	pointers are not filled in. Else we actually try
	to instantiate all the classes into our structure.
	Since it's a runtime decision, the linker will bind
	all the parameter classes.
   Note we don't include ExceptionJC.
  */
  parameters_DynamicLink(int i);

  /** Destroy the collection, if ever really instantiated. */
  ~parameters_DynamicLink();

private:
  int i_;

  BoolParameter *bp;
  DoubleParameter *dp;
  FloatParameter *fp;
  IntParameter *ip;
  LongParameter *lp;
  StringParameter *sp;

};
#endif // parameters_dynamic_h_seen
