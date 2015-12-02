#ifndef vport_hh_seen
#define vport_hh_seen

class vPort {
				public:
				virtual ~vPort()
				{
					std::cout << "vPort::DTOR called" << std::endl;
				}
};

class vComponent {
				public:
				virtual ~vComponent() 
				{
					std::cout << "vComponent::DTOR called" << std::endl;
				}
				virtual vPort * getPort() 
				{
					std::cout << "vComponent::getPort called" << std::endl;
					exit(1);
					return 0;
				}
				virtual int checkPort( vPort * p)
				{
					std::cout << "vComponent::checkPort called" << std::endl;
					exit(1);
					return 0;
				}
};

#endif  // vport_hh_seen
