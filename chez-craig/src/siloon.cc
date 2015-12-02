// ACL:license
// ----------------------------------------------------------------------
// This software and ancillary information (herein called "SOFTWARE")
// called SILOON is made available under the terms described here.  The
// SOFTWARE has been approved for release with associated LA-CC Number
// LA-CC-98-32.
// 
// Unless otherwise indicated, this SOFTWARE has been authored by an
// employee or employees of the University of California, operator of the
// Los Alamos National Laboratory under Contract No.  W-7405-ENG-36 with
// the U.S. Department of Energy.  The U.S. Government has rights to use,
// reproduce, and distribute this SOFTWARE, and to allow others to do so.
// The public may copy, distribute, prepare derivative works and publicly
// display this SOFTWARE without charge, provided that this Notice and
// any statement of authorship are reproduced on all copies.  Neither the
// Government nor the University makes any warranty, express or implied,
// or assumes any liability or responsibility for the use of this
// SOFTWARE.
// 
// If SOFTWARE is modified to produce derivative works, such modified
// SOFTWARE should be clearly marked, so as not to confuse it with the
// version available from LANL.  
// 
// For more information about SILOON, send e-mail to
// siloon-team@acl.lanl.gov, or visit the SILOON web page at
// http://www.acl.lanl.gov/siloon/.
// ----------------------------------------------------------------------
// ACL:license
#include "siloon.h"
#include "Prototype.h"
#include "Pointer.h"

using namespace Siloon;

#define READ -2
#define WRITE -3

void Siloon::siloon_init(PrototypeMap *&prototypeMap)
{
   prototypeMap = new PrototypeMap();
   registerFunctions(*prototypeMap);
}

int Siloon::siloonUtils(int fid, Buffer& buf, ContextID& target)
{
  int nItems;
  long count, offset;

  switch (fid) {
    case SILOON_READ_C:
    case SILOON_WRITE_C: {
      ServerPointer ptr(buf);
      buf.unpack(&count);
      buf.unpack(&offset);

      if (fid == SILOON_READ_C) {
	buf.reset();		// reset buffer so it can be written to
	nItems = ptr.writeToBuffer(buf, count, offset);
      } else {
	nItems = ptr.readFromBuffer(buf, count, offset);
	buf.reset();		// reset buffer so it can be written to
      }
      break;
    }
    case SILOON_READ_F:
    case SILOON_WRITE_F: {
      long handle;
      buf.unpack(&handle);
      buf.unpack(&count);
      buf.unpack(&offset);
      buf.reset();		// reset buffer so it can be written to

      if (fid == SILOON_READ_F) {
//	nItems = ptr.writeToBuffer(buf, count, offset);
      } else {
//	nItems = ptr.readFromBuffer(buf, count, offset);
      }
      break;
    }
  }	// end switch(fid)
  
  if (nItems != count) return SILOON_FAILURE;
  else		       return SILOON_SUCCESS;
}
