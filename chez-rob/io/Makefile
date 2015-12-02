# comment the following line if CCAFE_HOME is defined in your
# environment or in a calling makefile
CCAFE_HOME = ../../cxx
include $(CCAFE_HOME)/Makefile.Rules

%.o : %.C
	$(CXX) -c $(CXXFLAGS)  $<
%.o : %.cxx
	$(CXX) -c $(CXXFLAGS)  $<
CXXSRC = Reader.cxx testReader.cxx BufferedReader.cxx NonblockingReader.cxx \
         testBufferedReader.cxx testNonblockingReader.cxx
CXXOBJ = $(CXXSRC:%.cxx=%.o)

LIB=libdc_fwk.a

all : $(CXXOBJ) lib
	@echo done $(CXXOBJ)

lib $(LIB): $(CXXOBJ)
	@-/bin/rm -f $(LIB)
	ar ruv $(LIB) $(CXXOBJ)
	ranlib $(LIB)

test: all
	$(CXX) -o testReader testReader.o Reader.o 
	$(CXX) -o testBufferedReader testBufferedReader.o BufferedReader.o \
                  Reader.o $(CCAFE_HOME)/jc++/util/libutil.a \
                  $(CCAFE_HOME)/util/IO.o
	$(CXX) -o testNonblockingReader testNonblockingReader.o \
		  NonblockingReader.o \
                  Reader.o $(CCAFE_HOME)/jc++/util/libutil.a \
                  $(CCAFE_HOME)/util/IO.o
clean : 
	rm -f $(CXXOBJ) $(LIB)
