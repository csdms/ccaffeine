#ifndef vport_hh_seen
#define vport_hh_seen

class vPort {
				public:
				virtual ~vPort(){}
};

class vComponent {
				public:
				virtual ~vComponent() {}
				virtual vPort * getPort() = 0;
				virtual int checkPort( vPort * p) = 0;
};

#endif  // vport_hh_seen
