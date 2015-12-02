#===============Begin things you might want to change======================

# Steve, Kenneth, Dennis: you need to change this to be the cca-spec
# in your area.  To be safe, you can check it out from:
#
# cvs -d :ext:<you>@z.ca.sandia.gov:/home/ccastd/repository checkout cca-spec
#
# Change the following to point to where this is:
CCA_ROOT = /home/rob/cca/cca-spec

CCA_INCLUDE = -I$(CCA_ROOT)/cxx/include

# Change this to be whatever, I defer to Steve.
CXX = g++

CXXFLAGS = $(CCA_INCLUDE)


# Includes necessary for C to work with your distribution of Java.
# This *must* be the same JDK that you are running the JVM from.

JAVA_JNI_INCLUDE = -I/usr/jdk-sun1.2.2/include \
		   -I/usr/jdk-sun1.2.2/include/linux

JAVAC = /usr/jdk-sun1.2.2/bin/javac

# uncomment one of these:
# This is the standard swig distribution:
 SWIG=/usr/bin/swig
# This is the new one that also does ruby:
# SWIG=/usr/local/bin/swig

#===============End things you might need to change==========================

%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) $<

SWIGFLAGS= -c++ -shadow

SWIG_IFILE = BuilderSvc.i
SRC = DefaultBuilderService.cxx DefaultComponentID.cxx
OBJ = $(SRC:%.cxx=%.o)
OBJFROMBELOW = $(OBJ:%.o=../%.o)


libobj : $(OBJ)

# Directory into which all of the java-specific files will go.
JAVA_DIR = ./java

# The name of the SWIG-generated java class for this interface.
JAVA_SRC = $(SWIG_IFILE:%.i=%.java)
JAVA_CLS = $(JAVA_SRC:%.java=%.class)

# The name of the SWIG-generated JNI wrapper 
JAVA_WRAP = $(JAVA_SRC:%.java=%_wrap.c)
JAVA_OBJ = $(JAVA_WRAP:%.c=%.o)

# The name of the shared library for the C to Java binding 
JAVA_LIB = libBuilderSvc.so

all_Java : $(JAVA_DIR)/$(JAVA_LIB) $(JAVA_DIR)/$(JAVA_CLS)

doSWIG_Java : $(SWIG_IFILE) $(JAVA_DIR)
	(cd $(JAVA_DIR);$(SWIG) $(SWIGFLAGS) -java -o $(JAVA_WRAP) \
		../$(SWIG_IFILE))

$(JAVA_DIR) : 
	mkdir $(JAVA_DIR)


$(JAVA_DIR)/$(JAVA_SRC) $(JAVA_DIR)/$(JAVA_WRAP) : $(JAVA_DIR) doSWIG_Java

$(JAVA_DIR)/$(JAVA_OBJ) : $(JAVA_DIR) $(JAVA_DIR)/$(JAVA_WRAP) doSWIG_Java
	(cd $(JAVA_DIR);$(CXX) -c $(CXXFLAGS) $(JAVA_JNI_INCLUDE) $(JAVA_WRAP))

$(JAVA_DIR)/$(JAVA_CLS) : $(JAVA_DIR) $(JAVA_DIR)/$(JAVA_SRC)
	(cd $(JAVA_DIR);$(JAVAC) *.java)


$(JAVA_DIR)/$(JAVA_LIB) : $(JAVA_DIR) $(OBJ) $(JAVA_DIR)/$(JAVA_OBJ)
	(cd $(JAVA_DIR);g++ -shared $(OBJFROMBELOW) $(JAVA_OBJ) -o $(JAVA_LIB))

testJava : $(JAVA_DIR)/$(JAVA_LIB)
	cp RunTest.java $(JAVA_DIR)
	(cd $(JAVA_DIR);$(JAVAC) RunTest.java)
	(cd $(JAVA_DIR); LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:"`pwd`"/$(JAVA_DIR) java RunTest)


clean :
	rm -fr java
	rm $(OBJ)

