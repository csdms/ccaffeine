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

dead:
	@echo "babel/component/ParameterDialogServiceTest retired"

LIB = lib$(CMPT_NAME)$(LIBSUFFIX)

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
	@touch .dirs-made

# just stomp whatever is in there.
babel-copy .babel-copy : $(LINK_FILES)
#
# nothing. vpath now
babel-symlink .babel-symlink: .dirs-made .babel-copy
	touch .babel-symlink

gen: gen-babel $(CMPT_NAME).depl.cca

gen-babel .gen-babel : .dirs-made .babel-symlink $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) -sdc++ \
		--output-directory=$(SERVER_DIR) --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR) $(SIDL_FILES)
	$(BABEL) $(BABEL_FLAGS) $(CCA_BABEL_XMLFLAGS) \
		--output-directory=$(SERVER_DIR) --vpath=`pwd` \
		--repository-path=$(CCA_SERVER_DIR)  $(SIDL_FILES)
	$(MAKE) unstamp
	@touch .gen-babel

make-babel .make-babel : .gen-babel .babel-copy .depend $(IMPL_FILES)
	(cd server; $(MAKE) -f ../Makefile.babel)
	@touch .make-babel

$(CMPT_NAME).depl.cca:
	@$(GENDLINDEX) $(LIB) dummy-create $(FQ_CMPT_NAME) $(CCAFE_RPM_libdir)/ $(FQ_CMPT_NAME) babel > $(CMPT_NAME).cca
	@$(CCASPEC_GENSCLCCA_SH) cca \
		$(CCAFE_RPM_libdir)/$(LIB) \
		$(FQ_CMPT_NAME) $(FQ_CMPT_NAME) \
		dynamic global now \
		headers $(pkgincludedir) dc/babel/component/$(CMPT_NAME)/server/$(NAME_SPACE) >$@

#	$(CCASPEC_GENSCLCCA_SH) scl $(CCAFE_RPM_libdir)/$(LIB) $(FQ_CMPT_NAME) $(FQ_CMPT_NAME) dynamic global now > $(LIB).scl

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

tester: tester.o
	$(CXX) $(CXXFLAGS) -o tester tester.o -L $(SIDL_LIB_DIR) -lsidl
	LD_LIBRARY_PATH=$(SIDL_LIB_DIR):$(LD_LIBRARY_PATH) ./tester


# do nothing. now using babel vpath.
copy-back: 
# cp `$(IMPLNEWR) --exclusive server . 2>/dev/null` .; \

clean: copy-back
	-$(RM) *.o tester .babel-copy .babel-symlink .dirs-made \
		.gen-babel .make-babel .uncruft $(CMPT_NAME).depl.cca \
		$(CMPT_NAME).depl.scl \
		$(CMPT_NAME).depl.cca .lib-local-installed $(CMPT_NAME).cca \
	-$(RM) -r server

# Not quite clean
cl: copy-back
	$(RM)  server/*.o *.o tester .make-babel  $(CMPT_NAME).depl.cca

.depend depend: .gen-babel .uncruft
	touch $(SERVER_DIR)/Makefile.depends
	(cd $(SERVER_DIR); $(MAKE) -f ../Makefile.babel depend)
	touch .depend

