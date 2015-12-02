#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include "cca.h"
#endif
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"

#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#endif // HAVE_NEO
// #include "port/GUIService.h"
#include <string>
#include <map>
#include "dc/framework/dc_fwkPublic.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"


#include "dc/framework/OpqGUIService.h"

OpqGUIService::OpqGUIService()
{
	frame = 0;
}

OpqGUIService::~OpqGUIService()
{
	frame = 0;
}

void OpqGUIService::load( const ::std::string & arguments)
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

void OpqGUIService::setFrameData(std::map<std::string, void *> *fd)
{
	frame = fd;
}
