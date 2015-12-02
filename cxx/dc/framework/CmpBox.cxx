
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>

#include "parameters/parametersStar.h"
#include "util/IO.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"

#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/GizzardComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#endif // HAVE_CLASSIC
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "dc/framework/CmpBox.h"

#include "dc/export/AllExport.hh"

#include "util/TypeMap.h"

// #include "util/freefree.h"
#include <assert.h>

namespace {
char id[]=
"$Id: CmpBox.cxx,v 1.12 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

  //======================================================================
  //======================================================================
namespace {
	void whine( ::ccafeopq::ExceptionType et, const ::std::string & msg)  throw ( ::ccafeopq::Exception )
	{
		throw  ::ccafeopq::Exception(et, msg);
	}

	 void whinel( const char * msg)  throw ( ::ccafeopq::Exception )
	 { 
		 throw  ::ccafeopq::Exception(msg);
	 }

	 void whine( const ::std::string & msg)  throw ( ::ccafeopq::Exception )
	 { 
		 throw  ::ccafeopq::Exception(msg);
	 }

}

ccafe::CmpBox::CmpBox()
{
	giz = 0;
	comp = 0;
	cname = "";
	ctype = "";
	internal = false;
	IO_dn1("CmpBox CTOR empty");
}

ccafe::CmpBox::CmpBox(ccafeopq::Component * comp_, Gizzard * giz_, const std::string & name_) {
	if (giz_ == 0 || name_.size() == 0 || comp_ == 0) { 
		whine("CmpBox for ccafeopq::Component constructed with bogus input");
		exit(1);
	}
	giz = giz_;
	comp = comp_;
	cname = name_;
	ctype = "";
	internal = true;
	IO_dn2("CmpBox CTOR %s",name_.c_str());
}

ccafe::CmpBox::CmpBox(Gizzard * giz_, const std::string & name_) {
	if (giz_ == 0 || name_.size() == 0 ) { 
		whine("CmpBox for external Component constructed with bogus input");
		exit(1);
	}
	giz = giz_;
	cname = name_;
	ctype = "";
	internal = false;
	IO_dn2("CmpBox CTOR %s",name_.c_str());
}

void
ccafe::CmpBox::setType(const std::string & stype, bool intern)
{
	ctype = stype;
	internal = intern;
}

ccafe::CmpBox::~CmpBox(){
	delete giz;
	if (internal) {
		delete comp;
	}
	giz = 0;
	comp = 0;
	cname +=  "dead_instance";
	ctype +=  "dead_instance";
}


