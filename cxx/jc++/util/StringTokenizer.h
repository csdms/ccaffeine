#ifndef StringTokenizer_h_seen
#define StringTokenizer_h_seen
/**
 *  Version: $Revision: 1.7 $
 *  Version control file: $RCSfile: StringTokenizer.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/ 
// Rather safer than strtok ala java.
//

//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/StringEnumeration.h"
//#include "jc++/util/JString.h"

namespace jcpp {


/** Tokenizer vaguely like java's strtok */
class StringTokenizer : public virtual StringEnumeration {

private:

	char *input;
	char *delims;
	boolean retDelim;
	int position;
	int input_length;

	/** String returned from this function must be freed asap. */
	CFREE char *nextTokenInternal() ;

public:
	CDELETE StringTokenizer(char * str) ;

	CDELETE StringTokenizer(char *str, char *delim) ;

	CDELETE StringTokenizer(char *str, char *delim, boolean ret) ;

	virtual ~StringTokenizer() ;

	int countTokens() ;

	virtual boolean hasMoreElements() ;

	boolean hasMoreTokens() ;

	/** Same as nextToken. */
	CFREE virtual char *nextElement() ;

	/** Tokens returned must be freed when you are done with them. */
	CFREE char *nextToken(char *delim) ;

	/** Tokens returned must be freed when you are done with them. */
	CFREE char *nextToken() ;

};

}  ENDSEMI//jcpp
#endif // StringTokenizer_h_seen
