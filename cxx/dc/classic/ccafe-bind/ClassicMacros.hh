
#define CLASSIC_RETHROW_PREPEND(s)  \
catch ( std::exception ex) \
{  \
	std::cout << s << " " << ex.what() << std::endl; \
}
