#ifndef lint
static char id[]=
"$Id: CmdContextCCA.cxx,v 1.30 2005/01/11 01:21:20 baallan Exp $";
#endif
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "dc/framework/dc_fwkPublic.h"

#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/ccacmd/CmdContextCCA.h"
#include "stovepipe/stp.h"

#ifdef HAVE_LIBREADLINE
#ifdef HAVE_READLINE_READLINE_H
#include <readline/readline.h>
#else
#ifdef HAVE_READLINE_H
#include <readline.h>
#else
extern "C" char *readline(const char *);
#endif
#endif
#ifdef HAVE_READLINE_HISTORY
#ifdef HAVE_READLINE_HISTORY_H
#include <readline/history.h>
#else
#ifdef HAVE_HISTORY_H
#include <history.h>
#else
extern "C" void add_history(const char *);
#endif
#endif
#endif
#endif


#include <assert.h>
#include <errno.h>
#include <string.h>

#include "util/IO.h"
#include "util/freefree.h"



// instantiation of interpreters has specific details.
CmdContextCCA::CmdContextCCA(CmdLineBuilderView *bv_, DefaultBuilderModel* bm_) {
  this->tmpString = 0;
  in = IO::in();
  bv = bv_;
  bm = bm_;
  setup();
}

// Similar to above, uses a given input FILE argument, the FILE is
// expected to be line-buffered.
CmdContextCCA::CmdContextCCA(FILE* in, CmdLineBuilderView *bv_, DefaultBuilderModel* bm_) {
  this->tmpString = 0;
  this->in = in;
  bv = bv_;
  bm = bm_;
  setup();
}

void CmdContextCCA::setup() {
  rcFileName = 0;
  rcUnknown = 1;
  lineCount = 0;
  lastErr = 0;
  rc = 0;
}

CmdContextCCA::~CmdContextCCA() {
  delete bm; /// really that delete should probably be elsewhere...
  free(rcFileName);
}

void CmdContextCCA::pn(char *s) {
  bv->pn(s);
}

void CmdContextCCA::p(char *s) {
  bv->p(s);
}

void CmdContextCCA::pn(char c) {
  bv->pn(c);
}

void CmdContextCCA::p(char c) {
  bv->p(c);
}

char *CmdContextCCA::prompt() {
  static char ps[] = "\ncca>";
#ifdef HAVE_LIBREADLINE
  static char readline_ps[] = "\n";
  return (isatty(fileno(in))) ? readline_ps : ps;
#else
  return ps;
#endif
}

void CmdContextCCA::trim_blanks(char *str)
{
  if (str) {
    register int i = strlen(str) - 1;
    while (i >= 0 && isspace(str[i])) --i;
    str[i+1] = '\0';
  }
}

CFREE char *CmdContextCCA::_readLine(int &readerr) {
  readerr=0;
  char *buf;
  buf = (char *)malloc(2049);
  assert(buf!=0);
  buf[2048] = '\0'; // guarantee that buf is NUL terminated

  buf[0]='\0';
  buf[1]='\0';
  // try opening the rc file once only.
  if (rcUnknown) {
    int rcExists = initRC();
    rcUnknown = 0;
    if (!rcExists) {
      IO::en("\nCmdContextCCA::initRC: No rc file found. Pallet may be empty.");
    } else {
      IO::en("\nCmdContextCCA::initRC: Found %s.", rcFileName);
    }
  } 
  // get a line from rc, please.
  int rcOk = 0;
  if (rc != 0) {
    rcOk = rcLine(buf,2048);
  } 
  // ran out of rc. back to reading the normal input.
  if (!rcOk) {
#ifdef HAVE_LIBREADLINE
    if (isatty(fileno(in))) {
      free(buf);
      buf = readline("cca>");
#ifdef HAVE_READLINE_HISTORY
      trim_blanks(buf);
      if (buf && buf[0]) { // don't add blank lines
	add_history(buf);
	return buf;		// avoid retrimming
      }
#endif
    }
    else {
#endif
      if (!fgets(buf,2048,in)) { // NULL return value means EOF or error
        free(buf);
	buf = 0;
      }
#ifdef HAVE_LIBREADLINE
    }
#endif
  }
  trim_blanks(buf);
  return buf;
}

/** Return a pointer to the first non-space character of src. */
static char *firstNonBlank(char *src)
{
  while (isspace(*src)) ++src;
  return src;
}

/**
 * Concatenate prev and next and return their combined length in
 * the combinedLength argument. The last character of prev is
 * assumed to be a continuation character, and it is overwritten
 * by the first non-space character of next. Leading space characters
 * in next are not part of the combined string. The are skipped.
 * 
 * On entry, prev and next may be NULL or non-NULL. combinedLength is
 * the length of prev or 0 is prev is NULL.
 */
static char *concatLines(char *prev, char *next, int &combinedLength){
  if (prev) {
    if (next) {
      char *trimmedNext = firstNonBlank(next);
      const int nextLength = strlen(trimmedNext);
      const int prevLength = combinedLength;
      char *result = (char *)malloc(nextLength + prevLength);
      /* this isn't an off by one mistake because the last character
	 of prevLength is chopped off */
      assert(result);
      (void)strcpy(result, prev);
      (void)strcpy(result + prevLength - 1, trimmedNext);
      combinedLength = prevLength - 1 + nextLength;
      free(next);
      free(prev);
      next = result;
    }
    else {
      // the API specifies that combinedLength == strlen(prev);
      prev[--combinedLength] = '\0'; // remove continuation character
      next = prev;
    }
  }
  else {
    combinedLength = (next ?  strlen(next) : 0);
  }
  return next;
}

char *CmdContextCCA::readLine(int &readerr) {
  int len = 0;
  char *previousLine, *currentLine=0;
  readerr = 0;
  do {
    previousLine = currentLine;
    currentLine = concatLines(previousLine,_readLine(readerr),len);
    if (readerr) return 0;
  } while (currentLine && len > 0 && (currentLine[len-1] == '\\'));
  return currentLine;
}

char *CmdContextCCA::getInstance(char *instanceName) {

  char *s; // tmp string pointer obtained from arena before it is returned.
  std::string s1 = instanceName;
  std::vector< std::string >stdNames = bm->getInstanceNames();
  // exact match
  ::std::vector< ::std::string >::iterator pos = find(stdNames.begin(), stdNames.end(), s1);
  if ( pos != stdNames.end() ) {
     s = (char*)(s1.c_str());
     return strdup(s); // FIXME leak in callers. convert CmdContext to std::string.
  }


  // caseless match.
  size_t i;
  for (i=0; i < stdNames.size(); i++) {
    s1 = stdNames[i];
    s = (char *)s1.c_str();
    if (JString::compareToIgnoreCase(instanceName,s) == 0) {
      return strdup(s);
    }
  }

  // leading partial match (caseless)
  CFREE char *iname = JString::toLowerCase(instanceName);

  for (i=0; i < stdNames.size(); i++) {
    s1 = stdNames[i];
    s = JString::toLowerCase(s1.c_str()); // free the result.
    if (JString::startsWith(s,iname) == true) {
      free(s);
      s = strdup(s1.c_str());
      return s;
    }
    free(s); 
  }

  // poor partial match (caseless)
  for (i=0; i < stdNames.size(); i++) {
    int si;
    s1 = stdNames[i];
    s = JString::toLowerCase(s1.c_str()); // free the result.
    si = JString::indexOf(s,iname);
    if (si != -1) {
      free(s);
      s = strdup(s1.c_str());
      free(iname);
      return s;
    }
    free(s);
  }

  free(iname);
  return 0;
}

char *CmdContextCCA::getClass(char *className) {

  std::vector< std::string > pallet = bm->getPallet();

  // exact match
	int i;
  for (i=0; i < (int)pallet.size(); i++) {
    if (JString::compareTo(className,pallet[i].c_str()) == 0) {
      if(tmpString) { free(tmpString); }
      tmpString = strdup(pallet[i].c_str());
      return tmpString;
    }
  }

  // caseless match.
  for (i=0; i < (int)pallet.size(); i++) {
    const char *s = pallet[i].c_str();
    if (JString::compareToIgnoreCase(className,s) == 0) {
      if(tmpString) { free(tmpString); }
      tmpString = strdup(s);
      return tmpString;
    }
  }

  // leading partial match (caseless)
  CFREE char *cname = JString::toLowerCase(className);

  for (i=0; i < (int)pallet.size(); i++) {
    CFREE char *s = JString::toLowerCase(pallet[i].c_str());
    if (JString::startsWith(s,cname) == true) {
      free(s);
      free(cname);
      if(tmpString) { free(tmpString); }
      tmpString = strdup(pallet[i].c_str());
      return tmpString;
    }
    free(s);
  }

  // poor partial match (caseless)
  for (i=0; i < (int)pallet.size(); i++) {
    CFREE char *s = JString::toLowerCase(pallet[i].c_str());
    int si = JString::indexOf(s,cname);
    if (si != -1) {
      free(s);
      free(cname);
      if(tmpString) { free(tmpString); }
      tmpString = strdup(pallet[i].c_str());
      return tmpString;
    }
    free(s);
  }

  free(cname);
  return null;

}


 /** 
    In our version of readLine, we have overloaded to handle an rc file.
    We look for lines in files env(CCAFE_RC_FILE), env(HOME)/.ccaferc, and
    a compiled in path $(CCAFE_INSTALL_ROOT)/cxx/dc/user_iface/CcaffeineRC
    to return before we start parsing the regular input obtained from bv.
    The advisability of this on a global file system is not investigated here.
  */
int CmdContextCCA::initRC() {
  const char * optionValue; // --ccafe-rc
  char *homedir; // ~/.ccaferc
  char *envrc; // CCAFE_RC_FILE env var or CCAFE_RC_FILE=arg option w/mpi
  char *defaultFile = _RCPATH; // _RCPATH given from makefile
  int prevError = 0;
  homedir = getenv("HOME");
  if (homedir !=  0) { homedir = STRDUP(homedir); }
  // in parallel with global fs, make this different on every node.
  envrc = getenv("CCAFE_RC_FILE"); 
  errno = 0;
  int myerrno;

  // --ccafe-rc option
  optionValue = stp_get("ccafe-rc");
  if (optionValue != 0  && rcFileName == 0) {
    // Rob's kludge for overcoming MPI chg-to-exec-dir: basically MPI
    // does a basename(argv[0]) to find the relative path to the
    // executable.  It then chdir()'s to that directory (!).  This
    // messes up the path for the user who may have provided command
    // line switches based on the CWD of the originating shell.  This
    // will assume that MPI has done so if the ccafe-pwd switch has
    // been used or implanted directly by the main program.
    const char* cwd = stp_getn("ccafe", "pwd");
    char* rcFilePath = NULL;
    if(
       ((cwd != NULL) && (strcmp(cwd, "") != 0)) && // the option is valid.
       (strncmp("/", optionValue, 1) != 0) // does not begin with a `/'
       ) {
      int siz = 4 + strlen(cwd) + strlen(optionValue);
      rcFilePath = (char*)malloc(siz);
      memset(rcFilePath, 0, siz); // zero length string now
      rcFilePath = strcat(rcFilePath, cwd);
      rcFilePath = strcat(rcFilePath, "/");
      rcFilePath = strcat(rcFilePath, optionValue);
    } else {
      rcFilePath = STRDUP(optionValue);
    }
    // End Rob's kludge for overcoming MPI
    rc = fopen(rcFilePath,"r");
    myerrno = errno;
    if (rc == 0 || badMagic(rc,rcFilePath)) {
      if (myerrno != ENOENT && myerrno != 0) {
        IO::en("CmdContextCCA::initRC: Error reading %s: %s(%d)",
               rcFilePath,strerror(myerrno),myerrno);
      }
      if (myerrno == ENOENT ) {
        IO::en("CmdContextCCA::initRC: FileNotFound %s from --ccafe-rc.",
               rcFilePath);
      }
      free(rcFilePath);
      rcFilePath = 0;
      rc = 0;
      prevError=1;
    } else {
      rcFileName = rcFilePath;
    }
  }

  // env or CCAFE_RC_FILE= option
  if (envrc != 0 && rcFileName == 0) {
    rc = fopen(envrc,"r");
    myerrno = errno;
    if (rc == 0 || badMagic(rc,envrc)) {
      if (myerrno != ENOENT && myerrno != 0) {
        IO::en("CmdContextCCA::initRC: Error reading %s: %s(%d)",
               envrc,strerror(myerrno),myerrno);
      }
      if (myerrno == ENOENT ) {
        IO::en("CmdContextCCA::initRC: FileNotFound %s from CCAFE_RC_FILE.",
               envrc);
      }
      rc = 0;
      prevError=1;
    } else {
      if (prevError) {
        IO::en("CmdContextCCA::initRC: Instead found bootstrap script %s from CCAFE_RC_FILE.",
               envrc);
      }
      rcFileName = STRDUP(envrc);
    }
  }

  // users .ccaferc
  if (homedir != 0  && rcFileName == 0) {
    char *homerc;
    int homercLen = strlen(homedir) + strlen(CCAFE_RC_NAME) 
                    + strlen(PATHSEP_STRING) +1;
    homerc = (char *)malloc(homercLen);
    sprintf(homerc,"%s%s%s",homedir,PATHSEP_STRING,CCAFE_RC_NAME);
    free(homedir);
    rc = fopen(homerc,"r");
    myerrno = errno;
    if (rc == 0 || badMagic(rc,homerc)) {
      if (myerrno != ENOENT && myerrno != 0) {
        IO::en("CmdContextCCA::initRC: Error reading %s: %s(%d)",
               homerc,strerror(myerrno),myerrno);
        free(homerc);
      }
      homerc = 0;
      rc = 0;
    } else {
      if (prevError) {
        IO::en("CmdContextCCA::initRC: Instead found bootstrap script %s.",
               homerc);
      }
      rcFileName = homerc;
    }
  }

  // backstop in the installed tree.
  if (rcFileName == 0) {
    rc = fopen(defaultFile,"r");
    myerrno = errno;
    if (rc == 0 || badMagic(rc,defaultFile)) {
      if (myerrno != ENOENT && myerrno != 0) {
        IO::en("CmdContextCCA::initRC: Error reading %s: %s(%d)",
               defaultFile,strerror(myerrno),myerrno);
      }
      rc = 0;
    } else {
      if (prevError) {
        IO::en("CmdContextCCA::initRC: Instead found systemwide bootstrap script %s.",
               defaultFile);
      }
      rcFileName = STRDUP(defaultFile);
    }
  }


  if (rcFileName == 0) {
    return 0;
  }
  return 1;
  
}

int CmdContextCCA::badMagic(FILE *f,const char *fname) {
	/** side effect: if badmagic, close file. */
  char *line1;
  line1 = (char*)malloc(40);
  sprintf(line1,"badMagic: no ccaffeine");
  int result = 1;
  if ( fgets(line1,39,f) != 0 ) {
    result = strncmp(line1,"#!ccaffeine",11);
  }
  free(line1);
  if (result) {
    IO::en("CmdContextCCA::initRC: Bad magic in rc file %s. %s",fname,
           "CCAFFEINE rc file must start with '#!ccaffeine' on a line by itself. Closing file."
           );
    fclose(f);
  }
  return result;
}

bool CmdContextCCA::isFakeEOF(char *buf) {
	if (buf != 0) {
		if (strncmp(buf,"#!eof",5) == 0) {
			errno = EOF;
			return true;
		}
	}
	return false;
}
  /** returns a line from the rcfile. status out is 0 if ok, 1 if no more lines. */
int CmdContextCCA::rcLine(char *buf, int bufSize) {
  if (!rc) { return 0; }
  char *s;
  lineCount++;
  lastErr = 0;
  errno = 0;
  s = fgets(buf,bufSize,rc);
  if (s == 0 || isFakeEOF(s) ) {
    lastErr = errno;
    if (lastErr != 0 && lastErr != EOF) {
      IO::en("CmdContextCCA::rcLine: Error reading %s:%d> %s(%d)",
              rcFileName,lineCount,strerror(lastErr),lastErr);
    }
    fclose(rc);
    rc = 0;
    return 0;
  }
  return 1;
}

/** Returns the rcfile name and lines read statistics. If
    none returns will be null/0 */
char *CmdContextCCA::getRCInfo(int & linesRead, int & lineErr) {
  linesRead = lineCount;
  lineErr = lastErr;
  return rcFileName;
}

