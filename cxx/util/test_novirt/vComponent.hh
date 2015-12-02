#ifndef vport_hh_seen
#define vport_hh_seen

class vPort {
				public:
				~vPort()
				{
					std::cout << "vPort::DTOR called" << std::endl;
				}
};

class vComponent {
				public:
				~vComponent() 
				{
					std::cout << "vComponent::DTOR called" << std::endl;
				}
				vPort * getPort() 
				{
					std::cout << "vComponent::getPort called" << std::endl;
					return 0;
				}
				int checkPort( vPort * p)
				{
					std::cout << "vComponent::checkPort called" << std::endl;
					return 0;
				}
};

#endif  // vport_hh_seen
