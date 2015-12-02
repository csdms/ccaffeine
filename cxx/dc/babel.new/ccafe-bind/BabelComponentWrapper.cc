#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/server/ccaffeine_Services.hxx"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicPortConverter.hh"
#include "dc/classic/ccafe-bind/ClassicServicesHelper.hh"
#endif // HAVE_CLASSIC
#include "dc/babel.new/ccafe-bind/BabelComponentWrapper.hh"
#include "util/IO.h"

BabelComponentWrapper::BabelComponentWrapper(gov::cca::Component c) {
#ifdef CCAFE_AUDIT
  IO_dn1("BabelComponentWrapper::"
	 "BabelComponentWrapper(gov::cca::Component c called\n");
#endif
  wrapped = c;
}

void BabelComponentWrapper::setServices(ccafeopq::Services * svc)   throw (ccafeopq::Exception){
  IO_dn1("BabelComponentWrapper::setServices called");
  if(svc == 0) {
    if(bblSvc._is_nil()) {
      std::string cmsg = __FILE__;
      cmsg += ":setServices(nil) called on wrapper w/nil bblSvc.";
      throw ::ccafeopq::Exception(cmsg);
    } else {
	    // do the ComponentRelease interface calls
      bblSvc.doReleaseCallbacks();
    }
  } else {
    bblSvc = ccaffeine::Services::_create();
    if(bblSvc._is_nil()) {
      fprintf(stderr, ":-( %s: For some reason could not create "
	      "ccaffeine::Services\n", __FILE__);
      std::string cmsg = __FILE__;
      cmsg += "For some reason could not create ccaffeine::Services.";
      throw ::ccafeopq::Exception(cmsg);
    }
#ifdef HAVE_CLASSIC
		// put in the classic helper.
    ClassicServicesHelper *cshp;
    cshp = &csh;
    ccafeopq::ServicesHelper *oshp;
    oshp = cshp;
    svc->addServicesHelper(oshp);
    cshp->addBindingDelegates(svc);
#endif // HAVE_CLASSIC
 
		// then turn the component loose
    bblSvc.initialize(svc);
    wrapped.setServices(bblSvc);
  }
  IO_dn1("BabelComponentWrapper::setServices done");
}

void createException(const char * cmsg) {
	throw ::ccafeopq::Exception(cmsg);
}
