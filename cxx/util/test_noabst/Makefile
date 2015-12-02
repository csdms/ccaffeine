# set GPP to the gcc version you want.,possibloy adding -g
# usepv should be 1 or 0
INTEL=1
USEPV=0
USEPRAG=0
SCHEME=1
ifeq "$(INTEL)" "1"
PDIR=/home/baallan/work/posthack/ccafe-i7/cxx/util/test_noabst
MYFLAGS= -w0 -DUSEPV=$(USEPV) -DUSEPRAG=$(USEPRAG)
GPP=icpc $(MYFLAGS)
else
PDIR=/home/baallan/work/posthack/dccafe/cxx/util/test_noabst
MYFLAGS= -Wall -Wmissing-braces -Weffc++ -DUSEPV=$(USEPV) -DUSEPRAG=$(USEPRAG)
GPP=g++ $(MYFLAGS)
endif

all: clean libs main test

ifeq "$(SCHEME)" "1"
# must be set to result of pwd
LIBDIR=-Wl,-rpath,$(PDIR)
else
# but only if we want .so to know where they are, which isn't needed
# probably.
LIBDIR=
endif



# so, for gcc 3.2, mysoflags makes no difference.
# what matters is the sPort not being a pure base
# and the .so for the nonpure base being linked
# in to both .so Foo , Bar
# ld = 2.11.93.0.2
# ldd =  2.2.5
# probably ld(d) matters a lot, too.
ifeq "$(SCHEME)" "1"
# we could add:
#MYSOFLAGS=-Wl,-E
PORTLIBS=-lsPort $(LIBDIR)
COMPLIBS=-lvComponent $(LIBDIR)
else
# but we don't need to if we invoke with argx.
MYSOFLAGS=
COMPLIBS=
PORTLIBS=
endif

#	$(GPP) -shared -g -fPIC -L. sPortDummy.cc $(COMPLIBS) -o libsPort.so 
libs:
	$(GPP) -shared -g -fPIC vComponentDummy.cc -o libvComponent.so $(LIBDIR)
	$(GPP) -shared -g -fPIC -L. sPort.cc $(COMPLIBS) -o libsPort.so 
	$(GPP) -shared -g -fPIC -L. foo.cc -o libFoo.so $(PORTLIBS)
	$(GPP) -shared -g -fPIC -L. bar.cc -o libBar.so $(PORTLIBS)

EXTRA=-L. -g $(COMPLIBS)
# at runtime, load these libraries. note all virtual interfaces
# are explicitly required. they will not chain themselves.
ARGX=./libvComponent.so ./libsPort.so
# the empty case, which will fail.
NOARGX=

TEST1=-D_DL_LG
TEST2=-D_DL_GL
TEST3=-D_DL_LL
TEST4=-D_DL_GG
TEST=$(TEST4)

main:
	$(GPP) $(TEST1) -I. -I.. -I../.. -rdynamic cppDLTest.cc -o dltestLG.x $(EXTRA) ../libcafeutil.a -ldl
	$(GPP) $(TEST2) -I. -I.. -I../.. -rdynamic cppDLTest.cc -o dltestGL.x $(EXTRA) ../libcafeutil.a -ldl
	$(GPP) $(TEST3) -I. -I.. -I../.. -rdynamic cppDLTest.cc -o dltestLL.x $(EXTRA) ../libcafeutil.a -ldl
	$(GPP) $(TEST4) -I. -I.. -I../.. -c cppDLTest.cc
	$(GPP) $(TEST4) -I. -I.. -I../.. -rdynamic cppDLTest.o -o dltestGG.x $(EXTRA) ../libcafeutil.a -ldl

# test the interface loading approach
test:
	@echo '_____________local-global_______________'
	-./dltestLG.x $(ARGX)
	@echo '__________________global-local_______________'
	-./dltestGL.x $(ARGX)
	@echo '__________________local-local_______________'
	-./dltestLL.x $(ARGX)
	@echo '__________________global-global_______________'
	-./dltestGG.x $(ARGX)

testno:
	@echo '_____________local-global_______________'
	-./dltestLG.x $(NOARGX)
	@echo '__________________global-local_______________'
	-./dltestGL.x $(NOARGX)
	@echo '__________________local-local_______________'
	-./dltestLL.x $(NOARGX)
	@echo '__________________global-global_______________'
	-./dltestGG.x $(NOARGX)

clean:
	$(RM) *.o *.a *.x *.so core*
