#ifndef jcpp_dynamic_h_seen
#define jcpp_dynamic_h_seen
/** requires
// jc++.h
// jc++io.h
// jc++lang.h
// jc++util.h.
// Deliberately does not live in jcpp:: namespace.
*/
class JCPP_DynamicLink {

public:

  /** To force the link of the jc++ classes, construct and
   destroy 1 of these somewhere in your statically linked
   code (main() might be appropriate). Thus all the symbols
   will be required and the link editor will do the right
   thing.
	@argument int i -- if 0 (what you want) the member
	pointers are not filled in. Else we actually try
	to instantiate all the classes into our structure.
	Since it's a runtime decision, the linker will bind
	all the jc++ classes.
   Note we don't include ExceptionJC.
  */
  JCPP_DynamicLink(int i);

  /** Destroy the collection, if ever really instantiated. */
  ~JCPP_DynamicLink();

private:
  int i_;

  /**@ io implementation classes */
  //@{
  jcpp::BufferedReader *br;
  jcpp::NonblockingReader *nbr;
  jcpp::StdReader *sr;
  //@}

  /**@ lang implementation classes */
  //@{
  jcpp::BooleanJC *bjc;
  jcpp::DoubleJC *djc;
  jcpp::FloatJC *fjc;
  jcpp::IntegerJC *ijc;
  jcpp::LongJC  *ljc;
  //@}

  /**@ util implementation classes */
  //@{
  jcpp::Hashtable *ht;
  jcpp::ResourceHash *rh;
  jcpp::StringBuffer *sb;
  jcpp::StringHash *sh;
  jcpp::StringTokenizer *st;
  jcpp::StringVector *sv;
  jcpp::Vector *v;
  //@}

};
#endif // jcpp_dynamic_h_seen
