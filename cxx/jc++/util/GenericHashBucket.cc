/**
 *  Version: $Revision: 1.3 $
 *  Version control file: $RCSfile: GenericHashBucket.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:07 $
 *  Last modified by: $Author: baallan $
*/

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/lang/HashKey.h"
#include "jc++/util/GenericHashBucket.h"

#include "util/freefree.h"

#ifndef lint
static char id[]="$Id: GenericHashBucket.cc,v 1.3 2002/12/19 20:21:07 baallan Exp $"; // RCS string
#endif


jcpp::GenericHashBucket::GenericHashBucket(jcpp::HashKey * key_, jcpp::Object * value) {
	okey = key_;
	ovalue = value;
	hnext = NULL;
}

jcpp::HashKey * jcpp::GenericHashBucket::key() { return okey; }

jcpp::Object * jcpp::GenericHashBucket::element() { return ovalue; }

jcpp::GenericHashBucket *jcpp::GenericHashBucket::next() { return hnext; }

void jcpp::GenericHashBucket::setNext(jcpp::GenericHashBucket *next_) { hnext = next_; }

void jcpp::GenericHashBucket::setValue(jcpp::Object * val) { ovalue = val; }

