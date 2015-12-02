#include <boost/shared_ptr.hpp>
#include <stdio.h>

class HelloGoodbye {
private:
  string s;
public:
  HelloGoodbye(string s){
    printf("%s: hello\n", s.c_str());
    this->s = s;
  }
  HelloGoodbye(HelloGoodbye& hb) {
    printf("%s: hello copy\n", s.c_str());
    s = hb.s;
  }
  virtual ~HelloGoodbye(){
    printf("%s: goodbye\n", s.c_str());
  }
  void here() {
    printf("%s: Yo!\n", s.c_str());
  }
};


int main(int argc, char** argv) {
  boost::shared_ptr<HelloGoodbye> hgp = 
    boost::shared_ptr<HelloGoodbye>(new HelloGoodbye("1"));
  hgp->here();
  hgp.reset(new HelloGoodbye("2"));
  hgp->here();
  boost::shared_ptr<HelloGoodbye> hgp2 = 
    boost::shared_ptr<HelloGoodbye>(new HelloGoodbye("3"));
  hgp2 = hgp;
  hgp2.get();

  boost::shared_ptr<HelloGoodbye>* sp = new boost::shared_ptr<HelloGoodbye>(new HelloGoodbye("4"));
  boost::shared_ptr<HelloGoodbye> leaker = *sp;
  hgp = leaker;
}
