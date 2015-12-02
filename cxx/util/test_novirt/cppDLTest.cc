#define CONST const
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "ascDynaLoad.h"
#include <dlfcn.h>

#ifndef CCA_DL_SUFFIX
#define CCA_DL_SUFFIX ".so"
#endif

#include "vComponent.hh"
#define C1 "Foo"
#define C2 "Bar"
#define SOEXT "so"

// typedef ((vComponent *)( * )()) conFunc;
// typedef (void *(*)()) myctor;

using namespace std;

/**
python being all C, it shouldn't care that we
are opening c++ symbols into main behind its back.

This c function we could wrap with python
and use to dlopen the c++ dummy port interface .so files
to get the vtables into the global namespace without
python knowing or caring.
*/
void interface_load(int argc, char **argv)
{
  const char *erm;
  if (argc > 1)
  {
	for (int i = 1; i < argc; i++) {
		dlopen(argv[i],(RTLD_GLOBAL|RTLD_NOW));
		erm = dlerror();
		if (erm != 0) {
			fprintf(stderr, "%s: %s\n",argv[i],erm);
		}
  	}
  }
}

// -D$VER should be compiled, where VER is exactly one of
// _DL_GG _DL_GL _DL_LG _DL_LL
int main(int argc, char **argv)
{
    string f1 = "./lib"C1"."SOEXT;
    string f2 = "./lib"C2"."SOEXT;
    string ifun = "create";
    int i = 0;
    void *lib1 = 0, *lib2 = 0;
    interface_load(argc,argv);
#ifdef _DL_GG
    // load global now verbose
    lib1 = CCA_IntrospectLibrary(f1.c_str(), ifun.c_str(), 0, 1, 0, 1, 1);
    lib2 = CCA_IntrospectLibrary(f2.c_str(), ifun.c_str(), 0, 1, 0, 1, 1);
    i = 1;
#endif
#ifdef _DL_LL
    // load local now verbose
    lib1 = CCA_IntrospectLibrary(f1.c_str(), ifun.c_str(), 1, 0, 0, 1, 1);
    lib2 = CCA_IntrospectLibrary(f2.c_str(), ifun.c_str(), 1, 0, 0, 1, 1);
    i = 2;
#endif
#ifdef _DL_LG
    // load first local second global now verbose
    lib1 = CCA_IntrospectLibrary(f1.c_str(), ifun.c_str(), 1, 0, 0, 1, 1);
    lib2 = CCA_IntrospectLibrary(f2.c_str(), ifun.c_str(), 0, 1, 0, 1, 1);
    i = 3;
#endif
#ifdef _DL_GL
    // load first global second local  now verbose
    lib1 = CCA_IntrospectLibrary(f1.c_str(), ifun.c_str(), 0, 1, 0, 1, 1);
    lib2 = CCA_IntrospectLibrary(f2.c_str(), ifun.c_str(), 1, 0, 0, 1, 1);
    i = 4;
#endif
    if (i == 0) {
        std::cerr << "compiled without one of _DL_GG _DL_GL _DL_LG _DL_LL. bye " << std::endl;
        exit(1);
    }
    void *(*con1)();
    void *(*con2)();
    con1 = (void *(*)())lib1;
    con2 = (void *(*)())lib2;
    vComponent * cp1 = (vComponent *)con1();
    vComponent * cp2 = (vComponent *)con2();
    vPort *vp1 = cp1->getPort();
    vPort *vp2 = cp2->getPort();
    if (cp2->checkPort(vp1)) {
        cout << "port on 1 converted ok." << endl;
    } else {
        cerr << "port on 1 conversion bogosity." << endl;
        return 1;
    }

    if (cp1->checkPort(vp2)) {
        cout << "port on 2 converted ok." << endl;
    } else {
        cerr << "port on 2 conversion bogosity." << endl;
        return 1;
    }
    return 0;
}
