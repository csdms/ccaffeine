
CCAFE_HOME = ../../../..
include $(CCAFE_HOME)/Makefile.Rules

include Makefile.cmpt

BABEL_HOME = $(BABEL_ROOT)
BABEL = $(CCASPEC_BABEL_BABEL)

CLASSIC_HOME = $(CLASSIC_CCA_ROOT)
UNSTAMPER = $(CCAFE_ROOT)/cxx/dc/babel/bin/implUnstamper.sh
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

BABEL_INCLUDE = $(BOOST_INCLUDE) -I$(CCASPEC_BABEL_includedir) \
	$(BABEL_CCA_INC)

INSTALL_LIB = $(CCAFE_HOME)/lib

CXXFLAGS = $(BABEL_INCLUDE) $(CCAFE_INCLUDE) $(CLASSIC_INCL)

LINK_FILES = Makefile.babel

all: .dirs-made .gen-babel .uncruft .make-babel .lib-local-installed

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $<

$(DIRS) .dirs-made : 
	-@mkdir $(SERVER_DIR)
	@if test ! -d $(SERVER_DIR); then \
		echo "Cannot create directory `pwd`/$(SERVER_DIR)" ; \
		exit 1 ; \
	fi
	cp $(LINK_FILES) $(SERVER_DIR)
	touch .dirs-made

babel-copy .babel-copy : $(LINK_FILES) 

babel-symlink .babel-symlink: .dirs-made .babel-copy
	touch .babel-symlink

gen: gen-babel $(CMPT_NAME).depl.cca

gen-babel .gen-babel : .dirs-made .babel-symlink $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) -sdc++ \
		--output-directory=$(SERVER_DIR) --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR) \
		$(PORTFILES) $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(CCA_BABEL_XMLFLAGS)   \
		--output-directory=$(SERVER_DIR) --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR) \
		$(PORTFILES) $(SIDL_FILES)
	$(MAKE) unstamp
	touch .gen-babel

src-list: $(CMPT_NAME).depl.cca
	@(cd $(SERVER_DIR); $(MAKE) -f ../Makefile.babel src-list)

make-babel .make-babel : .gen-babel .depend $(IMPL_FILES)
	(cd $(SERVER_DIR); $(MAKE) -f ../Makefile.babel)
	touch .make-babel

$(CMPT_NAME).depl.cca:
	@$(GENDLINDEX) $(LIB) dummy-create $(FQ_CMPT_NAME) $(CCAFE_RPM_libdir)/ $(FQ_CMPT_NAME) babel > $(CMPT_NAME).cca
	@$(CCASPEC_GENSCLCCA_SH) cca \
		$(CCAFE_RPM_libdir)/$(LTLIB) \
		$(FQ_CMPT_NAME) $(FQ_CMPT_NAME) \
		dynamic global now \
		headers $(pkgincludedir) dc/babel/component/$(CMPT_NAME)/server/$(NAME_SPACE) >$@


lib-install .lib-local-installed : .make-babel $(CMPT_NAME).depl.cca
	if ! [ -d $(INSTALL_LIB) ]; then mkdir -p $(INSTALL_LIB); fi
	$(INSTALL) $(SERVER_DIR)/$(LIB) $(INSTALL_LIB)
	$(INSTALL_DATA) $(CMPT_NAME).depl.cca $(INSTALL_LIB)
	$(INSTALL_DATA) $(CMPT_NAME).cca $(INSTALL_LIB)
	touch .lib-local-installed

.uncruft uncruft : .gen-babel
	touch .uncruft

unstamp:
	$(UNSTAMPER) $(IMPL_FILES)

tester: tester.o
	$(CXX) $(CXXFLAGS) -o tester tester.o -L$(SIDL_LIB_DIR) -lsidl
	LD_LIBRARY_PATH=$(SIDL_LIB_DIR):$(LD_LIBRARY_PATH) ./tester


# do nothing. vpath
copy-back: 
#	-if [ -d server ];then cp `$(IMPLNEWR) --exclusive server . 2>/dev/null` .;fi

clean: 
	-$(RM) *.o tester .babel-copy .babel-symlink .dirs-made \
		.gen-babel .make-babel .uncruft $(CMPT_NAME).cca \
		$(CMPT_NAME).depl.cca .lib-local-installed $(CMPT_NAME).cca
	-$(RM) -r $(SERVER_DIR)

# Not quite clean
cl:
	$(RM)  $(SERVER_DIR)/*.o *.o tester .make-babel  $(CMPT_NAME).depl.cca

.depend depend: .gen-babel .uncruft
	touch $(SERVER_DIR)/Makefile.depends
	(cd $(SERVER_DIR); $(MAKE) -f ../Makefile.babel depend)
	touch .depend

.PHONY: ParameterPortFactoryTest.depl.cca
