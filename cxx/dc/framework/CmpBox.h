#ifndef CMPBOX_H_SEEN
#define CMPBOX_H_SEEN

// #include "dc/framework/XCmptFactory.hh"
#include <string>

namespace ccafe {

/** A little container to group component,
 * its name, and its Services object,
 * and a vast pile of meta-info.
 * Basically, this is the only place we
 * *really* know how a connection is made.
 */
class CmpBox {
 private:

 public:
  CmpBox(ccafeopq::Component * comp, Gizzard *giz, const std::string & name) ;
  CmpBox(Gizzard *giz, const std::string & name) ;
  CmpBox();
  virtual ~CmpBox();
  void setType(const std::string & type, bool internal);
  const char *name() { return cname.c_str(); }
  const char *type() { return ctype.c_str(); }

  // why are these public again?

  Gizzard *giz;
  ccafeopq::Component * comp;
  std::string cname;
  std::string ctype;
  bool internal;


};

typedef ::boost::shared_ptr< CmpBox > CmpBox_shared;

}  ENDSEMI // end namespace ccafe


#endif // CMPBOX_H_SEEN
