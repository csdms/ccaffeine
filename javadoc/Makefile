#Makefile for /home/pvwall/sandia/dccafe/javadoc
#should do all of the javadoc stuff
#
#
#
# update Makefile.conf
# then type 'make'
#
# DO NOT put hand crafted html in this directory it will be blown away
# by the clean target.

CCAFE_HOME = ../java
include $(CCAFE_HOME)/Makefile.Rules

all: doc

clean:
	-$(RM) -rf cca *.html package-list stylesheet.css gnu gov


CCA_HOME = ..

JAVAC = javac
#JAVADOCFLAGS = -classpath $(CLASSPATH):$(CCA_HOME)/java
JAVADOCFLAGS = -classpath $(JPATH) 
JAVADOC = javadoc -private

CCAPACK=cca

PACKAGES = gov.sandia.ccaffeine.cmd \
gov.sandia.ccaffeine.dc.kernel \
gov.sandia.ccaffeine.dc.framework \
gov.sandia.ccaffeine.dc.port \
gov.sandia.ccaffeine.dc.std_iface \
gov.sandia.ccaffeine.dc.user_iface \
gov.sandia.ccaffeine.dc.user_iface.gui \
gov.sandia.ccaffeine.dc.user_iface.gui.guicmd \
gov.sandia.ccaffeine.dc.user_iface.applet \
gov.sandia.ccaffeine.dc.user_iface.ccacmd \
gov.sandia.ccaffeine.esi \
gnu.getopt \
gov.sandia.ccaffeine.parameters \
gov.sandia.ccaffeine.port \
gov.sandia.ccaffeine.util \
gov.cca \
gov.cca.ports
# gov.sandia.ccaffeine.dc.distributed \
# gov.sandia.ccaffeine.dc.component \


doc: 
	$(JAVADOC) $(JAVADOCFLAGS) -d . $(PACKAGES)




