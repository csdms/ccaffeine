#ifndef __PORTCONVERTER_HH__
#define __PORTCONVERTER_HH__

#include <AllCCA.hh>

//Interface to translate ccafeopq::Port's to gov::cca::Port's
class PortConverter {
private:

public:

  virtual ~PortConverter(){}

  virtual gov::cca::Port convert(::ccafeopq::Port *) = 0;

};

typedef boost::shared_ptr< PortConverter > PortConverter_ptr;

#endif // __PORTCONVERTER_HH__
