#include "vComponent.hh"
#include <string>
class sPort : public virtual vPort {
				public:
				virtual ~sPort() {}
				virtual std::string getCname() = 0;
};
