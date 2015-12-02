#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include "cca.h"
#endif
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"

#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#endif // HAVE_NEO
#include "port/GUIService.h"
#include <string>
#include <map>
#include "dc/framework/dc_fwkPublic.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"


#include "dc/port/DefaultGUIService.h"

DefaultGUIService::DefaultGUIService()
{
	frame = 0;
}

DefaultGUIService::~DefaultGUIService()
{
	frame = 0;
}

void DefaultGUIService::load( ::std::string & arguments)
{
	if (frame != 0) 
	{
		void *bv;
		CmdLineBuilderView *clbv = 0;
		bv = (*frame)["CmdLineBuilderView"];	
		clbv = static_cast<CmdLineBuilderView *>(bv);
		clbv->p("load ");
		const char *args = arguments.c_str();
		clbv->pn(args);
	}
}

void DefaultGUIService::setFrameData(std::map<std::string, void *> *fd)
{
	frame = fd;
}
