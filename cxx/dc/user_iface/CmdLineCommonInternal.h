#ifdef CmdLineCommonInternal_dependent
#ifndef CmdLineCommonInternal_h_seen
/*
 * headers needed by all CmdLineBuilderView derivatives.
 * Not for external consumption.
 */
#define CmdLineCommonInternal_h_seen
#include "dc/export/config.hh"
#include "util/IO.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif

#include "dc/framework/dc_fwkPublic.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#endif // CmdLineCommonInternal
#endif //CmdLineCommonInternal_dependent
