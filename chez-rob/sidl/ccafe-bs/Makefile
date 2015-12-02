
BABEL = PATH=/usr/local/babel/bin:/usr/local/java/bin:/usr/local/bin:$$PATH babel

DIRS = server
SIDL_FILES = CcafeBuilderService.sidl

IMPL_FILES = $(shell ls *Impl* 2>/dev/null)

UNCRUFTER = $(shell pwd)/../bin/sidlUncrufter.rb

BABEL_HOME = /usr/local/babel

SIDL_LIB_DIR = $(BABEL_HOME)/lib

SERVER_DIR = ./server
CCA_SERVER_DIR = ../cca/server

CXXFLAGS = -I$(HOME)/src/boost_1_27_0 -I$(BABEL_HOME)/include -I$(CCA_SERVER_DIR) 


all: .dirs-made .gen-babel .uncruft .make-babel

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $<

$(DIRS) .dirs-made : 
	mkdir server client
	touch .dirs-made

babel-copy .babel-copy : (IMPL_FILES) Object.hh
	cp -p  $(IMPL_FILES)                                  \
               Object.hh                                      \
               server/
	touch .babel-copy

gen-babel .gen-babel : .dirs-made $(IMPL_FILES) .babel-copy
	if [ -n "$(IMPL_FILES)" ]; then cp $(IMPL_FILES) server; fi
	$(BABEL) -sC++ -oserver --repository-path ../cca/server $(SIDL_FILES)
	$(BABEL) -cC++ -oclient --repository-path ../cca/server $(SIDL_FILES)
	touch .gen-babel

make-babel .make-babel : .gen-babel .uncruft
	cp Makefile.babel server/Makefile
	(cd server;make)
	touch .make-babel

.uncruft uncruft : .gen-babel
	(cd server; $(UNCRUFTER) --re-to-delete gov_cca --re-to-delete SIDL_ \
               --re-to-delete SIDL\.h )
	touch .uncruft

typeMapTempl:
	typemapGen.rb --overwrite ccaffeine_CcafeTypeMap_Impl.cc

tester: tester.o
	$(CXX) $(CXXFLAGS) -o tester tester.o -L $(SIDL_LIB_DIR) -lsidl
	LD_LIBRARY_PATH=$(SIDL_LIB_DIR):$LD_LIBRARY_PATH ./tester
clean:
	rm -rf client server *.o tester .dirs-made .gen-babel .make-babel .uncruft
