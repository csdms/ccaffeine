IFACE_FILE_NAME = tst

# uncomment one of these:
# This is the standard swig distribution:
 SWIG=/usr/bin/swig
# This is the new one that also does ruby:
# SWIG=/usr/local/bin/swig

SWIG_IFILE = tst.i
SRC = tst.c
OBJ = $(SRC:%.c=%.o)

# Directory into which all of the java-specific files will go.
JAVA_DIR = ./java

# Includes necessary for C to work with your distribution of Java.  This *must* be the same JDK that you are running the JVM from.
JAVA_JNI_INCLUDE = -I/usr/jdk-sun1.2.2/include \
		   -I/usr/jdk-sun1.2.2/include/linux

# The name of the SWIG-generated java class for this interface.
JAVA_SRC = $(SWIG_IFILE:%.i=%.java)
JAVA_CLS = $(JAVA_SRC:%.java=%.class)

# The name of the SWIG-generated JNI wrapper 
JAVA_WRAP = $(JAVA_SRC:%.java=%_wrap.c)
JAVA_OBJ = $(JAVA_WRAP:%.c=%.o)

# The name of the shared library for the C to Java binding 
JAVA_LIB = libtst.so

all_Java : $(JAVA_DIR)/$(JAVA_LIB) $(JAVA_DIR)/$(JAVA_CLS)

doSWIG_Java : $(SRC)
	(cd $(JAVA_DIR);$(SWIG) -java -o $(JAVA_WRAP) \
		../$(SWIG_IFILE))

$(JAVA_DIR) : 
	mkdir $(JAVA_DIR)


$(JAVA_DIR)/$(JAVA_SRC) $(JAVA_DIR)/$(JAVA_WRAP) : $(JAVA_DIR) doSWIG_Java

$(JAVA_DIR)/$(JAVA_OBJ) : $(JAVA_DIR) $(JAVA_DIR)/$(JAVA_WRAP) doSWIG_Java
	(cd $(JAVA_DIR);$(CC) -c $(JAVA_JNI_INCLUDE) $(JAVA_WRAP))

$(JAVA_DIR)/$(JAVA_CLS) : $(JAVA_DIR) $(JAVA_DIR)/$(JAVA_SRC)
	(cd $(JAVA_DIR);javac $(JAVA_SRC))


$(JAVA_DIR)/$(JAVA_LIB) : $(JAVA_DIR) $(OBJ) $(JAVA_DIR)/$(JAVA_OBJ)
	(cd $(JAVA_DIR);ld -shared ../$(OBJ) $(JAVA_OBJ) -o $(JAVA_LIB))


testJava :
	javac RunTst.java
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:"`pwd`"/$(JAVA_DIR) java RunTst


RUBY_DIR = ./ruby
RUBY_WRAP = $(SWIG_IFILE:%.i=%_wrap.c)
RUBY_OBJ = $(RUBY_WRAP:%.c=%.o)
RUBY_LIB = $(SWIG_IFILE:%.i=%.so)
RUBY_INCLUDE = -I/usr/lib/ruby/1.6/i586-linux-gnu/

all_Ruby : $(RUBY_DIR)/$(RUBY_LIB)

$(RUBY_DIR) :
	mkdir $(RUBY_DIR)

doSWIG_Ruby : $(RUBY_DIR) $(SRC)
	(cd $(RUBY_DIR);$(SWIG) -ruby -o $(RUBY_WRAP) \
		../$(SWIG_IFILE))

$(RUBY_DIR)/$(RUBY_WRAP) : doSWIG_Ruby

$(RUBY_DIR)/$(RUBY_OBJ) : $(RUBY_DIR)/$(RUBY_WRAP)
	(cd $(RUBY_DIR);$(CC) -c  $(RUBY_INCLUDE) $(RUBY_WRAP))

$(RUBY_DIR)/$(RUBY_LIB) : $(OBJ) $(RUBY_DIR)/$(RUBY_OBJ)
	(cd $(RUBY_DIR);ld -shared ../$(OBJ) $(RUBY_OBJ) -o $(RUBY_LIB))

testRuby :
	RUBYLIB=`pwd`/ruby ruby RunTst.rb


# Python stuff


PYTHON_DIR = ./python
PYTHON_WRAP = $(SWIG_IFILE:%.i=%_wrap.c)
PYTHON_OBJ = $(PYTHON_WRAP:%.c=%.o)
PYTHON_LIB = $(SWIG_IFILE:%.i=%.so)
PYTHON_INCLUDE = -I/usr/include/python1.5

all_Python : $(PYTHON_DIR)/$(PYTHON_LIB)

doSWIG_Python : $(PYTHON_DIR) $(SRC)
	(cd $(PYTHON_DIR);$(SWIG) -python -o $(PYTHON_WRAP) \
		../$(SWIG_IFILE))

$(PYTHON_DIR) :
	mkdir python

$(PYTHON_DIR)/$(PYTHON_WRAP) : doSWIG_Python

$(PYTHON_DIR)/$(PYTHON_OBJ) : $(PYTHON_DIR)/$(PYTHON_WRAP)
	(cd $(PYTHON_DIR);$(CC) -c  $(PYTHON_INCLUDE) $(PYTHON_WRAP))

$(PYTHON_DIR)/$(PYTHON_LIB) : $(OBJ) $(PYTHON_DIR)/$(PYTHON_OBJ)
	(cd $(PYTHON_DIR);ld -shared ../$(OBJ) $(PYTHON_OBJ) -o $(PYTHON_LIB))

testPython :
	PYTHONPATH=`pwd`/python python RunTst.py


clean:
	rm -f $(OBJ)
	rm -fr java;mkdir java
	rm -fr ruby;mkdir ruby
	rm -fr python;mkdir python

