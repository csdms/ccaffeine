# Generated automatically from Makefile.in by configure.
#
# Makefile
#
# This file contains a Makefile template which can be modified as
# needed to create a custom python project Makefile.  Normally, one
# should only need to make sure that SILOON_USER_INCLUDES,
# SILOON_USER_LIBRARIES, and SILOON_USER_OBJECTS from ../user.defs
# are correct.
#

# ACL:license
#  ----------------------------------------------------------------------
#  This software and ancillary information (herein called "SOFTWARE")
#  called SILOON is made available under the terms described here.  The
#  SOFTWARE has been approved for release with associated LA-CC Number
#  LA-CC-98-32.
#  
#  Unless otherwise indicated, this SOFTWARE has been authored by an
#  employee or employees of the University of California, operator of the
#  Los Alamos National Laboratory under Contract No.  W-7405-ENG-36 with
#  the U.S. Department of Energy.  The U.S. Government has rights to use,
#  reproduce, and distribute this SOFTWARE, and to allow others to do so.
#  The public may copy, distribute, prepare derivative works and publicly
#  display this SOFTWARE without charge, provided that this Notice and
#  any statement of authorship are reproduced on all copies.  Neither the
#  Government nor the University makes any warranty, express or implied,
#  or assumes any liability or responsibility for the use of this
#  SOFTWARE.
#  
#  If SOFTWARE is modified to produce derivative works, such modified
#  SOFTWARE should be clearly marked, so as not to confuse it with the
#  version available from LANL.  
#  
#  For more information about SILOON, send e-mail to
#  siloon-team@acl.lanl.gov, or visit the SILOON web page at
#  http://www.acl.lanl.gov/siloon/.
#  ----------------------------------------------------------------------
# ACL:license
# Makefile template for the SILOON project
#
# $Id: Makefile,v 1.7 2002/01/15 19:31:48 rasmussn Exp $

#### Start of system configuration section. ####

CCAFE_ROOT = ../..

include ../user.defs

CXX          = $(SILOON_CXX)
AR           = $(SILOON_AR)
SIL_ARFLAGS  = $(SILOON_ARFLAGS)
SIL_DEFS     = $(SILOON_DEFS)

SILOON_INCLUDE  = ../include

SIL_CXXFLAGS = -g
SIL_CPPFLAGS = $(SILOON_USER_INCLUDES) -I$(SILOON_INCLUDE) -I$(PYTHON_INCLUDE)
SIL_LDFLAGS = -L../src

MODULE = cca_siloon

#### End of system configuration section. ####

SHELL = /bin/sh

# Default rule for compiling C++ files.  Some versions of make don't
# automatically recognize the .cc suffix, so add it to .SUFFIXES.
.SUFFIXES: .cc .o
.cc.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFS) -c $(@:.o=.cc)

# We only build the shared library by default.
all: shared

shared: cca_siloon.so

cca_siloon.so: siloon_python.o ../siloon_register.o ../siloon_execute.o
	$(CCAFE_SHLIB_LD) $(CCAFE_SHLIB_LDFLAGS) -o $(MODULE).so $(SIL_LDFLAGS) siloon_python.o ../siloon_register.o ../siloon_execute.o $(SILOON_USER_OBJECTS) -lsiloon $(SILOON_USER_LIBRARIES) -ldl

siloon_python.o: siloon_python.cc
	$(CXX) $(SIL_CXXFLAGS) $(SIL_CPPFLAGS) $(SIL_DEFS) -c $(@:.o=.cc)

mostlyclean: force
	rm -f *~

clean: mostlyclean
	-rm -f *.o *.so *.pyc
	-rm -rf ii_files ti_files

distclean: clean
	rm -f Makefile

force:
