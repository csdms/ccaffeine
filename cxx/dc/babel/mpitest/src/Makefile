CCAFE_HOME = ../../../..
include $(CCAFE_HOME)/Makefile.Rules

ifneq "x$(TARGET)" "xclean"
include babel.make
include glue/babel.make
endif
CMPT_NAME=mpitest

SRC = $(IMPLSRCS)
GLUE_SRC_CXX= $(SKELSRCS) $(STUBSRCS)

OUTSRC=  tee -a src-list-driver >>  ../../../src-list
HERE=$(CCAFE_ROOT)/cxx/dc/babel/mpitest/src

UNSTAMPER = $(CCAFE_ROOT)/cxx/dc/babel/bin/implUnstamper.sh
IMPL_FILES = $(shell ls *Impl* 2>/dev/null)
 
unstamp:
	$(UNSTAMPER) $(IMPL_FILES)

src-list:
	@$(RM) src-list-driver
	@echo "BABEL_TESTS += mpitest" | $(OUTSRC)
	@echo 'ifeq "x$$(CMPT)" "x$(CMPT_NAME)"' | $(OUTSRC)
	@echo "CMPT_LIST_CXX = \\" | $(OUTSRC)
	@for i in $(SRC) ; do \
                echo "$(CCAFE_ROOT)/cxx/dc/babel/mpitest/src/$$i \\" | $(OUTSRC) ; \
        done
	@for i in $(GLUE_SRC_CXX); do \
                echo "$(CCAFE_ROOT)/cxx/dc/babel/mpitest/src/glue/$$i \\" | $(OUTSRC) ; \
        done
	@echo "" | $(OUTSRC)
	@echo "CMPT_LIST_CC = \\" | $(OUTSRC)
	@for i in $(IORSRCS); do \
                echo "$(CCAFE_ROOT)/cxx/dc/babel/mpitest/src/glue/$$i \\" | $(OUTSRC) ; \
        done
	@echo "" | $(OUTSRC) 
	@echo "CMPT_CXXFLAGS=-I$(HERE) \\" | $(OUTSRC)
	@echo "-I$(HERE)/glue \\" | $(OUTSRC)
	@echo "-I$(CCAFE_ROOT)/cxx/dc/babel/babel-cca/server" | $(OUTSRC)
	@echo "" | $(OUTSRC)
	@echo "CMPT_CFLAGS=-I$(HERE)/glue \\" | $(OUTSRC)
	@echo "-I$(CCAFE_ROOT)/cxx/dc/babel/babel-cca/server" | $(OUTSRC)
	@echo "" | $(OUTSRC)
	@echo "CMPT_COMPLIBS=StarterComponent PrinterComponent ParameterPortFactoryTest StringConsumerPort MPIComponent" | $(OUTSRC)
	@echo "endif" | $(OUTSRC)
	@cat src-list-driver | sed -e 's%^CMPT%$(CMPT_NAME)_CMPT%g' > src-list-driver2
	@$(RM) src-list-driver
	@cp src-list-driver2 src-list-driver
	@$(RM) src-list-driver2

	@echo "updated src-list from dc/babel/mpitest/src"

clean:
	-@$(RM) src-list-driver
