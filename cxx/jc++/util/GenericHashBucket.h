/**
 *  Version: $Revision: 1.3 $
 *  Version control file: $RCSfile: GenericHashBucket.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef GenericHashBucket_seen
#define GenericHashBucket_seen
//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/HashKey.h"

namespace jcpp {


/** internal class for an object keyed hash of objects. */
class GenericHashBucket : public virtual Object {

private:
	HashKey *okey;
	Object *ovalue;
	GenericHashBucket *hnext;

public:
	CDELETE GenericHashBucket(HashKey *key, Object *value);

	/** Get the bucket's key. */
	HashKey *key();

	/** Get the bucket's element. */
	Object *element();

	/** Get the next bucket. */
	GenericHashBucket *next();

	/** Set the next bucket. */
	void setNext(GenericHashBucket *next);
	/** Set the bucket's value. */
	void setValue(Object *val);

};

} ENDSEMI //jcpp
#endif // GenericHashBucket_seen
