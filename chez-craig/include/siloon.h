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
#ifndef _SILOON_H_
#define _SILOON_H_

#include "siloon_types.h"

namespace Siloon {

class Buffer;
class PrototypeMap;

// offset of return value in Buffer
static const int BufferReturnLocation = 4;

// register public functions
void registerFunctions(PrototypeMap& map);

// remote read and write functions for data array passing
int siloonUtils(int fid, Buffer& buf, ContextID& target); 

// initialize scripting land dispatch
void siloon_init(PrototypeMap *&prototypeMap);

} // namespace Siloon

// send function to the remote target and execute the C++ function
int SiloonInvokeCFunction(Siloon::Buffer& buf, ContextID& target);

// send function to the remote target and execute the Fortran function
int SiloonInvokeFFunction(Siloon::Buffer& buf, ContextID& target);

#endif // _SILOON_H
