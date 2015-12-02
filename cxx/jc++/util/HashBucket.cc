/**
 *  Version: $Revision: 1.4 $
 *  Version control file: $RCSfile: HashBucket.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:07 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/HashBucket.h"

#include "util/freefree.h"

#ifndef lint
static char id[]="$Id: HashBucket.cc,v 1.4 2002/12/19 20:21:07 baallan Exp $"; // RCS string
#endif


jcpp::HashBucket::HashBucket(Object * key_, Object * value) {
	okey = key_;
	ovalue = value;
	hnext = NULL;
}

jcpp::Object * jcpp::HashBucket::key() { return okey; }

jcpp::Object * jcpp::HashBucket::element() { return ovalue; }

jcpp::HashBucket *jcpp::HashBucket::next() { return hnext; }

void jcpp::HashBucket::setNext(HashBucket *next) { hnext = next; }

void jcpp::HashBucket::setValue(Object * val) { ovalue = val; }

