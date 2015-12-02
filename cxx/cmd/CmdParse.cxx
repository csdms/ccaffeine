#include <assert.h>
#include <stdlib.h> // for abort

#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdActionExit.h"
#include "cmd/CmdActionHelp.h"
#include "cmd/CmdParse.h"

#include "util/IO.h"

#include "util/freefree.h"

CDELETE CmdParse::CmdParse(CmdContext *icc) {

  alist = new JCPN(Vector)();	// commands in this parser.

  CmdActionHelp *cah = new CmdActionHelp(); // must be first.
  alist->add(cah);

  CmdActionExit *cae = new CmdActionExit(); 
  alist->add(cae);

  cc = icc;

}

CmdParse::~CmdParse() {
  delete alist;
  alist = NULL;
  cc = NULL;
}

CmdContext *CmdParse::getContext() {
  return cc;
}

/** Adds a command to the parser. Presently does not check the sanity of 
    the command. */
void CmdParse::addAction(CmdAction *c) {
// This function needs to do some insertion with checking for
// duplicates if we're paranoid. As it is, this comes out in
// the wash at getAction. Duplication will make commands useless.

  alist->add(c);

}


/** Returns the nearest match (by leading characters) of commands 
    stored in the list. */
CmdAction *CmdParse::getAction(char *s) {

  JCPN(Vector) matches;
  CmdAction *c;
  int i,j,len;

  int s_length;
  s_length = strlen(s);
  if ((s_length >= 1 && (s[0] == '#' || s[0] == '!' )) ||
      (s_length >= 2 && s[0] == '/' && s[1] =='/')) {
    return null;
  }

  j = alist->size();
  for (i=0; i < j; i++) {
    c = dynamic_cast<CmdAction *>(alist->get(i)); CHECKDC(c);
    char **na = c->names(len);
    assert(na != NULL);
    int k=0;
    for  (k = 0; k < len; k++) {
      if (JString::startsWith(na[k],s)) {
        matches.add(c);
      }
    }
  }

  // got it.
  if (matches.size() == 1) {
    c = dynamic_cast<CmdAction *>(matches.get(0)); CHECKDC(c);
    return c;
  }

  // bogosity.
  if (matches.size() == 0) {
    cc->p((char *)"! Command ");
    cc->p(s);
    cc->pn((char *)" is undefined. Type 'help' for assistance.");
    if (cc->verbose()) {
      // call the help function here.
      JCPN(Vector) dummy;
      dummy.add(alist);
      c = dynamic_cast<CmdAction *>(alist->get(0)); CHECKDC(c); // Help command is always 0.
      try {
        c->doIt(cc,&dummy);
      } catch(...) {
        exit(2); // Help hurling an exception is bad.
      }

    }
    return null;
  }

  // ambiguity
  j = matches.size();
  cc->p((char *)"Ambiguous command '");
  cc->p(s);
  cc->pn((char *)"', try one of: ");
  for (i=0; i < j; i++) {
    c = dynamic_cast<CmdAction *>(matches.get(i)); CHECKDC(c);
    char **na = c->names(len);
    assert(na != NULL);
    cc->p((char *)"   ");
    int k=0;
    for (k=0; k < len; k++) {
      cc->p(na[k]);
      cc->p((char *)" ");
    }
  }
  return null;
}


// The following holds for all addXxxArg functions:
// returns 0 if ok, -1 if error in next token, 1 if no next token.

/** Converts the next token to a class (per app. definition) and adds to 
    arg list. */
int CmdParse::addClassArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {

  if (!st->hasMoreTokens()) {
    return 1;
  }

  CFREE char * tok = st->nextToken();

  char * className = cc->getClass(tok);
  // Whether or not this is valid is not the parser's decision.
  if (className == null) {
//     cc->p((char *)"Unknown class {");
//     cc->p(tok);
//     cc->pn((char *)"}");
// Likely leaking memory.
    className = STRDUP(tok);
    free(tok);
  } else {
    free(tok);
  }

  args->addString(STRDUP(className));
  cb->append((char *)" ");
  cb->append(className);
  return 0;
}



/** Converts the next token to an instance (per app. definition) and adds 
    to arg list. */
int CmdParse::addInstanceArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {

  if (!st->hasMoreTokens()) {
    return 1;
  }

  CFREE char * tok = st->nextToken();
  char * instanceName = cc->getInstance(tok);

  // Same as Unknown component.  This is not the parser's business.
  if (instanceName == null) {
//     cc->p((char *)"Unknown instance {");
//     cc->p(tok);
//     cc->pn((char *)"}");
// Very likely leaking memory here, but I have no idea how to fix it.
    instanceName = STRDUP(tok);
    free(tok);
  } else {
    free(tok);
  }

  args->addString(STRDUP(instanceName));
  cb->append((char *)" ");
  cb->append(instanceName);
  return 0;
}


/** Converts the remaining tokens to a string and adds to arg list. */
int CmdParse::addLine(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {

  if (!st->hasMoreTokens()) {
    return 1;
  }

  char *tok;
  CFREE tok = st->nextToken();
  JCPN(StringBuffer) *sb = new JCPN(StringBuffer)(tok);
  free(tok);
  while (st->hasMoreTokens()) {
    sb->append((char *)" ");
    tok = st->nextToken();
    sb->append(tok);
    free(tok);
  }
  args->addString(sb->toString());
  cb->append((char *)" ");
  char *stmp;
  stmp = sb->toString();
  cb->append(stmp);
  free(stmp);
  delete sb;

  return 0;

}


/** Adds the next token as a string to the arg list */
int CmdParse::addStringArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {

  if (!st->hasMoreTokens()) {
    return 1;
  }

  CFREE char * tok = st->nextToken();
  args->addString(tok); // will be destroying tok in clearArgs
  cb->append((char *)" ");
  cb->append(tok);

  return 0;

}


/** Converts the next token to a Double and adds to arg list. */
int CmdParse::addDoubleArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {
  if (!st->hasMoreTokens()) {
    return 1;
  }
  CFREE char *tok = st->nextToken();
  int err;
  JCPN(DoubleJC) *dval = new JCPN(DoubleJC)(tok, err);
  free(tok); tok = 0;
  if (dval && !err) {
    args->add(dval);
    cb->append((char *)" ");
    cb->append(dval->doubleValue());
  } else {
    delete dval;
    return -1;
  }
  return 0;
}

/** Converts the next token to a Integer and adds to arg list. */
int CmdParse::addIntegerArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {
  if (!st->hasMoreTokens()) {
    return 1;
  }
  CFREE char *tok = st->nextToken();
  int err;
  JCPN(IntegerJC) *ival = new JCPN(IntegerJC)(tok,err);
  free(tok); tok = 0;
  if (ival && !err) {
    args->add(ival);
    cb->append((char *)" ");
    cb->append(ival->intValue());
  } else {
    delete ival;
    return -1;
  }
  return 0;
}

/** Converts the next token to a Integer and adds to arg list. */
int CmdParse::addLongArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {
  if (!st->hasMoreTokens()) {
    return 1;
  }
  CFREE char *tok = st->nextToken();
  int err;
  JCPN(LongJC) *lval = new JCPN(LongJC)(tok,err);
  free(tok); tok = 0;
  if (lval && !err) {
    args->add(lval);
    cb->append((char *)" ");
    cb->append((long)lval->longValue());
  } else {
    delete lval;
    return -1;
  }
  return 0;
}

/** Converts the next token to a Boolean (more usefully than the 
    broken java version and adds to arg list. */
int CmdParse::addBooleanArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) {
  if (!st->hasMoreTokens()) {
    return 1;
  }
  boolean value;
  boolean assigned;
  value = false;
  assigned = false;
  CFREE char *val = st->nextToken();
  if (JString::compareToIgnoreCase(val,(char *)"n")==0 ||
      JString::compareToIgnoreCase(val,(char *)"no")==0 ||
      JString::compareToIgnoreCase(val,(char *)"nyet")==0 ||
      JString::compareToIgnoreCase(val,(char *)"nada")==0 ||
      JString::compareToIgnoreCase(val,(char *)"zip")==0 ||
      JString::compareToIgnoreCase(val,(char *)"f")==0 ||
      JString::compareToIgnoreCase(val,(char *)"FALSE")==0 ||
      JString::compareToIgnoreCase(val,(char *)"0")==0 ||
      JString::compareToIgnoreCase(val,(char *)"wrong")==0 ||
      JString::compareToIgnoreCase(val,(char *)"buzz")==0) {

      value = false;
      assigned = true;

  }
  if (JString::compareToIgnoreCase(val,(char *)"y")==0 ||
      JString::compareToIgnoreCase(val,(char *)"yes")==0 ||
      JString::compareToIgnoreCase(val,(char *)"da")==0 ||
      JString::compareToIgnoreCase(val,(char *)"si")==0 ||
      JString::compareToIgnoreCase(val,(char *)"yep")==0 ||
      JString::compareToIgnoreCase(val,(char *)"t")==0 ||
      JString::compareToIgnoreCase(val,(char *)"TRUE")==0 ||
      JString::compareToIgnoreCase(val,(char *)"1")==0 ||
      JString::compareToIgnoreCase(val,(char *)"right")==0 ||
      JString::compareToIgnoreCase(val,(char *)"correct")==0 ||
      JString::compareToIgnoreCase(val,(char *)"bingo")==0 ||
      JString::compareToIgnoreCase(val,(char *)"ok")==0 ||
      JString::compareToIgnoreCase(val,(char *)"ding!")==0) {

    value = true;
    assigned = true;
  }

  free(val); val = 0;
  if (assigned) {
    JCPN(BooleanJC) *bval = new JCPN(BooleanJC)(value);
    args->add(bval);
    cb->append((char *)" ");
    cb->append(bval);
  } else {
    return -1;
  }
  return 0;
}


int CmdParse::parse() {

  int readError;
  while (true) {
    
    cc->p(cc->prompt());
    
    CFREE char * read = cc->readLine(readError);
    
    if (read == null) {
      return readError;
    }
    
    CDELETE JCPN(StringTokenizer) *st = new JCPN(StringTokenizer)(read);
    free(read);
    read = null;
    
    if (!st->hasMoreTokens()) {
      delete st;
      continue;
    }
    
    CFREE char *tok = st->nextToken();
    
    CmdAction *c = getAction(tok);
    
    if (c == null) {
      free(tok); tok = 0;
      continue;
    }
    
    CDELETE JCPN(StringBuffer) *sb = new JCPN(StringBuffer)(tok);

    char *argtype = c->argtype();

    char ch, lastch;
    lastch = 'A'; // so that * will kick out an error if it appears first.
    int err = 0;
    int alen;
    int acount;

    acount = st->countTokens();
    alen = strlen(argtype);

    if ((alen <= 0 && acount != 0 ) ||
        (alen > 0 && 
         (lastch = argtype[alen-1]) != 'A' &&
         (lastch = argtype[alen-1]) != 'a' &&
         lastch != '*' && alen < acount) 
       ) {
      cc->p((char *)"Too many arguments to ");
      cc->pn(tok);
      delete st; st = 0;
      delete sb; sb = 0;
      free(tok); tok = 0;
      continue;
    }

    lastch = 'A'; // so that * will kick out an error if it appears first.
    CDELETE JCPN(Vector) *args = new JCPN(Vector)();

    for (int i = 0; i < alen; i++) {
    
      ch = argtype[i];
     
      switch (ch) 
      {
        case '*':
          switch (lastch)
          {
            case 'C':
            case 'c':
            case 'I':
            case 'i':
            case 'S':
            case 's':
            case 'D':
            case 'd':
            case 'K':
            case 'k':
            case 'B':
            case 'b':
            case 'G':
            case 'g':
              // FALLTHRU
              i -= 2;
              break;
            default:
              cc->p((char *)"Error in CmdAction ");
              cc->p(tok);
              cc->p((char *)": argtype misdefined (");
              cc->p( argtype);
              cc->pn((char *)").");
              break;
          }
          break;
        case 'C':
          err = addClassArg(st,args,sb);
          break;
        case 'c':
          err = addClassArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'I':
          err = addInstanceArg(st,args,sb);
          break;
        case 'i':
          err = addInstanceArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'S':
          err = addStringArg(st,args,sb);
          break;
        case 's':
          err = addStringArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'K':
          err = addLongArg(st,args,sb);
          break;
        case 'k':
          err = addLongArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'D':
          err = addIntegerArg(st,args,sb);
          break;
        case 'd':
          err = addIntegerArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'B':
          err = addBooleanArg(st,args,sb);
          break;
        case 'b':
          err = addBooleanArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;
        case 'G':
          err = addDoubleArg(st,args,sb);
          break;
        case 'g':
          err = addDoubleArg(st,args,sb);
          if (err == 1) {
            err = 2;
          }
          break;

        case 'A':
          err = addLine(st,args,sb);
          break;
        case 'a':
          err = addLine(st,args,sb);
          err = 0;
          break;
        case 'L':
          args->add(alist);
          err = 0;
          break;
        case 'P':
          args->add(this);
          err = 0;
          break;
        default:
          cc->p((char *)"Unknown parser argtype (");
          cc->p(ch);
          cc->pn((char *)")");
      }
    
      if (err == -1) {
        // type specific errors will be printed in addXxxArg()
        break;
      }
      if (err == 1) {
        cc->pn((char *)"Missing argument(s)");
        break; // exit the for loop, bogus args.
      }
      if (err == 2) {
        err = 0;
        break; // exit the for loop, no more optional args.
      }
    
      lastch = ch;
    
    } // END for
    
    if (err != 0) {
      delete st;
      delete sb;
      clearArgs(args);
      delete args;
      free(tok);
      st = 0; sb = 0; args = 0; tok = 0;
      continue; // skip bogus input.
    }
    
    int derr;
    derr = c->doIt(cc,args);
    if (!derr) {;
      // delete st; FIXME
      // delete sb; FIXME
      clearArgs(args);
      // delete args; FIXME
      free(tok);
      st = 0; sb = 0; args = 0; tok = 0;
    } else {
      delete st;
      delete sb;
      clearArgs(args);
      delete args;
      free(tok);
      st = 0; sb = 0; args = 0; tok = 0;
      return derr;
    }
    
  } // END while
}

void CmdParse::setContextVerbose(bool noisy) {
  cc->setVerbose(noisy);
}

void CmdParse::clearArgs(JCPN(Vector) *args) {
  // Note this means we need to malloc each string added to args
  // if it is not from a CFREE/cdelete source in the addX functions.
  // We know that everything in args is either a basic_typeJC object, a string,
  // or the Vector of commands alist or the object this.
  int i,len;
  len = args->size();
  char *s;
  for (i = len-1; i >= 0; i--) { 
    s = args->getString(i);
    if (s != 0) {
      free(s); // every string added to args should be owned by args.
      continue;
    }
    args->setElementAt(0,i);
  }
}
