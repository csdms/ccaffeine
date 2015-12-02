# set GPP to the gcc version you want.,possibloy adding -g
GPP=g++

all: clean libs main test

# must be set to result of pwd
LIBDIR=-Wl,-rpath,/home/baallan/work/posthack/dccafe/cxx/util/test
# but only if we want .so to know where they are, which isn't needed
# probably.
LIBDIR=

# we could add:
PORTLIBS=-lsPort $(LIBDIR)
COMPLIBS=-lvComponent $(LIBDIR)
# but we don't need to if we invoke with argx.
COMPLIBS=
PORTLIBS=

libs:
	$(GPP) -shared -g -fPIC vComponentDummy.cc -o libvComponent.so $(LIBDIR)
	$(GPP) -shared -g -fPIC -L. sPortDummy.cc $(COMPLIBS) -o libsPort.so 
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
