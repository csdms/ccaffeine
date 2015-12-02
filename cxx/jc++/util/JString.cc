#ifndef lint
static char id[]="$Id: JString.cc,v 1.6 2002/12/19 20:21:07 baallan Exp $"; // RCS string
#endif

#include <ctype.h>
#if defined(__sun) || defined(__sgi)
#include <strings.h>
#endif // __sun

#include "jc++/jc++.h"
#include "jc++/util/JString.h"

#include "util/freefree.h"

boolean JString::startsWith(char *haystack, char *needle) {
    return (strstr(haystack,needle) == haystack);
}

int JString::indexOf(char *haystack, char *needle) {
    char *top;
    top = strstr(haystack,needle);
    if (top != NULL) {
    	return top-haystack;
    }
    return -1;
}

int JString::indexOf(char *s, char c) {
    char *top;
    top = strchr(s,c);
    return (int)((top!=NULL)?(top-s):-1);
}

int JString::indexOf(char *s, char c, int r) {
    char *top;
    s = &(s[r]); // gotta love that pointer arithmetic
    top = strchr(s,c);
    return (int)((top!=NULL)?(top-s):-1);
}

int JString::lastIndexOf(char *s, char c) {
    char *cloc;
    cloc = rindex(s,c);
    if (cloc==NULL) {
        return -1;
    }
    return (cloc-s);
}


int JString::compareToIgnoreCase(const char *s1, const char *s2) {
    return strcasecmp(s1,s2);
}

int JString::compareTo(const char *s1, const char *s2) {
    return strcmp(s1,s2);
}

CFREE char *JString::toLowerCase(const char *s) {
    char *lc;
    lc = STRDUP(s);
    int len = strlen(lc);
    for (int i=0; i < len; i++) {
    	lc[i] = (char)tolower((int)(lc[i]));
    }
    return lc;
}

CFREE char *JString::strdup(const char *s) {
    char *lc;
    if (s==0) { return 0; }
    int len = strlen(s);
    lc = (char *)malloc(len+1);
    strcpy(lc,s);
    return lc;
}
