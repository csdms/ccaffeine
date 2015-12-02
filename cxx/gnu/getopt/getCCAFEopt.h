/* Declarations for getCCAFEopt. (produced from gnu getopt with 
 *  sed -e 's/opt/CCAFEopt/g')
   Copyright (C) 1989,90,91,92,93,94,96,97 Free Software Foundation, Inc.

   NOTE: The canonical source of this file is maintained with the GNU C Library.
   Bugs can be reported to bug-glibc@gnu.org.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your CCAFEoption) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

#ifndef _GETCCAFEOPT_H
#define _GETCCAFEOPT_H 1

#ifdef	__cplusplus
extern "C" {
#endif

/* For communication from `getCCAFEopt' to the caller.
   When `getCCAFEopt' finds an CCAFEoption that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-CCAFEoption ARGV-element is returned here.  */

extern char *CCAFEoptarg;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getCCAFEopt'.

   On entry to `getCCAFEopt', zero means this is the first call; initialize.

   When `getCCAFEopt' returns -1, this is the index of the first of the
   non-CCAFEoption elements that the caller should itself scan.

   Otherwise, `CCAFEoptind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

extern int CCAFEoptind;

/* Callers store zero here to inhibit the error message `getCCAFEopt' prints
   for unrecognized CCAFEoptions.  */

extern int CCAFEopterr;

/* Set to an CCAFEoption character which was unrecognized.  */

extern int CCAFEoptCCAFEopt;

/* Describe the long-named CCAFEoptions requested by the application.
   The LONG_OPTIONS argument to getCCAFEopt_long or getCCAFEopt_long_only is a vector
   of `struct CCAFEoption' terminated by an element containing a name which is
   zero.

   The field `has_arg' is:
   no_argument		(or 0) if the CCAFEoption does not take an argument,
   required_argument	(or 1) if the CCAFEoption requires an argument,
   CCAFEoptional_argument 	(or 2) if the CCAFEoption takes an CCAFEoptional argument.

   If the field `flag' is not NULL, it points to a variable that is set
   to the value given in the field `val' when the CCAFEoption is found, but
   left unchanged if the CCAFEoption is not found.

   To have a long-named CCAFEoption do something other than set an `int' to
   a compiled-in constant, such as set a value from `CCAFEoptarg', set the
   CCAFEoption's `flag' field to zero and its `val' field to a nonzero
   value (the equivalent single-letter CCAFEoption character, if there is
   one).  For long CCAFEoptions that have a zero `flag' field, `getCCAFEopt'
   returns the contents of the `val' field.  */

struct CCAFEoption
{
#if defined (__STDC__) && __STDC__
  const char *name;
#else
  char *name;
#endif
  /* has_arg can't be an enum because some compilers complain about
     type mismatches in all the code that assumes it is an int.  */
  int has_arg;
  int *flag;
  int val;
};

/* Names for the values of the `has_arg' field of `struct CCAFEoption'.  */

#define	no_argument		0
#define required_argument	1
#define CCAFEoptional_argument	2

#if defined (__STDC__) && __STDC__
#ifdef __GNU_LIBRARY__
/* Many other libraries have conflicting prototypes for getCCAFEopt, with
   differences in the consts, in stdlib.h.  To avoid compilation
   errors, only prototype getCCAFEopt for the GNU C library.  */
extern int getCCAFEopt (int argc, char *const *argv, const char *shortCCAFEopts);
#else /* not __GNU_LIBRARY__ */
extern int getCCAFEopt ();
#endif /* __GNU_LIBRARY__ */
extern int getCCAFEopt_long (int argc, char *const *argv, const char *shortCCAFEopts,
		        const struct CCAFEoption *longCCAFEopts, int *longind);
extern int getCCAFEopt_long_only (int argc, char *const *argv,
			     const char *shortCCAFEopts,
		             const struct CCAFEoption *longCCAFEopts, int *longind);

/* Internal only.  Users should not call this directly.  */
extern int _getCCAFEopt_internal (int argc, char *const *argv,
			     const char *shortCCAFEopts,
		             const struct CCAFEoption *longCCAFEopts, int *longind,
			     int long_only);
#else /* not __STDC__ */
extern int getCCAFEopt (int argc, char *const *argv, const char *shortCCAFEopts);
extern int getCCAFEopt_long (int argc, char *const *argv, const char *shortCCAFEopts,
                        const struct CCAFEoption *longCCAFEopts, int *longind);
extern int getCCAFEopt_long_only (int argc, char *const *argv,
                             const char *shortCCAFEopts,
                             const struct CCAFEoption *longCCAFEopts, int *longind);

extern int _getCCAFEopt_internal ();
#endif /* __STDC__ */

#ifdef	__cplusplus
}
#endif

#endif /* getCCAFEopt.h */
