#ifndef dc_fwkStar_h_seen
#define dc_fwkStar_h_seen
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "dc/export/config.hh"
#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif // HAVE_CLASSIC
#include "dc/export/ccafeopq.hh"
#include "dc/framework/PropertiesHelper.h"
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/ComponentID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "dc/framework/CmpBox.h"
#include "dc/framework/ComponentInfo.h"
#include "dc/framework/ComponentRecord_Impl.h"
#include "dc/framework/ComponentRegistrar.h" 
#include "dc/framework/StaticFactory.h" 
#include "dc/framework/ComponentFactory.h" 
#include "dc/framework/ServicesHelper.h"
#include "dc/framework/GoThread.hh"
//#include "dc/framework/Frame.h"
#include "dc/framework/ConnectionFramework.h"
#include "dc/framework/OpqBuilderService.h"
#endif // dc_fwkStar_h_seen
