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
#
# $Id: Makefile,v 1.2 2002/01/15 19:27:17 rasmussn Exp $

#### Start of system configuration section. ####

CCAFE_ROOT = ../..

include ../user.defs

CXX      = $(SILOON_CXX)
AR       = $(SILOON_AR)
ARFLAGS  = $(SILOON_ARFLAGS)
DEFS     = $(SILOON_DEFS)

SILOON_INCLUDE  = ../include

CXXFLAGS = $(SILOON_CXX_FLAGS)
CPPFLAGS = $(SILOON_USER_INCLUDES) -I$(SILOON_INCLUDE) -I$(PDT_INCLUDE)

#### End of system configuration section. ####

SHELL = /bin/sh

all: libsiloon.a

SRCS = Buffer.cc Pointer.cc Prototype.cc Type.cc siloon.cc
OBJS = $(SRCS:.cc=.o)

# Default rule for compiling C++ files.  Some versions of make don't
# automatically recognize the .cc suffix, so add it to .SUFFIXES.
.SUFFIXES: .cc .o
.cc.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFS) -c $(@:.o=.cc)

libsiloon.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
	$(RANLIB) libsiloon.a

clean: force
	rm -f *~ *.o *.a
	rm -rf ii_files ti_files 

distclean: clean

force:
