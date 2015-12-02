#ifndef dcfwkPublic_h_seen
#define dcfwkPublic_h_seen

// a header containing enough for practically everyone
// dcfwkStar is massively and incorrectly polluting
// most places it is used.

#include "dc/export/ccafeopq.hh"
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif
#include "dc/framework/ComponentRegistrar.h"
#include "dc/framework/StaticFactory.h"
#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/framework/ComponentID.h"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/Gizzard.h"
#include "dc/framework/CmpBox.h"
#include "dc/framework/ComponentInfo.h"
#include "util/TypeMap.h"
#include "dc/framework/GoThread.hh"
#include "dc/framework/ConnectionFramework.h"

#endif // dcfwkPublic_h_seen
