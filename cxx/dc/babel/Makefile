
# $Revision: 1.7 $
# $Author: baallan $

CCAFE_HOME = ../..

include $(CCAFE_HOME)/Makefile.Rules

ifeq "x$(CCA_USEMPI)" "x1"
MPITEST=mpitest
endif

SUBDIRS = \
	babel-cca   \
	component   \
	ccafe-bind \
	test \
	$(MPITEST)

DEVDIRS = mpitest

all:
	for i in $(SUBDIRS); do if ! (cd $$i;$(MAKE));then exit -1;fi done

src-list:
	@for i in $(SUBDIRS); do \
		echo $$i; \
		if ! (cd $$i;$(MAKE) src-list);then \
			exit -1; \
		fi ; \
	 done

distclean:
	for i in $(SUBDIRS); do if ! (cd $$i;$(MAKE) clean);then exit -1;fi done

depend:
	for i in $(SUBDIRS); do if ! (cd $$i;$(MAKE) depend);then exit -1;fi done

gen install clean uncruft:
	for i in $(SUBDIRS); do if ! (cd $$i;$(MAKE) $@);then exit -1;fi done


# DO NOT DELETE
