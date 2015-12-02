#include <sys/time.h>
#ifdef __linux
// #include <error.h> 
//#include <errno.h>
#endif
#include <sys/types.h>
#include <unistd.h>

#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "jc++/io/jc++io.h"
#include "jc++/jc++dynamic.h"

JCPP_DynamicLink::JCPP_DynamicLink(int i) {
  i_ = i;
  if (i) {
    br = new jcpp::BufferedReader((jcpp::Reader *)0);
    nbr = new jcpp::NonblockingReader((jcpp::Reader *)0);
    sr = new jcpp::StdReader(-1);

    bjc = new jcpp::BooleanJC((char *)"t");
    djc = new jcpp::DoubleJC(0);
    fjc = new jcpp::FloatJC(0);
    ijc = new jcpp::IntegerJC(0);
    ljc = new jcpp::LongJC(0);

    ht = new jcpp::Hashtable();
    rh = new jcpp::ResourceHash();
    sb = new jcpp::StringBuffer();
    sh = new jcpp::StringHash();
    st = new jcpp::StringTokenizer((char *)"");
    sv = new jcpp::StringVector();
    v = new jcpp::Vector();
  }
}

JCPP_DynamicLink::~JCPP_DynamicLink() {
  if (i_) {
#define forget(x) delete x; x = 0
    forget(br);
    forget(nbr);
    forget(sr);
    forget(bjc);
    forget(djc);
    forget(fjc);
    forget(ijc);
    forget(ljc);
    forget(ht);
    forget(rh);
    forget(sb);
    forget(sh);
    forget(st);
    forget(sv);
    forget(v);
  }
}
