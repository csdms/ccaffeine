#include <string>
#include <stdio.h>

int main(int arg, char** argv) {
  string s = "asdf:adsf:qwer";
  int zer = 0;
  int pos = s.find(':', zer);
  printf("the position is: %d\n", pos);
  string t = s.substr(zer,pos);
  printf("substr: %s\n", t.c_str());
  zer = pos + 1;
  pos = s.find(':', zer);
  t = s.substr(zer,pos);
  printf("substr: %s\n", t.c_str());
  
  
  exit(0);
}
