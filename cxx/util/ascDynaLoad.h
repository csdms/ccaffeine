/*
 *  -----------------------------------------------------------------
 *    Copyright 1993 D.I.S. - Universita` di Pavia - Italy
 *  -----------------------------------------------------------------
 *
 *  Permission to  use,  copy,   modify,   distribute  this  software
 *  and  its  documentation foar any purpose is hereby granted without
 *  fee, provided that the above copyright  notice   appear   in  all
 *  copies   and  that both that copyright notice and this permission
 *  notice appear in supporting documentation, and that the  name  of
 *  D.I.S.   not  be  used  in advertising or publicity pertaining to
 *  distribution of the software without specific, written prior per-
 *  mission.   D.I.S.  makes no representations about the suitability
 *  of this software for any purpose.  It is provided "as is" without
 *  express or implied warranty.
 *
 *  D.I.S. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, IN-
 *  CLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN
 *  NO EVENT SHALL D.I.S.  BE LIABLE FOR  ANY  SPECIAL,  INDIRECT  OR
 *  CONSEQUENTIAL  DAMAGES  OR  ANY DAMAGES WHATSOEVER RESULTING FROM
 *  LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION  OF  CONTRACT,
 *  NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNEC-
 *  TION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */



#ifndef __ASCDYNALOAD_H_SEEN__
/**
 * Small changes made by Michael Moore (mdm@cis.ohio-state.edu)
 * December 24th, 1993.
 * The tcl sections ripped out by Kirk Abbott (ka0p@edrc.cmu.edu)
 * September 3rd, 1994.
 * To date the architectures supported are:
 * sunos, 
 * osf,
 * solaris,
 * hpux
 * sgi
 * ultrix
 * linux
 * aix, as we plunder it from tcl8
 *
 * Added AIX 3.x support. BAA.
 * Added Asc_DynamicUnLoad. Ben Allan (ballan@cs.cmu.edu) Jan 1998.
 * Your mileage may vary.
 * UnLoad alleged for sun, hp, sgi, and alpha/osf. It probably works
 * only as well as their dlclose and shl_unload do.
 *
 * May 2000, Ben Allan: Added the more general component 
 * loading API needed by CCA,
 * which does not require successfully calling an init function.
 * Either Asc_DynamicLoad() or CCA_IntrospectLibrary() can be used
 * to open a library. (each with different side effects).
 * Subsequent calls to get more symbols can
 * be made with Asc_DynamicSymbol/CCA_DynamicSymbol.
 * Given that most remaining operating systems have undergone
 * major releases, the support for more obscure OS's needs to
 * be re-verified.
 *
 * 12/2004 added osx 10.3 support.
 */
#define __ASCDYNALOAD_H_SEEN__
/** Use of this header requires
 * #include "utilities/ascConfig.h"
 * for the definition of CONST and standardized defines
 * from ./configure based on platform.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CONST_reminder

/**
 * error = Asc_DynamicLoad(path, initFun);
 * Returns 1 if fails to load the file named in path and find 
 * the symbol in initFun as an int function.
 * Otherwise returns the result of the call to initFun.
 * If initFun == NULL, calls nothing and returns 0 after opening
 * library.
 *
 * This is our simplest wrapping of dlopen. It makes provision for dynamic 
 * unloading.
 * Once all references to the previously loaded library have been
 * scheduled to be removed without further ado, it can be unloaded
 * on most architectures.
 */
extern int Asc_DynamicLoad(const char *,const char *);

/**
 * initFunPtr = CCA_IntrospectLibrary(path, initFun, local, global,
 *                                    lazy, now, verbose);
 * Returns 0 if fails to load the file named in path and find 
 * the function symbol named initFun.
 * Otherwise returns a pointer to the initFun requested which
 * must be cast appropriately.
 * This is the CCA-handy version of Asc_DynamicLoad, where we
 * want to query before really loading.
 * 
 * The usual initFun for CCA components is "getComponentList"
 * and the usual function signature is:
 *     char **argv = getComponentList();
 *     // Returns null or empty list if no components.
 *     // The list is null-terminated.
 *     // The argv is a set of strings of the format:
 *     //   C-null-constructor-function Classname
 *     // whitespace separated.
 *     // Subsequent calls to CCA_DynamicSymbol may be made
 *     // with the argument "C-null-constructor-function"
 *     // and will have the function signature:
 *     //   CCAComponent * ccac = "C-null-constructor-function"();
 * If initFun is NULL, returns NULL immediately.
 *
 * The ints local,global,lazy,now are treated as boolean (off=0)
 * flags for loading according to the definitions of 
 * <bits/dlfcn.h> RTLD_GLOBAL, RTLD_LAZY, RTLD_NOW, RTLD_LOCAL.
 * Since these are flags are bits defined by the implementation
 * of dlopen, we put this interface on top to make calling code
 * portable without it having to include the header for dlopen.
 * In the event that both local and global are specified, local wins.
 * In the event that lazy and now are both specified, now wins.
 * The verbose flag affects our noise level and may affect
 * the underlying loader noise level as well, though the latter is
 * OS-dependent.
 *
 * By appropriate use of the flags, we can snoop before loading.
 */
extern void * CCA_IntrospectLibrary(const char *,const char *, int rtld_local, int rtld_global, int rtld_lazy, int rtld_now, int verbose);

/**
 dlopen (GLOBAL|NOW) the lib and return 0 or the error code
 if any.
 Currently ported for:
 Linux, OSX
*/
extern int CCA_LoadPorts(const char *libPathName, int verbose);

/**
 * Asc_DynamicUnLoad(path);
 * Attempts to find our record of loading a module of the same
 * path and unload it. 
 *
 * This is our wrapping dlclose. It provides unloading.
 * Once all references to the previously loaded library have been
 * scheduled to be removed without further ado, it can be unloaded
 * on most architectures. Once you call this function, you damn
 * well better not reference functions or data that came from
 * the path given.
 *
 * returns the output of dlclose (shl_unload) or -3 if confused.
 *
 * CCA_DynamicUnLoad is an alias for Asc_DynamicUnLoad.
 */
extern int Asc_DynamicUnLoad(const char *);
#define CCA_DynamicUnLoad(lib) Asc_DynamicUnLoad(lib)

/**
 * yourFuncOrVar = (YOURCAST)Asc_DynamicSymbol(libraryname,symbolname);
 * rPtr =
 *  (double (*)(double *, double *))Asc_DynamicSymbol("lib.dll","calc");
 * returns you a pointer to a symbol exported from the dynamically
 * linked library named, if the library is loaded and the
 * symbol can be found in it.
 */
extern void *Asc_DynamicSymbol(const char *, const char *);
/**
 * CCA_DynamicSymbol is an alias for Asc_DynamicSymbol.
 */
#define CCA_DynamicSymbol(lib,sym) Asc_DynamicSymbol(lib,sym)

#ifdef __cplusplus
}
#endif /* cplusplus */
#endif /* __ASCDYNALOAD_H_SEEN__ */
