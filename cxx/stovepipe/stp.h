#ifndef __STP_H__
#define __STP_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** Initialize stovepipe with command line arguments. */
void 
stp_init(int argc, char** argv);

/** Return the value keyed to the commandline argument name.  */
const char* 
stp_get(const char* argName);

/** By convention, namespaces for arguments are designated with a
    selected prefix in front of the argument name separated by a dash.
    For example: myprog --myNamespace-myArgName argValue.  stp_getn is
    a convenience function that enforces that convention.  This call
    is equivalent to stp_get(strcat(strcat(namespace, "-"),argName)). 
	This implementation doesn't support multiple levels of -,
	so internal - are allowed in argName.
*/
const char* 
stp_getn(const char* namespce, const char* argName);

  /** Put a value into stovepipe. */
void
stp_put(const char* option, const char* value);

  /** Put a value into stovepipe with a namespace. */
void
stp_putn(const char* namespce, const char* option, const char* value);

  /** Stovepipe will no longer be needed. Calling on any stp function
      after this except stp_init will cause problems. */
void 
stp_shutdown();
#define STP_BUFSIZ 1024


#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif  /*/ __STP_H__*/


