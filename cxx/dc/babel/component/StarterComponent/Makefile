CCAFE_HOME = ../../../..
include $(CCAFE_HOME)/Makefile.Rules

include Makefile.cmpt

BABEL_HOME = $(BABEL_ROOT)
BABEL = $(CCASPEC_BABEL_BABEL)

CLASSIC_HOME = $(CLASSIC_CCA_ROOT)
UNCRUFTER = $(RUBY) $(CCAFE_ROOT)/cxx/dc/babel/bin/sidlUncrufter.rb
UNSTAMPER = $(CCAFE_ROOT)/cxx/dc/babel/bin/implUnstamper.sh
IMPLNEWR = $(RUBY) $(CCAFE_ROOT)/cxx/dc/babel/bin/newer.rb
CCA_SERVER_DIR = $(CCASPEC_BABEL_XML_REPOSITORY)
BOOST_INCLUDE = $(BOOST_INC)


LIB = lib$(CMPT_NAME)$(LIBSUFFIX)
LTLIB = lib$(CMPT_NAME)$(VER_SUFFIX)$(PROGRAM_SUFFIX).la

DIRS = server

SIDL_FILES = $(CMPT_NAME).sidl

IMPL_FILES = $(shell ls *Impl* 2>/dev/null)

SIDL_LIB_DIR = $(CCASPEC_BABEL_libdir)


CLASSIC_HOME = $(CLASSIC_CCA_ROOT)

CCAFE_INCLUDE = -I$(CCAFE_HOME) $(CCA_INC)

SERVER_DIR = ./server

BABEL_INCLUDE = \
$(BOOST_INCLUDE) \
-I$(CCASPEC_BABEL_includedir) \
$(BABEL_CCA_INC)

INSTALL_LIB = $(CCAFE_HOME)/lib

BCXXFLAGS = \
$(BABEL_INCLUDE) $(CCAFE_INCLUDE) $(CLASSIC_INCL) \
$(CXXFLAGS)

LINK_FILES = \
Makefile.babel

all: .dirs-made .gen-babel .uncruft .make-babel .lib-local-installed

%.o : %.cc
	$(CXX) -c $(BCXXFLAGS) $<

$(DIRS) .dirs-made : 
	-mkdir server
	-mkdir client
	cp $(LINK_FILES) server/
	touch .dirs-made

#using vpath
babel-copy .babel-copy : $(LINK_FILES) .dirs-made
#	if [ -n "$(LINK_FILES)" ];then cp -p `$(IMPLNEWR) $(LINK_FILES) server` server/;fi;
	@touch .babel-copy

# does nothing. vpath now.
babel-symlink .babel-symlink: .dirs-made
	@touch .babel-symlink

gen: gen-babel $(CMPT_NAME).depl.cca


gen-babel .gen-babel : .dirs-made .babel-symlink $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) -sdc++ \
		--output-directory=server --vpath=`pwd` \
		$(BABEL_OPTS) \
		--repository-path $(CCA_SERVER_DIR) $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(CCA_BABEL_XMLFLAGS) \
		--output-directory=server --vpath=`pwd` \
		$(BABEL_OPTS) \
		--repository-path $(CCA_SERVER_DIR)  $(SIDL_FILES)
	$(MAKE) unstamp
	touch .gen-babel

make-babel .make-babel : .gen-babel .depend $(IMPL_FILES)
	(cd server;$(MAKE) -f ../Makefile.babel)
	touch .make-babel

src-list: $(CMPT_NAME).depl.cca
	@(cd server; $(MAKE) -f ../Makefile.babel src-list)

$(CMPT_NAME).depl.cca:
	@$(GENDLINDEX) $(LIB) dummy-create $(FQ_CMPT_NAME) $(CCAFE_RPM_libdir)/ $(FQ_CMPT_NAME) babel > $(CMPT_NAME).cca
	@$(CCASPEC_GENSCLCCA_SH) cca \
		$(CCAFE_RPM_libdir)/$(LTLIB) \
		$(FQ_CMPT_NAME) $(FQ_CMPT_NAME) \
		dynamic global now \
		headers $(pkgincludedir) dc/babel/component/$(CMPT_NAME)/server/$(NAME_SPACE) >$@


lib-install .lib-local-installed : .make-babel $(CMPT_NAME).depl.cca
	if ! [ -d $(INSTALL_LIB) ]; then mkdir -p $(INSTALL_LIB); fi
	$(INSTALL) server/$(LIB) $(INSTALL_LIB)
	$(INSTALL_DATA) $(CMPT_NAME).depl.cca $(INSTALL_LIB)
	$(INSTALL_DATA) $(CMPT_NAME).cca $(INSTALL_LIB)
	touch .lib-local-installed

#	$(INSTALL_DATA) $(LIB).scl $(INSTALL_LIB)

.uncruft uncruft : .gen-babel
	(cd server; $(UNCRUFTER) --re-to-delete gov_cca --re-to-delete SIDL_ \
	       --re-to-delete SIDL\.h )
	touch .uncruft

unstamp:
	$(UNSTAMPER) $(IMPL_FILES)

typeMapTempl:
	$(RUBY) typemapGen.rb --overwrite ccaffeine_CcafeTypeMap_Impl.cc

tester: tester.o
	$(CXX) $(CXXFLAGS) -o tester tester.o -L $(SIDL_LIB_DIR) -lsidl
	LD_LIBRARY_PATH=$(SIDL_LIB_DIR):$(LD_LIBRARY_PATH) ./tester

# do nothing. vpath now.
copy-back: 

clean: copy-back
	$(RM) -r client server *.o tester .babel-copy .babel-symlink \
		.dirs-made .gen-babel .make-babel .uncruft \
		$(CMPT_NAME).depl.cca .lib-local-installed $(CMPT_NAME).cca

# Not quite clean
cl: copy-back
	$(RM) -r  server/*.o *.o tester .make-babel  $(CMPT_NAME).depl.cca

.depend depend: .gen-babel .uncruft
	touch server/Makefile.depends
	(cd server;$(MAKE) -f ../Makefile.babel depend)
	touch .depend

