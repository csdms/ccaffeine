/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: HashBucket.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef HashBucket_seen
#define HashBucket_seen
//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"

namespace jcpp {


/** internal class for an object keyed hash of objects. */
class HashBucket : public virtual Object {

private:
	Object *okey;
	Object *ovalue;
	HashBucket *hnext;

public:
	CDELETE HashBucket(Object *key, Object *value);

	/** Get the bucket's key. */
	Object *key();

	/** Get the bucket's element. */
	Object *element();

	/** Get the next bucket. */
	HashBucket *next();

	/** Set the next bucket. */
	void setNext(HashBucket *next);
	/** Set the bucket's value. */
	void setValue(Object *val);

};

}  ENDSEMI //jcpp
#endif // HashBucket_seen
