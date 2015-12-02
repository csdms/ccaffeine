#ifndef lint
static char id[]="$Id: StringTokenizer.cc,v 1.6 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif

#include <stdlib.h>
#include <string.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/JString.h"
#include "jc++/util/StringTokenizer.h"
#include "util/IO.h"


#include "util/freefree.h"

// string returned from this function must be freed asap.
char *jcpp::StringTokenizer::nextTokenInternal() {
	if (position >= input_length) {
		return (null);
	}

	// If we're on a delimiter, we must either return it or skip it.
	if (JString::indexOf(delims,input[position]) != -1) {
		position++;
		// If we're returning them, do it now
		if (retDelim) {
			char del[2];
			del[0] = input[position-1];
			del[1]='\0';
			return STRDUP(del);
		}
		// Otherwise step though stream until we've reached a
		// non-delimiter
		for (;;) {
			if (position >= input_length) {
				return (null);
			}
			if (JString::indexOf(delims,input[position]) == -1) {
				break;
			}
			position++;
		}
	}

	int start = position;
	for (;;) {
		position++;
		if (position >= input_length || JString::indexOf(delims,input[position]) != -1) {
			break;
		}
	}

	char *tok = STRDUP(input);
    strncpy(tok,&(input[start]),position-start+1);
    tok[position-start] = '\0';

	return tok;
}

jcpp::StringTokenizer::StringTokenizer(char * str) {
	input_length = strlen(str);
	input = STRDUP(str);
	delims = STRDUP(" \t\n\r");
	retDelim = FALSE;
	position = 0;
}

jcpp::StringTokenizer::StringTokenizer(char *str, char *delim) {
	input_length = strlen(str);
	input = STRDUP(str);
	delims = STRDUP(delim);
	retDelim = FALSE;
	position = 0;
}

jcpp::StringTokenizer::StringTokenizer(char *str, char *delim, boolean ret) {
	input_length = strlen(str);
	input = STRDUP(str);
	delims = STRDUP(delim);
	retDelim = ret;
	position = 0;
}

jcpp::StringTokenizer::~StringTokenizer() {
	free(input);
	free(delims);
	input = delims = NULL;
	retDelim=-1;
	position=-2;
	input_length = -3;
}

int jcpp::StringTokenizer::countTokens() {

	int count;
	int oldPosition = position;

	char *s;
	for (count = 0; (s=nextTokenInternal()) != null; count++) {
		free(s);
	}

	position = oldPosition;

	return (count);
}

boolean jcpp::StringTokenizer::hasMoreElements() {
	return (hasMoreTokens());
}


boolean jcpp::StringTokenizer::hasMoreTokens() {

	int oldPosition = position;
	char *ret = nextTokenInternal();
	position = oldPosition;
	if (ret == null) {
		return (false);
	}
	free(ret);
	return (true);
}

// tokens returned must be freed when you are done with them.
char *jcpp::StringTokenizer::nextElement() {
	return (nextToken());
}

// tokens returned must be freed when you are done with them.
char *jcpp::StringTokenizer::nextToken(char *delim) {
	delims = delim;
	return (nextToken());
}

// tokens returned must be freed when you are done with them.
char *jcpp::StringTokenizer::nextToken() {
	char *ret = nextTokenInternal();
	if (ret == null) {
		IO::en("no more elements in StringTokenizer::nextToken");
		abort();
	}
	return (ret);
}

