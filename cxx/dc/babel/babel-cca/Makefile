
CCAFE_HOME=../../..
include $(CCAFE_HOME)/Makefile.Rules

ifneq ($(CCAFE_BUILD_PY),) # is it empty?
BUILD_PY = .gen-babel-py
endif

BABEL_HOME = $(BABEL_ROOT)
BABEL = $(CCASPEC_BABEL_BABEL)

DIRS = server
SIDL_FILES = ccafe.sidl
LIB = server/libccaffeine$(VER_SUFFIX)$(PROGRAM_SUFFIX)$(CCAFE_SHLIB_SUFFIX)
LIBA = server/libccaffeine$(VER_SUFFIX)$(PROGRAM_SUFFIX).a

DEPRECATED=

IMPL_FILES = \
     ccaffeine_ports_GUIServiceWrap_Impl.cc \
     ccaffeine_ports_GoPortWrap_Impl.cc \
     ccaffeine_ports_ServiceRegistryWrap_Impl.cc \
     ccaffeine_CCAException_Impl.cc  \
     ccaffeine_CCAException_Impl.hh  \
     ccaffeine_ComponentClassDescription_Impl.cc  \
     ccaffeine_ComponentClassDescription_Impl.hh  \
     ccaffeine_ComponentID_Impl.cc  \
     ccaffeine_ComponentID_Impl.hh  \
     ccaffeine_ConnectionEventService_Impl.cc  \
     ccaffeine_ConnectionEventService_Impl.hh  \
     ccaffeine_ConnectionID_Impl.cc  \
     ccaffeine_ConnectionID_Impl.hh  \
     ccaffeine_ports_BuilderService_Impl.cc  \
     ccaffeine_ports_BuilderService_Impl.hh  \
     ccaffeine_ports_ComponentRepository_Impl.cc  \
     ccaffeine_ports_ComponentRepository_Impl.hh  \
     ccaffeine_ports_ConnectionEvent_Impl.cc  \
     ccaffeine_ports_ConnectionEvent_Impl.hh  \
     ccaffeine_ports_PortTranslator_Impl.cc  \
     ccaffeine_ports_PortTranslator_Impl.hh  \
     ccaffeine_ports_BasicParameterPortWrap_Impl.cc \
     ccaffeine_ports_BasicParameterPortWrap_Impl.hh \
     ccaffeine_ports_ParameterPortWrap_Impl.cc \
     ccaffeine_ports_ParameterPortWrap_Impl.hh \
     ccaffeine_ports_ParameterPortFactoryWrap_Impl.cc \
     ccaffeine_ports_ParameterPortFactoryWrap_Impl.hh \
     ccaffeine_Services_Impl.cc  \
     ccaffeine_Services_Impl.hh  \
     ccaffeine_TypeMap_Impl.cc  \
     ccaffeine_TypeMap_Impl.hh  \
     ccaffeine_TypeMismatchException_Impl.cc  \
     ccaffeine_TypeMismatchException_Impl.hh  \
     ccaffeine_AbstractFramework_Impl.cc  \
     ccaffeine_AbstractFramework_Impl.hh  \


UNCRUFTER = $(RUBY) $(shell pwd)/../bin/sidlUncrufter.rb
UNSTAMPER = $(shell pwd)/../bin/implUnstamper.sh


SIDL_LIB_DIR = $(CCASPEC_BABEL_libdir)

CLASSIC_HOME = $(CLASSIC_CCA_ROOT)

CCAFE_INCLUDE = -I$(CCAFE_HOME) $(CCA_INC)

SERVER_DIR = ./server
CCA_SERVER_DIR = $(CCASPEC_BABEL_XML_REPOSITORY)

LOCAL_FLAGS=$(BABEL_CCA_INC) -I$(CCASPEC_BABEL_includedir)

COPY_FILES = allCcaffeine.hh Makefile.babel

all: .lib-local-installed $(BUILD_PY)

debug:
	echo $(BUILD_PY)

%.o : %.cc
	(cd server; $(MAKE) -f ../Makefile.babel $@)

%.i : %.cc
	(cd server; $(MAKE) -f ../Makefile.babel $@)

$(DIRS) .dirs-made : 
	-mkdir server
	-mkdir client
	-mkdir py-client
	cp $(COPY_FILES) server/
	touch .dirs-made

gen: gen-babel

src-list:
	@(cd server; $(MAKE) -f ../Makefile.babel src-list)

gen-babel .gen-babel : .dirs-made $(SIDL_FILES) 
	$(BABEL) $(BABEL_FLAGS) -sdc++ \
		--output-directory=server --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR) $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(CCA_BABEL_XMLFLAGS) \
		--output-directory=server --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR)  $(SIDL_FILES)
	$(MAKE) unstamp
	touch .gen-babel

# Generates the Python client for Ccaffiene needed for BuilderService

INCLUDEDIR = $(CCASPEC_BABEL_includedir)
INCLUDEDIR2 = .
SIDLPYTHONLIB = $(CCASPEC_BABEL_libdir)
PYTHON_VERSION = $(CCASPEC_BABEL_PYTHON_VERSION)
BABEL_RUNTIME_INCLUDE = $(INCLUDEDIR)/python$(PYTHON_VERSION)/babel
CCASPEC_PYTHON_INCLUDE_DIR = $(BABEL_CCA_ROOT)/include/python$(PYTHON_VERSION)/babel

gen-babel-py .gen-babel-py :  $(SIDL_FILES) .dirs-made .gen-babel .make-babel
	(cd py-client;$(BABEL) -cpython \
		--repository-path $(CCA_SERVER_DIR) -E ../$(SIDL_FILES) )
	(cd py-client; python setup.py \
	  --include-dirs=$(CCASPEC_BABEL_PYTHONINC) \
	  --include-dirs=$(INCLUDEDIR) \
	  --include-dirs=$(INCLUDEDIR2)	\
	  --include-dirs=$(BABEL_RUNTIME_INCLUDE) \
	  --include-dirs=$(CCASPEC_pkgincludedir) \
	  --include-dirs=$(CCASPEC_PYTHON_INCLUDE_DIR) \
	  --library-dirs=$(SIDLPYTHONLIB) \
	  build_ext --inplace --force )
	touch .gen-babel-py



unstamp:
	$(UNSTAMPER) $(IMPL_FILES)

make-babel .make-babel : .gen-babel .uncruft .depend $(IMPL_FILES)
	(cd server;$(MAKE) -f ../Makefile.babel)
	touch .make-babel

install-lib .lib-local-installed : .make-babel $(LIB) $(LIBA) 
	$(INSTALL) $(LIB) $(CCAFE_HOME)/lib
	$(INSTALL_DATA) $(LIBA) $(CCAFE_HOME)/lib
	touch .lib-local-installed

.uncruft uncruft : .gen-babel
	(cd server; $(UNCRUFTER) --re-to-delete gov_cca --re-to-delete sidl_ \
               --re-to-delete sidl\.h )
	touch .uncruft

typeMapTempl:
	$(RUBY) typemapGen.rb --overwrite ccaffeine_CcafeTypeMap_Impl.cc

tester: tester.o
	$(CXX) $(CXXFLAGS) -o tester tester.o -L $(SIDL_LIB_DIR) -lsidl
	LD_LIBRARY_PATH=$(SIDL_LIB_DIR):$(LD_LIBRARY_PATH) ./tester
copy-back: 
	-if [ -d server ]; then cp `$(RUBY) ../bin/newer.rb --exclusive server .` .; fi

clean: 
	$(RM) -rf client server *.o tester .babel-copy .lib-local-installed .dirs-made .gen-babel .make-babel .uncruft .depend py-client .install-babel-py .gen-babel-py

# Not quite clean
cl: 
	$(RM) -rf server/*.o tester .lib-local-installed .make-babel 


.depend depend: .gen-babel .uncruft
	touch server/Makefile.depends
	(cd server;$(MAKE) -f ../Makefile.babel depend)
	touch .depend
