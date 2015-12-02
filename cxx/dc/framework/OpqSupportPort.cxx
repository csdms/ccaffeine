#include "dc/export/AllExport.hh"
#include "util/IO.h"

int ccafeopq::support::Port::next_serial = 0;

ccafeopq::support::Port::Port()
{
	next_serial++;
	serial = next_serial;
	char buf[40];
	sprintf(buf,"OSP::Port(%d)",serial);
	supported.push_back(buf);
	IO_dn2("ccafeopq::support::Port::Port() CTOR {size %d}",  supported.size());
}

ccafeopq::support::Port::Port( const std::string kind)
{
	next_serial++;
	serial = next_serial;
	char buf[40];
	sprintf(buf,"OSP::Port(%d)",serial);
	supported.push_back(buf);
	IO_dn3("ccafeopq::support::Port::Port( %s ) CTOR {size %d}", kind.c_str(), supported.size());
	supported.push_back(kind);
}

ccafeopq::support::Port::~Port()
{
	IO_dn2("ccafeopq::support::Port::Port() DTOR {size %d}",  supported.size());
}

void ccafeopq::support::Port::addSupportedKind(const std::string & s)
{
	if (!supportsKind(s)) {
		supported.push_back(s);
		IO_dn2("ccafeopq::support::Port::addSupportedKind(%s)", s.c_str());
		return;
	} 
	IO_dn2("ccafeopq::support::Port::addSupportedKind redundant call %s", s.c_str());
}


const std::string ccafeopq::support::Port::getKind()
{
	if (supported.size() > 1 ) {
		return supported[1];
	}
	return "ERROR:NONE_DEFINED";
}

bool ccafeopq::support::Port::isSameKind( ::ccafeopq::Port *p)
{
	if (p != 0) {
		for (size_t i = 0; i < supported.size(); i++)
		{
			if ( p->supportsKind(supported[i]) )
			{
  				return true;
			}
		}
	}
	return false;
}

const std::vector< std::string > ccafeopq::support::Port::getSupportedKinds()
{ 
	return supported; 
}

bool ccafeopq::support::Port::supportsMultipleKinds()
{
	return supported.size() > 1; 
}

bool ccafeopq::support::Port::supportsKind( const std::string & k)
{
#if 0
	size_t n = supported.size();
	// the iterator find version of this doesn't work under 2.96
	// stupid missing compare maybe?
	std::string s;
	for (size_t i = 0; i < n; i++) {
		s = supported[i];
		cerr << "--SUPP checking " << k <<  " against " << s << endl;
		if (strcmp(s.c_str(), k.c_str()) == 0) {
			return true;
		}
	}
#else
	std::vector< std::string >::const_iterator p = 
		find(supported.begin(), supported.end(), k);
	if (p != supported.end()) {
		return true;
	}
#endif
	return false;

}

