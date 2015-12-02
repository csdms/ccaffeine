#include <stdlib.h>
#include <stdio.h>
#include "jc++/lang/Object.h"

void jcpp::BadCastMessage::checkDynamicCast(void *p, char *f, int l) {
  if (p == 0) {
    ::fprintf(stderr,"dynamic_cast failed at %s:%d.\n",f,l);
    ::exit(2);
  }
}

void jcpp::BadCastMessage::checkDynamicCastMessage(void *p, char *f, int l, char *mess) {
  if (p == 0) {
    ::fprintf(stderr,"!dynamic_cast failed at %s:%d.\n!%s\n",f,l,mess);
    ::exit(2);
  }
}

