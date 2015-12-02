// if this is defined a variety of spew occurs via IO_dn*
// and all users of this header have access to IO_dn automatically.
#define CCAFE_AUDIT CCAFE_SPEW

#include "dc/export/ccafeopq.hh"

/* the next header belongs elsewhere, but we
 * don't have time to move it at the moment.
 */
#include "dc/export/OpqPortInfo.hh"
#include "dc/export/oldPorts.hh"
#include "dc/export/paramPorts.hh"
#include "dc/export/ccafeopq_support.hh"
// the next file should live in ccafeopq_support somehow
#include "dc/framework/KernelPort.h"

#ifdef CCAFE_AUDIT
#if CCAFE_AUDIT == 1
#include "util/IO.h"
#else
#undef CCAFE_AUDIT
#endif
#endif
