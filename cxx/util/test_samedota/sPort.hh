#include "vComponent.hh"
#include <string>
class sPort : public virtual vPort {
				public:
				virtual ~sPort() { std::cout <<"sPort destructor" << std::endl; }
				virtual std::string getCname() {
					std::cout <<"sPort::getCname called" << std::endl;
					exit(1);
				}
};
