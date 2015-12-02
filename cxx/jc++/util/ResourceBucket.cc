/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: ResourceBucket.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:07 $
 *  Last modified by: $Author: baallan $
*/
#include <stdlib.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/JString.h"
#include "jc++/util/ResourceBucket.h"
#ifndef lint
static char id[]="$Id: ResourceBucket.cc,v 1.6 2002/12/19 20:21:07 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"


jcpp::ResourceBucket::~ResourceBucket() {
  ::free(svalue); svalue = 0;
  ::free(okey); okey = 0;
}

jcpp::ResourceBucket::ResourceBucket(char * key_, char * value) {
	okey = STRDUP(key_);
	svalue = STRDUP(value);
	hnext = NULL;
}

char * jcpp::ResourceBucket::key() { return okey; }

char * jcpp::ResourceBucket::element() { return svalue; }

jcpp::ResourceBucket *jcpp::ResourceBucket::next() { return hnext; }

void jcpp::ResourceBucket::setNext(ResourceBucket *next_) { hnext = next_; }

void jcpp::ResourceBucket::setValue(char * val) { 
  if (svalue != 0) { free(svalue); svalue = 0; }
  if (val) {
    svalue = STRDUP(val);
  }
}

