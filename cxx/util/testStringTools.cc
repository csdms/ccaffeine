#include <vector>
#include <string>
#include <stdio.h>
#include "StringTools.hh"

using namespace std;

int main(int argc, char**argv) {
  string s = string(" a b cdsa ");
  string ans = StringTools::chomp(s);
  printf("string \"%s\" chomps to \"%s\"\n", s.c_str(), ans.c_str());
  printf("string \"%s\" splits to:\n", s.c_str());
  vector< string > a = StringTools::split(s);
  for(size_t i = 0;i < a.size();i++) {
    printf("array[%d] = \"%s\"\n",int(i), a[i].c_str());
  }
  s = string("asdf sadf eqwr");
  a = StringTools::split(s);
  for(size_t i = 0;i < a.size();i++) {
    printf("array[%d] = \"%s\"\n",int(i), a[i].c_str());
  }
}
