CCAFE_HOME = ../../..
include $(CCAFE_HOME)/Makefile.Rules

include MakeIncl.user

BABEL_HOME = $(BABEL_ROOT)
BABEL = $(CCASPEC_BABEL_BABEL)
	
B2BCPP=$(BABEL_CCA_ROOT)/bin/bld2babel-cpp

UNSTAMPER = $(CCAFE_ROOT)/cxx/dc/babel/bin/implUnstamper.sh
CCA_SERVER_DIR = $(CCASPEC_BABEL_XML_REPOSITORY)
CCAFE_SERVER_DIR= $(CCAFE_ROOT)/cxx/dc/babel/babel-cca/server
BOOST_INCLUDE = $(BOOST_INC)

SIDL_FILES = $(PKG_NAME).sidl

SIDL_LIB_DIR = $(CCASPEC_BABEL_libdir)

CCAFE_INCLUDE = -I$(CCAFE_HOME) $(CCA_INC)

BABEL_INCLUDE = $(BOOST_INC) -I$(CCASPEC_BABEL_includedir) \
	$(BABEL_CCA_INC)

XBABEL_FLAGS=--hide-glue -E

BCXXFLAGS = $(BABEL_INCLUDE) $(CCAFE_INCLUDE) $(CXXFLAGS)

CFLAGS_LOCAL=$(BCXXFLAGS) -I. -I.. -Iglue -I../$(CCAFE_HOME)

all: script-gen babel-gen build

print:
	@echo $(BABEL_INCLUDE)

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $<

INPUT= ./mpitest-input.scr
OUTPUT=mpitest_script_babel
OUTDIR=src

gen:  script-gen babel-gen

bgen script-gen:
	$(B2BCPP) $(INPUT) $(OUTPUT) $(OUTDIR)

src-list:
	(cd src; $(MAKE) $@)

gen-babel babel-gen : $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(XBABEL_FLAGS) -sdc++ \
		--output-directory=src --vpath=src \
		--repository-path $(CCA_SERVER_DIR) \
		--repository-path $(CCAFE_SERVER_DIR) $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(XBABEL_FLAGS) $(CCA_BABEL_XMLFLAGS) \
		--output-directory=xml \
		--repository-path $(CCA_SERVER_DIR) \
		--repository-path $(CCAFE_SERVER_DIR) $(SIDL_FILES)


CCASPEC_INCLUDE_DIR = $(CCASPEC_BABEL_HEADERS)
INCLUDEDIR = $(CCASPEC_BABEL_includedir)
INCLUDEDIR2 = .

build:	build-glue build-impl build-driver link

build-glue:
	(cd src/glue;  $(CC) -c $(CFLAGS_LOCAL) *.c)
	(cd src/glue;  $(CXX) -c $(CFLAGS_LOCAL) *.cc)

build-impl:
	(cd src;  $(CXX) -c $(CFLAGS_LOCAL) *.cc)

build-driver:
	(cd src;  $(CXX) -c $(CFLAGS_LOCAL) driver.cc)

link:
	$(CXX) -o driver.x src/*.o src/glue/*.o \
		$(CFLAGS_LOCAL) $(OTHER_LINK_OBJ) 

clean:
	$(RM) -r *.o tester src/*.o src/glue *.x
	-(cd src; $(MAKE) TARGET=clean clean)
		 
# do nothing.
depend:

# Not quite clean
cl: 
	-$(RM)  src/*.o *.o src/*.guts.hh

