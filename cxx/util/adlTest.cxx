#define _FAKE_CCA_TESTING
/* file to test dynamic loading ala cca, in a trivial fashion */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/testcca.h>
#include "ascDynaLoad.h"

#ifndef CCA_DL_SUFFIX
#define CCA_DL_SUFFIX ".so"
#endif

using namespace classic::gov::cca;

int main(const int argc, const char **argv) {
  char **clist=0;
  char *adltestlib;
  char *creator=0;
  char *className=0;
  int numerrs;
  int loadLocal, loadGlobal, loadLazy, loadNow, loadVerbose;
  /* defaults. should be parsed from argv instead */
  loadLocal = 1; loadGlobal=0; loadLazy=0; loadNow=1; loadVerbose= 1;
  size_t len;
  char **(*getComponentList)();
  void *(*createComponent)();
  CCAComponent *component=0;

  adltestlib = (char *)malloc(40);
  sprintf(adltestlib,"libadltest%s",CCA_DL_SUFFIX);

  getComponentList = (char **(*)())CCA_IntrospectLibrary(adltestlib,"getComponentList", loadLocal, loadGlobal, loadLazy, loadNow, loadVerbose); 
  if (getComponentList == 0) {
    fprintf(stderr,"CCA_IntrospectLibrary returned 0.\n");
    exit(1);
  }
  
  clist = getComponentList();
  if (clist == 0) {
    fprintf(stderr,"getComponentList returned null list.\n");
    exit(1);
  }
    
  if (clist[0] == 0) {
    fprintf(stderr,"getComponentList returned 0 length list.\n");
    exit(1);
  }
    
  numerrs = 0;
  while (clist[0] != 0) {

    len = strlen(clist[0])+1;
    creator = (char *)malloc(len);
    className = (char *)malloc(len);
    len = sscanf(clist[0],"%s %s", creator, className);
    if (len != 2) {
      fprintf(stderr,"Unable to parse component library index entry {%s}\n",clist[0]);
      numerrs++;
      free(creator);
      free(className);
      continue;
    }

    fprintf(stderr,"Attempting to load function %s for component type %s ...\n",creator,className);
    createComponent = (void *(*)())CCA_DynamicSymbol(adltestlib,creator);
    if (createComponent==NULL) {
      fprintf(stderr,"\nFailed to load function {%s}.\n",creator);
      numerrs++;
      free(creator);
      free(className);
      continue;
    }
    fprintf(stderr,"Succeeded.\n");
    

    fprintf(stderr,"Attempting to call function %s for component type %s ...\n",creator,className);
    component = (CCAComponent *)(createComponent());
    if (component==0) {
      fprintf(stderr,"\nFailed to load function {%s}.\n",creator);
      numerrs++;
      free(creator);
      free(className);
      continue;
    }
    fprintf(stderr,"Succeeded.\n");
    delete component; 
    fprintf(stderr,"Deleted instance of %s\n",className);
    free(creator);
    free(className);
    clist++;
  }
  /* now we back up to the last class and change the create function name request
     to make sure we don't get back a function when we shouldn't. 
  */
  clist--;
  len = strlen(clist[0])+1;
  creator = (char *)malloc(len);
  className = (char *)malloc(len);
  len = sscanf(clist[0],"%s %s", creator, className);
  if (len != 2) {
    fprintf(stderr,"Unable to parse component library index entry {%s}\n",clist[0]);
    numerrs++;
    free(creator);
    free(className);
  } else {
    creator[0]++; /* bump the first character */
    className[0]++; /* bump the first character */
    fprintf(stderr,"Attempting to load bogus function %s for bogus type %s ...\n",creator,className);
    createComponent = (void *(*)())CCA_DynamicSymbol(adltestlib,creator);
    if (createComponent==NULL) {
      fprintf(stderr,"\nFailed as expected {%s}.\n",creator);
    } else {
      numerrs++;
      fprintf(stderr,"Succeeded unexpectedly!\n");
    }
    free(creator);
    free(className);
  }
  
  
  CCA_DynamicUnLoad(adltestlib);

  exit(numerrs);
}
