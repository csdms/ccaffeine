#include "vComponent.hh"
#include <string>
class sPort : public virtual vPort {
				public:
				~sPort() { std::cout <<"sPort destructor" << std::endl; }
				std::string getCname() {
					 std::cout <<"sPort::getCname called" << std::endl;
				}
};
