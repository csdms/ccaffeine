#include <vector>
#include <string>
#include <stdio.h>

#include "StringTools.hh"

using namespace std;
string 
StringTools::chomp(const string& toChomp) {
    string s = toChomp;
    int begin = s.find_first_not_of(" \t\n\b\r");
    int end = s.find_last_not_of(" \t\n\b\r");
    end++;
     if (begin >= end) {
       return string();
     }
     return s.substr(begin,end - begin);
  }

vector<string> 
StringTools::split(const string& s, const char c) {
    vector<string> v;
    unsigned int i = 0;
    int begin = i;
    int end = i;
    int count = 0;
    while(i < s.size()) {
      while((i < s.size()) && (s[i] == c)) {
	i++;
      }
      begin = i;
      while((i < s.size()) && (s[i] != c)) {
	i++;
      }
      end = i;
      if(end > begin) {
	try {
	  string t = s.substr(begin, end - begin);
	  v.push_back(t); 
	  count++;
	}catch(exception e) {
	  printf("Exception: %s\n", e.what());
	}
      }
    }
    return v;
  }

