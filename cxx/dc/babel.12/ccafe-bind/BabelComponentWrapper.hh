#ifndef __BABELCOMPONENTWRAPPER_H__
#define __BABELCOMPONENTWRAPPER_H__


class BabelComponentWrapper : public virtual ccafeopq::Component {
private:

  ::gov::cca::Component wrapped;
  ccaffeine::Services bblSvc;
#ifdef HAVE_CLASSIC
  ClassicServicesHelper csh;
#endif // HAVE_CLASSIC

  void createException(const char * msg);

public:

  BabelComponentWrapper(gov::cca::Component c);

  virtual ~BabelComponentWrapper(){}

  virtual void setServices(ccafeopq::Services * svc) throw (ccafeopq::Exception);
  ::gov::cca::Component getWrapped() { return wrapped; }

};

#endif // __BABELCOMPONENTWRAPPER_H__
