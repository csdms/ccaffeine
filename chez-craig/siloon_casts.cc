#include "jc++/util/jc++util.h"
#include "ccaFrameworkServices.h"
#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "siloon_casts.h"

gov::cca::BuilderService* BuilderService_Cast(gov::cca::Port* port)
{
 return dynamic_cast<gov::cca::BuilderService*>(port);
}
