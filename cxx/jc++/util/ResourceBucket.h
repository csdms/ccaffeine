/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: ResourceBucket.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef ResourceBucket_seen
#define ResourceBucket_seen

namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"

/** string keyed hashtable bucket that differentiates
 string and object values.
*/
class ResourceBucket : public virtual Object {

private:
	char *okey;
	char *svalue;
	ResourceBucket *hnext;

public:
    /** key/value will be copied, not kept */
	CDELETE ResourceBucket(char *key, char *value);
	~ResourceBucket();

	char *key();

	char *element();

	ResourceBucket *next();

	void setNext(ResourceBucket *next);
    /** val will be copied, not kept. */
	void setValue(char *val);

};

} ENDSEMI //jcpp
#endif // ResourceBucket_seen
