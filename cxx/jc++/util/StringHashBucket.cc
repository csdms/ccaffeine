/**
 *  Version: $Revision: 1.4 $
 *  Version control file: $RCSfile: StringHashBucket.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:08 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringHashBucket.h"
#ifndef lint
static char id[]="$Id: StringHashBucket.cc,v 1.4 2002/12/19 20:21:08 baallan Exp $"; // RCS string
#endif



#include "util/freefree.h"

jcpp::StringHashBucket::StringHashBucket(char * key_, Object * value) {
	okey = key_;
	ovalue = value;
	hnext = NULL;
}


char * jcpp::StringHashBucket::key() { return okey; }

jcpp::Object * jcpp::StringHashBucket::element() { return ovalue; }

jcpp::StringHashBucket *jcpp::StringHashBucket::next() { return hnext; }

void jcpp::StringHashBucket::setNext(StringHashBucket *next_) { hnext = next_; }

void jcpp::StringHashBucket::setValue(jcpp::Object * val) { 
  ovalue = val; 
}
