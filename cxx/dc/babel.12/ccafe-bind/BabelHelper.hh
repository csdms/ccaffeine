#ifndef CCAFE_BABEL_HELPER_SEEN
#define CCAFE_BABEL_HELPER_SEEN

class BabelHelper {

public:

static ::gov::cca::CCAExceptionType babelExceptionType( ::ccafeopq::ExceptionType ot);

static ::ccafeopq::ExceptionType opaqueExceptionType( ::gov::cca::CCAExceptionType bt);

static ::gov::cca::Type babelType( ::ccafeopq::Type ot);

static ::ccafeopq::Type opaqueType( ::gov::cca::Type bt);

// The next set of functions makes the conversions to sidl from stl vectors.
// This can be done with a template declaration, but is less obvious that way.
// We keep the templatization inside the implementation of these functions.

static sidl::array< ::std::string >stringVectorToSidlArray( ::std::vector< ::std::string > & val);

static sidl::array< bool >boolVectorToSidlArray( ::std::vector< bool > & val);

static sidl::array< float >floatVectorToSidlArray( ::std::vector< float > & val);

static sidl::array< double >doubleVectorToSidlArray( ::std::vector< double > & val);

static sidl::array< int32_t >intVectorToSidlArray( ::std::vector< int32_t > & val);

static sidl::array< int64_t >longVectorToSidlArray( ::std::vector< int64_t > & val);

static sidl::array< std::complex< float> >fcomplexVectorToSidlArray( ::std::vector< std::complex< float > > & val);

static sidl::array< std::complex< double> >dcomplexVectorToSidlArray( ::std::vector< std::complex< double > > & val);

};

#endif // CCAFE_BABEL_HELPER_SEEN
