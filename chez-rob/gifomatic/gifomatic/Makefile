# CCAFFEINE Makefile by Rob Armstrong and Ben Allan, SNL/CA, 1999,2000
# $Header: /cvs/ccaffeine/repository/dccafe/chez-rob/gifomatic/gifomatic/Makefile,v 1.2 2000/11/03 20:50:01 rob Exp $
SHELL = /bin/sh

# Must be a jdk1.1 compat java
JAVA_HOME = $(HOME)/j/jdk118_v1
HTML_INSTALL_DIR = /home/httpd/html
BROWSER = netscape

JAVAC = $(JAVA_HOME)/bin/javac
JAVAFLAGS = -classpath $(JAVA_HOME)/lib/classes.zip:..
APPLETVIEWER = $(JAVA_HOME)/bin/appletviewer
JAR = $(JAVA_HOME)/bin/jar


%.class : %.java
	$(JAVAC) $(JAVAFLAGS) $<

JAVASRC =   GifGrabber11.java AppletShell11.java 

CLS = $(JAVASRC:%.java=%.class)
NEWCLS = $(NEWSRC:%.java=%.class)

all : symLinks $(CLS)

install:
	-(cd ..;ln -s . gov;ln -s . sandia)
	cp test11.html tst.gif $(HTML_INSTALL_DIR)
	(cd ..;$(JAR) cf gifomatic/gifomatic.jar gov/sandia/gifomatic/*.class)
	cp gifomatic.jar $(HTML_INSTALL_DIR)

test testBrowser:
	$(BROWSER) http://localhost/test11.html

testViewer: all
	$(APPLETVIEWER)  http://localhost/test11.html
.symLinksMade: 
	touch .symLinksMade
symLinks: .symLinksMade
	-cd ..;ln -s . gov
	-cd ..;ln -s . sandia

clean : 
	rm -f $(CLS) *~ \#* $(NEWCLS) .symLinksMake ../gov ../sandia
