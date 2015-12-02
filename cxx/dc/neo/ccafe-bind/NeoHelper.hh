#ifndef CCAFE_NEO_HELPER_SEEN
#define CCAFE_NEO_HELPER_SEEN

class NeoHelper {

public:

static ::neo::cca::ExceptionType neoExceptionType( ::ccafeopq::ExceptionType ot);

static ::ccafeopq::ExceptionType opaqueExceptionType( ::neo::cca::ExceptionType bt);

static ::neo::cca::Type neoType( ::ccafeopq::Type ot);

static ::ccafeopq::Type opaqueType( ::neo::cca::Type bt);


};

#endif // CCAFE_NEO_HELPER_SEEN
