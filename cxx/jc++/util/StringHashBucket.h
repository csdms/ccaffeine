/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: StringHashBucket.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef StringHashBucket_seen
#define StringHashBucket_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"

/** string keyed hashtable bucket that differentiates
 string and object values.
*/
class StringHashBucket : public virtual Object {

private:
	char *okey;
	Object *ovalue;
	StringHashBucket *hnext;

public:
	CDELETE StringHashBucket(char *key, Object *value);

	char *key();

	Object *element();

	StringHashBucket *next();

	void setNext(StringHashBucket *next);
	void setValue(Object *val);

};

} ENDSEMI //jcpp
#endif // StringHashBucket_seen
