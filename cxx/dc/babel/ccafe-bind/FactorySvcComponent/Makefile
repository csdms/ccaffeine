# ==========This points to the Ccaffeine build=======================
CCAFE_ROOT=../../../../..

# ===========This is the name of your component source===============
COMPONENT_SRC = BabelFactoryService.cc
OTHER_SRC = 
# ==================Other things that you may need====================
# make sure that a compatible compiler is first in your path (gcc
# 2.95.3 works) for me it lives in /usr/local/bin.  At any event it
# must be the same compiler with which Ccaffeine itself has been
# built.

# =====================================================================
# For simple situations you should not have to change anything below here
# =====================================================================

zeroth: first

CCAFE_HOME = $(CCAFE_ROOT)/cxx

include $(CCAFE_HOME)/Makefile.Rules
include $(CCAFE_HOME)/MakeIncl.CCAFE_Component

LIBSUFFIX=$(VER_SUFFIX)$(PROGRAM_SUFFIX)$(CCAFE_SHLIB_SUFFIX)


BABEL_HOME = $(BABEL_ROOT)

SIDL_LIB_DIR = $(CCASPEC_BABEL_libdir)
CLASSIC_HOME = $(CLASSIC_CCA_ROOT)

CCAFE_INCLUDE = -I$(CCAFE_HOME) 

BOOST_INCLUDE = $(BOOST_INC)

CCA_SERVER_DIR = $(CCASPEC_BABEL_XML_REPOSITORY)

BABEL_INCLUDE = \
-I$(CCASPEC_BABEL_includedir) $(CCA_INC) $(BABEL_CCA_INC)

LOCALFLAGS = $(BABEL_INCLUDE) $(CCAFE_INCLUDE) $(BOOST_INCLUDE)

WRAPPERFLAGS= -w
WRAPPERFLAGS= 

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $(LOCALFLAGS) $<

%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) $(LOCALFLAGS) $<

%.i : %.cxx
	-$(RM) $@
	$(CXX) $(CPPFLAGS) $(LOCALFLAGS) $< | egrep -v ^$$ |egrep -v '^# ' > $@

%.i : %.cc
	-$(RM) $@
	$(CXX) $(CPPFLAGS) $(LOCALFLAGS) $< | egrep -v ^$$ |egrep -v '^# ' > $@


# stuff built with or without a parallel environment.
OTHEROBJ = \
$(OTHER_SRC:%.cc=%.o) \
$(CCAFE_HOME)/stovepipe/libstovepipe.a \
$(CCAFE_HOME)/util/libcafeutil.a \
$(CCAFE_HOME)/jc++/libjcpp.a \
$(BABEL_CCA_LIBS) \
$(BABEL_LIBS)

CXXSRC = $(COMPONENT_SRC) 


CXXOBJ = $(CXXSRC:%.cc=%.o)
CXXDSSOBJ = $(COMPONENT_SRC:%.cc=libclassic%$(LIBSUFFIX))

$(CXXDSSOBJ) : libclassic%$(LIBSUFFIX) : %.cc
	-$(RM) $@ $*.o $*_wrapper.cc
	$(GENDLWRAPPEROPAQUE) $* > $*_wrapper.cc
	$(GENDLINDEXXML) $@ create_$* $* $(CCAFE_RPM_libdir)/ $* classic > $*.cca
	$(CXX) -c $(CXXFLAGS) $(LOCALFLAGS) $(CCAFE_SHLIB_CFLAGS) $< 
	$(CXX) -c $(CXXFLAGS) $(LOCALFLAGS) $(CCAFE_SHLIB_CFLAGS) \
		$(WRAPPERFLAGS) $*_wrapper.cc
	$(CCAFE_SHLIB_LD) $(CCAFE_SHLIB_LDFLAGS) -o $@ $*.o $*_wrapper.o $(OTHEROBJ)
	-$(RM) $*.o $*_wrapper.o
	chmod 655 $@

lib: $(CXXDSSOBJ)
	touch .make.ok

LIB= libcomponent.a

first all: $(OTHEROBJ) $(CXXDSSOBJ) install
	@echo done $(CXXOBJ) $(JAVACLS) $(JNIHDR)


$(CXXOBJ) : $(CXXSRC)

clean : 
	$(RM) $(CXXOBJ) $(LIB) $(JAVACLS) $(JNIHDR) $(NEWOBJ) \
		*_wrapper.cc *.so *.cca *_wrapper.o *.i *.u \
		runOneProcWGUI CcaffeineRC *.o .make.ok

Makefile.depends:
	touch Makefile.depends

.depend depend: 
	-$(DEPEND) $(CXXFLAGS) $(LOCALFLAGS) $(OTHER_SRC) $(COMPONENT_SRC)
	touch .depend

install: .depend $(CXXDSSOBJ)
	mkdir -p $(CCAFE_HOME)/lib
	$(INSTALL) *.so $(CCAFE_HOME)/lib
	$(INSTALL_DATA) *.cca $(CCAFE_HOME)/lib

runOneProcWGUI: runOneProcWGUI.sed
	sed -e s=\@JAVA\@="$(JAVA)"= <runOneProcWGUI.sed|\
        sed -e s+\@CCA_ROOT\@+"$(CCA_ROOT)"+|\
        sed -e s+\@CCAFE_ROOT\@+"$(CCAFE_ROOT)"+|\
        sed -e s+\@JAVARUNFLAGS\@+"$(JAVARUNFLAGS)"+|\
        sed -e s+\@MPIRUN\@+"$(MPIRUN)"+ >runOneProcWGUI
	chmod a+rx runOneProcWGUI

testStringTools: testStringTools.o StringTools.o
	$(CC) -g -o testStringTools testStringTools.o StringTools.o -lstdc++

ifneq "x$(TARGET)" "xclean"
ifneq "x$(TARGET)" "xdistclean"
include Makefile.depends
endif
endif
