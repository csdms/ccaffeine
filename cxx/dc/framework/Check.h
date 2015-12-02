#ifndef CCAFE_KERNEL_CHECK // ccafe_kernelcheck
#define CCAFE_KERNEL_CHECK // ccafe_kernelcheck
#include <string>
#include <stdio.h>

class Thrown : public virtual ::std::exception
{	
private:
	::std::string m;
public:
	Thrown() { m = ""; }
	Thrown(const char *s) { m = s; }
	Thrown(const std::string & s) { m = s; }
	virtual ~Thrown() throw() {}
	virtual const char *what() const throw() { return m.c_str(); }
};

class Check {
	public:
		static void DC(void *p, char *f, int l) {
			if (p == 0) {
				::std::string m = f;
				char s[40];
				::sprintf(s, "%d", l);
				m += s;
				::fprintf(stderr,"dynamic_cast failed at %s:%d.\n",f,l);
				Thrown t(m);
				throw t;
			}
		}
};
			
#ifndef CHECKDC
#define CHECKDC(p) Check::DC(p,__FILE__,__LINE__)
#endif

#endif // ccafe_kernelcheck
