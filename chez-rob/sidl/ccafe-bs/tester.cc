#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>

#include "SIDL_cxx.hh"
#include "gov_cca_Type.hh"
#include "Object.hh"
#include <boost/shared_ptr.hpp>

using namespace ccaffeine;

typedef std::map<std::string, ObjectBase*> ObjectMap;
typedef std::map<std::string, ObjectBase*>::const_iterator Iter;

int main(int argc, char** arg) {

  ObjectMap table;
  Object<bool> o(Bool);

  o.set(false);

  if(o.get()) {
    fprintf(stdout, "reads true\n");
  } else {
    fprintf(stdout, "reads false\n");
  }
  
  table["myBool"] = &o;

  ObjectBase* q = table["myBool"];
  Object<bool>* p = (Object<bool>*)(q);

  std::string s = q->getTypeAsString();

  fprintf(stdout, "p is of type %s\n", s.c_str());
  
  if(p->get()) {
    fprintf(stdout, "reads true\n");
  } else {
    fprintf(stdout, "reads false\n");
  }
  int arraySize = 20;
  {
    SIDL::array<int>* aip = new SIDL::array<int>();
    SIDL::array<int>& ai = *aip;

    int32_t len = arraySize; // array length
    int32_t dim = 1;  // one dimensional
    int32_t lower[1] = {0}; // zero offset
    int32_t upper[1] = {len-1};
    ai.create(dim, lower, upper);
    for(int i = 0; i < arraySize; i++) {
      ai.set(i, i);
    }
  
    // get methods.
    typedef boost::shared_ptr< ObjectBase > OPtr;
    typedef std::map<std::string, OPtr> OPtrMap;
    typedef std::map<std::string, OPtr>::const_iterator OptrMapIter;
 
    OPtrMap optrMap;
    {    
      Object< SIDL::array<int> >* op = 
	new Object< SIDL::array<int> >(IntArray);
      Object< SIDL::array<int> >& o = *op;
      SIDL::array<int>* axp = new SIDL::array<int>(ai); // copy (I hope)
      SIDL::array<int>& ax = *axp;
      for(int i = 0; i < arraySize; i++) {
	ax.set(i+10, i);
      }
      o.set(ax);
      OPtr optr(&o);
      optrMap["one"] = optr;
    }
    {    
      Object< SIDL::array<int> >* op = 
	new Object< SIDL::array<int> >(IntArray);
      Object< SIDL::array<int> >& o = *op;
      SIDL::array<int>* axp = new SIDL::array<int>(ai); // copy (I hope)
      SIDL::array<int>& ax = *axp;
      o.set(ax);
      OPtr optr(&o);
      optrMap["two"] = optr;
    }
    {    
      Object< SIDL::array<int> >* op = 
	new Object< SIDL::array<int> >(IntArray);
      Object< SIDL::array<int> >& o = *op;
      SIDL::array<int>* axp = new SIDL::array<int>(ai); // copy (I hope)
      SIDL::array<int>& ax = *axp;
      o.set(ax);
      OPtr optr(&o);
      optrMap["three"] = optr;
    }

    int count = 0;
    for(OptrMapIter it = optrMap.begin(); it != optrMap.end();++it) {
      ObjectBase* ob = (it->second).get();
      Object< SIDL::array<int> >* o = 
	dynamic_cast< Object< SIDL::array<int> >* >(ob);
      const char* str = ob->getTypeAsString().c_str();
      const char* key = (it->first).c_str();
      fprintf(stdout, "%dth item, key = %s, my type is: %s\n", 
	      count++, key, str);
      SIDL::array<int> ax = o->get();
      int size = ax.upper(0) - ax.lower(0) + 1;
      for(int i = 0; i < size;i++) {
	fprintf(stdout, "%dth elem = %d\n", i, ax.get(i));
      }
    }
  }

  return 0;
}



