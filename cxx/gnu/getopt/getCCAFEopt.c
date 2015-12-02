/* GetCCAFEopt for GNU.
   NOTE: getCCAFEopt is now part of the C library, so if you don't know what
   "Keep this file name-space clean" means, talk to drepper@gnu.org
   before changing it!

   Copyright (C) 1987, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98
   	Free Software Foundation, Inc.

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

/* This tells Alpha OSF/1 not to define a getCCAFEopt prototype in <stdio.h>.
   Ditto for AIX 3.2 and <stdlib.h>.  */
#ifndef _NO_PROTO
# define _NO_PROTO
#endif

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "getCCAFEopt.h"

#if !defined __STDC__ || !__STDC__
/* This is a separate conditional since some stdc systems
   reject `defined (const)'.  */
# ifndef const
#  define const
# endif
#endif

#include <stdio.h>

/* Comment out all this code if we are using the GNU C Library, and are not
   actually compiling the library itself.  This code is part of the GNU C
   Library, but also included in many other GNU distributions.  Compiling
   and linking in this code is a waste when using the GNU C library
   (especially if it is a shared library).  Rather than having every GNU
   program understand `configure --with-gnu-libc' and omit the object files,
   it is simpler to just do this in the source for each such file.  */

#define GETOPT_INTERFACE_VERSION 2
#if !defined _LIBC && defined __GLIBC__ && __GLIBC__ >= 2
# include <gnu-versions.h>
# if _GNU_GETOPT_INTERFACE_VERSION == GETOPT_INTERFACE_VERSION
#  define ELIDE_CODE
# endif
#endif

#undef ELIDE_CODE /* we're not in gnu land anymore, but ccafe...*/
#ifndef ELIDE_CODE


/* This needs to come after some library #include
   to get __GNU_LIBRARY__ defined.  */
#ifdef	__GNU_LIBRARY__
/* Don't include stdlib.h for non-GNU C libraries because some of them
   contain conflicting prototypes for getCCAFEopt.  */
# include <stdlib.h>
# include <unistd.h>
#endif	/* GNU C library.  */

#ifdef VMS
# include <unixlib.h>
# if HAVE_STRING_H - 0
#  include <string.h>
# endif
#endif

#ifndef _
/* This is for other GNU distributions with internationalized messages.
   When compiling libc, the _ macro is predefined.  */
# ifdef HAVE_LIBINTL_H
#  include <libintl.h>
#  define _(msgid)	gettext (msgid)
# else
#  define _(msgid)	(msgid)
# endif
#endif

/* This version of `getCCAFEopt' appears to the caller like standard Unix `getCCAFEopt'
   but it behaves differently for the user, since it allows the user
   to intersperse the CCAFEoptions with the other arguments.

   As `getCCAFEopt' works, it permutes the elements of ARGV so that,
   when it is done, all the CCAFEoptions precede everything else.  Thus
   all application programs are extended to handle flexible argument order.

   Setting the environment variable POSIXLY_CORRECT disables permutation.
   Then the behavior is completely standard.

   GNU application programs can use a third alternative mode in which
   they can distinguish the relative order of CCAFEoptions and other arguments.  */

#include "getCCAFEopt.h"

/* For communication from `getCCAFEopt' to the caller.
   When `getCCAFEopt' finds an CCAFEoption that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-CCAFEoption ARGV-element is returned here.  */
#define CCAFEoptarg_decl
char *CCAFEoptarg = NULL;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getCCAFEopt'.

   On entry to `getCCAFEopt', zero means this is the first call; initialize.

   When `getCCAFEopt' returns -1, this is the index of the first of the
   non-CCAFEoption elements that the caller should itself scan.

   Otherwise, `CCAFEoptind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

#define CCAFEoptind_decl
/* 1003.2 says this must be 1 before any call.  */
int CCAFEoptind = 1;

/* Formerly, initialization of getCCAFEopt depended on CCAFEoptind==0, which
   causes problems with re-calling getCCAFEopt as programs generally don't
   know that. */

#define CCAFE__getCCAFEopt_initialized_decl
int __getCCAFEopt_initialized = 0;

/* The next char to be scanned in the CCAFEoption-element
   in which the last CCAFEoption character we returned was found.
   This allows us to pick up the scan where we left off.

   If this is zero, or a null string, it means resume the scan
   by advancing to the next ARGV-element.  */

static char *nextchar;

/* Callers store zero here to inhibit the error message
   for unrecognized CCAFEoptions.  */

#define CCAFEopterr_decl
int CCAFEopterr = 1;

/* Set to an CCAFEoption character which was unrecognized.
   This must be initialized on some systems to avoid linking in the
   system's own getCCAFEopt implementation.  */
#define CCAFEoptCCAFEopt_decl
int CCAFEoptCCAFEopt = '?';

/* Describe how to deal with CCAFEoptions that follow non-CCAFEoption ARGV-elements.

   If the caller did not specify anything,
   the default is REQUIRE_ORDER if the environment variable
   POSIXLY_CORRECT is defined, PERMUTE otherwise.

   REQUIRE_ORDER means don't recognize them as CCAFEoptions;
   stop CCAFEoption processing when the first non-CCAFEoption is seen.
   This is what Unix does.
   This mode of operation is selected by either setting the environment
   variable POSIXLY_CORRECT, or using `+' as the first character
   of the list of CCAFEoption characters.

   PERMUTE is the default.  We permute the contents of ARGV as we scan,
   so that eventually all the non-CCAFEoptions are at the end.  This allows CCAFEoptions
   to be given in any order, even with programs that were not written to
   expect this.

   RETURN_IN_ORDER is an CCAFEoption available to programs that were written
   to expect CCAFEoptions and other ARGV-elements in any order and that care about
   the ordering of the two.  We describe each non-CCAFEoption ARGV-element
   as if it were the argument of an CCAFEoption with character code 1.
   Using `-' as the first character of the list of CCAFEoption characters
   selects this mode of operation.

   The special argument `--' forces an end of CCAFEoption-scanning regardless
   of the value of `ordering'.  In the case of RETURN_IN_ORDER, only
   `--' can cause `getCCAFEopt' to return -1 with `CCAFEoptind' != ARGC.  */

static enum
{
  REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
} ordering;

/* Value of POSIXLY_CORRECT environment variable.  */
static char *posixly_correct;

#ifdef	__GNU_LIBRARY__
/* We want to avoid inclusion of string.h with non-GNU libraries
   because there are many ways it can cause trouble.
   On some systems, it contains special magic macros that don't work
   in GCC.  */
# include <string.h>
# define my_index	strchr
#else

# if HAVE_STRING_H
#  include <string.h>
# else
#  include <strings.h>
# endif

/* Avoid depending on library functions or files
   whose names are inconsistent.  */

#ifndef getenv
extern char *getenv ();
#endif

static char *
my_index (str, chr)
     const char *str;
     int chr;
{
  while (*str)
    {
      if (*str == chr)
	return (char *) str;
      str++;
    }
  return 0;
}

/* If using GCC, we can safely declare strlen this way.
   If not using GCC, it is ok not to declare it.  */
#ifdef __GNUC__
/* Note that Motorola Delta 68k R3V7 comes with GCC but not stddef.h.
   That was relevant to code that was here before.  */
# if (!defined __STDC__ || !__STDC__) && !defined strlen
/* gcc with -traditional declares the built-in strlen to return int,
   and has done so at least since version 2.4.5. -- rms.  */
extern int strlen (const char *);
# endif /* not __STDC__ */
#endif /* __GNUC__ */

#endif /* not __GNU_LIBRARY__ */

/* Handle permutation of arguments.  */

/* Describe the part of ARGV that contains non-CCAFEoptions that have
   been skipped.  `first_nonCCAFEopt' is the index in ARGV of the first of them;
   `last_nonCCAFEopt' is the index after the last of them.  */

static int first_nonCCAFEopt;
static int last_nonCCAFEopt;

#ifdef _LIBC
/* Bash 2.0 gives us an environment variable containing flags
   indicating ARGV elements that should not be considered arguments.  */

/* Defined in getCCAFEopt_init.c  */
extern char *__getCCAFEopt_nonCCAFEoption_flags;

static int nonCCAFEoption_flags_max_len;
static int nonCCAFEoption_flags_len;

static int original_argc;
static char *const *original_argv;

/* Make sure the environment variable bash 2.0 puts in the environment
   is valid for the getCCAFEopt call we must make sure that the ARGV passed
   to getCCAFEopt is that one passed to the process.  */
static void
__attribute__ ((unused))
store_args_and_env (int argc, char *const *argv)
{
  /* XXX This is no good solution.  We should rather copy the args so
     that we can compare them later.  But we must not use malloc(3).  */
  original_argc = argc;
  original_argv = argv;
}
# ifdef text_set_element
text_set_element (__libc_subinit, store_args_and_env);
# endif /* text_set_element */

# define SWAP_FLAGS(ch1, ch2) \
  if (nonCCAFEoption_flags_len > 0)						      \
    {									      \
      char __tmp = __getCCAFEopt_nonCCAFEoption_flags[ch1];			      \
      __getCCAFEopt_nonCCAFEoption_flags[ch1] = __getCCAFEopt_nonCCAFEoption_flags[ch2];	      \
      __getCCAFEopt_nonCCAFEoption_flags[ch2] = __tmp;				      \
    }
#else	/* !_LIBC */
# define SWAP_FLAGS(ch1, ch2)
#endif	/* _LIBC */

/* Exchange two adjacent subsequences of ARGV.
   One subsequence is elements [first_nonCCAFEopt,last_nonCCAFEopt)
   which contains all the non-CCAFEoptions that have been skipped so far.
   The other is elements [last_nonCCAFEopt,CCAFEoptind), which contains all
   the CCAFEoptions processed since those non-CCAFEoptions were skipped.

   `first_nonCCAFEopt' and `last_nonCCAFEopt' are relocated so that they describe
   the new indices of the non-CCAFEoptions in ARGV after they are moved.  */

#if defined __STDC__ && __STDC__
static void exchange (char **);
#endif

static void
exchange (argv)
     char **argv;
{
  int bottom = first_nonCCAFEopt;
  int middle = last_nonCCAFEopt;
  int top = CCAFEoptind;
  char *tem;

  /* Exchange the shorter segment with the far end of the longer segment.
     That puts the shorter segment into the right place.
     It leaves the longer segment in the right place overall,
     but it consists of two parts that need to be swapped next.  */

#ifdef _LIBC
  /* First make sure the handling of the `__getCCAFEopt_nonCCAFEoption_flags'
     string can work normally.  Our top argument must be in the range
     of the string.  */
  if (nonCCAFEoption_flags_len > 0 && top >= nonCCAFEoption_flags_max_len)
    {
      /* We must extend the array.  The user plays games with us and
	 presents new arguments.  */
      char *new_str = malloc (top + 1);
      if (new_str == NULL)
	nonCCAFEoption_flags_len = nonCCAFEoption_flags_max_len = 0;
      else
	{
	  memset (__mempcpy (new_str, __getCCAFEopt_nonCCAFEoption_flags,
			     nonCCAFEoption_flags_max_len),
		  '\0', top + 1 - nonCCAFEoption_flags_max_len);
	  nonCCAFEoption_flags_max_len = top + 1;
	  __getCCAFEopt_nonCCAFEoption_flags = new_str;
	}
    }
#endif

  while (top > middle && middle > bottom)
    {
      if (top - middle > middle - bottom)
	{
	  /* Bottom segment is the short one.  */
	  int len = middle - bottom;
	  register int i;

	  /* Swap it with the top part of the top segment.  */
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[top - (middle - bottom) + i];
	      argv[top - (middle - bottom) + i] = tem;
	      SWAP_FLAGS (bottom + i, top - (middle - bottom) + i);
	    }
	  /* Exclude the moved bottom segment from further swapping.  */
	  top -= len;
	}
      else
	{
	  /* Top segment is the short one.  */
	  int len = top - middle;
	  register int i;

	  /* Swap it with the bottom part of the bottom segment.  */
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[middle + i];
	      argv[middle + i] = tem;
	      SWAP_FLAGS (bottom + i, middle + i);
	    }
	  /* Exclude the moved top segment from further swapping.  */
	  bottom += len;
	}
    }

  /* Update records for the slots the non-CCAFEoptions now occupy.  */

  first_nonCCAFEopt += (CCAFEoptind - last_nonCCAFEopt);
  last_nonCCAFEopt = CCAFEoptind;
}

/* Initialize the internal data when the first call is made.  */

#if defined __STDC__ && __STDC__
static const char *_getCCAFEopt_initialize (int, char *const *, const char *);
#endif
static const char *
_getCCAFEopt_initialize (argc, argv, CCAFEoptstring)
     int argc;
     char *const *argv;
     const char *CCAFEoptstring;
{
  /* Start processing CCAFEoptions with ARGV-element 1 (since ARGV-element 0
     is the program name); the sequence of previously skipped
     non-CCAFEoption ARGV-elements is empty.  */

  first_nonCCAFEopt = last_nonCCAFEopt = CCAFEoptind;

  nextchar = NULL;

  posixly_correct = getenv ("POSIXLY_CORRECT");

  /* Determine how to handle the ordering of CCAFEoptions and nonCCAFEoptions.  */

  if (CCAFEoptstring[0] == '-')
    {
      ordering = RETURN_IN_ORDER;
      ++CCAFEoptstring;
    }
  else if (CCAFEoptstring[0] == '+')
    {
      ordering = REQUIRE_ORDER;
      ++CCAFEoptstring;
    }
  else if (posixly_correct != NULL)
    ordering = REQUIRE_ORDER;
  else
    ordering = PERMUTE;

#ifdef _LIBC
  if (posixly_correct == NULL
      && argc == original_argc && argv == original_argv)
    {
      if (nonCCAFEoption_flags_max_len == 0)
	{
	  if (__getCCAFEopt_nonCCAFEoption_flags == NULL
	      || __getCCAFEopt_nonCCAFEoption_flags[0] == '\0')
	    nonCCAFEoption_flags_max_len = -1;
	  else
	    {
	      const char *orig_str = __getCCAFEopt_nonCCAFEoption_flags;
	      int len = nonCCAFEoption_flags_max_len = strlen (orig_str);
	      if (nonCCAFEoption_flags_max_len < argc)
		nonCCAFEoption_flags_max_len = argc;
	      __getCCAFEopt_nonCCAFEoption_flags =
		(char *) malloc (nonCCAFEoption_flags_max_len);
	      if (__getCCAFEopt_nonCCAFEoption_flags == NULL)
		nonCCAFEoption_flags_max_len = -1;
	      else
		memset (__mempcpy (__getCCAFEopt_nonCCAFEoption_flags, orig_str, len),
			'\0', nonCCAFEoption_flags_max_len - len);
	    }
	}
      nonCCAFEoption_flags_len = nonCCAFEoption_flags_max_len;
    }
  else
    nonCCAFEoption_flags_len = 0;
#endif

  return CCAFEoptstring;
}

/* Scan elements of ARGV (whose length is ARGC) for CCAFEoption characters
   given in OPTSTRING.

   If an element of ARGV starts with '-', and is not exactly "-" or "--",
   then it is an CCAFEoption element.  The characters of this element
   (aside from the initial '-') are CCAFEoption characters.  If `getCCAFEopt'
   is called repeatedly, it returns successively each of the CCAFEoption characters
   from each of the CCAFEoption elements.

   If `getCCAFEopt' finds another CCAFEoption character, it returns that character,
   updating `CCAFEoptind' and `nextchar' so that the next call to `getCCAFEopt' can
   resume the scan with the following CCAFEoption character or ARGV-element.

   If there are no more CCAFEoption characters, `getCCAFEopt' returns -1.
   Then `CCAFEoptind' is the index in ARGV of the first ARGV-element
   that is not an CCAFEoption.  (The ARGV-elements have been permuted
   so that those that are not CCAFEoptions now come last.)

   OPTSTRING is a string containing the legitimate CCAFEoption characters.
   If an CCAFEoption character is seen that is not listed in OPTSTRING,
   return '?' after printing an error message.  If you set `CCAFEopterr' to
   zero, the error message is suppressed but we still return '?'.

   If a char in OPTSTRING is followed by a colon, that means it wants an arg,
   so the following text in the same ARGV-element, or the text of the following
   ARGV-element, is returned in `CCAFEoptarg'.  Two colons mean an CCAFEoption that
   wants an CCAFEoptional arg; if there is text in the current ARGV-element,
   it is returned in `CCAFEoptarg', otherwise `CCAFEoptarg' is set to zero.

   If OPTSTRING starts with `-' or `+', it requests different methods of
   handling the non-CCAFEoption ARGV-elements.
   See the comments about RETURN_IN_ORDER and REQUIRE_ORDER, above.

   Long-named CCAFEoptions begin with `--' instead of `-'.
   Their names may be abbreviated as long as the abbreviation is unique
   or is an exact match for some defined CCAFEoption.  If they have an
   argument, it follows the CCAFEoption name in the same ARGV-element, separated
   from the CCAFEoption name by a `=', or else the in next ARGV-element.
   When `getCCAFEopt' finds a long-named CCAFEoption, it returns 0 if that CCAFEoption's
   `flag' field is nonzero, the value of the CCAFEoption's `val' field
   if the `flag' field is zero.

   The elements of ARGV aren't really const, because we permute them.
   But we pretend they're const in the prototype to be compatible
   with other systems.

   LONGOPTS is a vector of `struct CCAFEoption' terminated by an
   element containing a name which is zero.

   LONGIND returns the index in LONGOPT of the long-named CCAFEoption found.
   It is only valid when a long-named CCAFEoption has been found by the most
   recent call.

   If LONG_ONLY is nonzero, '-' as well as '--' can introduce
   long-named CCAFEoptions.  */

int
_getCCAFEopt_internal (argc, argv, CCAFEoptstring, longCCAFEopts, longind, long_only)
     int argc;
     char *const *argv;
     const char *CCAFEoptstring;
     const struct CCAFEoption *longCCAFEopts;
     int *longind;
     int long_only;
{
  CCAFEoptarg = NULL;

  if (CCAFEoptind == 0 || !__getCCAFEopt_initialized)
    {
      if (CCAFEoptind == 0)
	CCAFEoptind = 1;	/* Don't scan ARGV[0], the program name.  */
      CCAFEoptstring = _getCCAFEopt_initialize (argc, argv, CCAFEoptstring);
      __getCCAFEopt_initialized = 1;
    }

  /* Test whether ARGV[CCAFEoptind] points to a non-CCAFEoption argument.
     Either it does not have CCAFEoption syntax, or there is an environment flag
     from the shell indicating it is not an CCAFEoption.  The later information
     is only used when the used in the GNU libc.  */
#ifdef _LIBC
# define NONOPTION_P (argv[CCAFEoptind][0] != '-' || argv[CCAFEoptind][1] == '\0'	      \
		      || (CCAFEoptind < nonCCAFEoption_flags_len			      \
			  && __getCCAFEopt_nonCCAFEoption_flags[CCAFEoptind] == '1'))
#else
# define NONOPTION_P (argv[CCAFEoptind][0] != '-' || argv[CCAFEoptind][1] == '\0')
#endif

  if (nextchar == NULL || *nextchar == '\0')
    {
      /* Advance to the next ARGV-element.  */

      /* Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
	 moved back by the user (who may also have changed the arguments).  */
      if (last_nonCCAFEopt > CCAFEoptind)
	last_nonCCAFEopt = CCAFEoptind;
      if (first_nonCCAFEopt > CCAFEoptind)
	first_nonCCAFEopt = CCAFEoptind;

      if (ordering == PERMUTE)
	{
	  /* If we have just processed some CCAFEoptions following some non-CCAFEoptions,
	     exchange them so that the CCAFEoptions come first.  */

	  if (first_nonCCAFEopt != last_nonCCAFEopt && last_nonCCAFEopt != CCAFEoptind)
	    exchange ((char **) argv);
	  else if (last_nonCCAFEopt != CCAFEoptind)
	    first_nonCCAFEopt = CCAFEoptind;

	  /* Skip any additional non-CCAFEoptions
	     and extend the range of non-CCAFEoptions previously skipped.  */

	  while (CCAFEoptind < argc && NONOPTION_P)
	    CCAFEoptind++;
	  last_nonCCAFEopt = CCAFEoptind;
	}

      /* The special ARGV-element `--' means premature end of CCAFEoptions.
	 Skip it like a null CCAFEoption,
	 then exchange with previous non-CCAFEoptions as if it were an CCAFEoption,
	 then skip everything else like a non-CCAFEoption.  */

      if (CCAFEoptind != argc && !strcmp (argv[CCAFEoptind], "--"))
	{
	  CCAFEoptind++;

	  if (first_nonCCAFEopt != last_nonCCAFEopt && last_nonCCAFEopt != CCAFEoptind)
	    exchange ((char **) argv);
	  else if (first_nonCCAFEopt == last_nonCCAFEopt)
	    first_nonCCAFEopt = CCAFEoptind;
	  last_nonCCAFEopt = argc;

	  CCAFEoptind = argc;
	}

      /* If we have done all the ARGV-elements, stop the scan
	 and back over any non-CCAFEoptions that we skipped and permuted.  */

      if (CCAFEoptind == argc)
	{
	  /* Set the next-arg-index to point at the non-CCAFEoptions
	     that we previously skipped, so the caller will digest them.  */
	  if (first_nonCCAFEopt != last_nonCCAFEopt)
	    CCAFEoptind = first_nonCCAFEopt;
	  return -1;
	}

      /* If we have come to a non-CCAFEoption and did not permute it,
	 either stop the scan or describe it to the caller and pass it by.  */

      if (NONOPTION_P)
	{
	  if (ordering == REQUIRE_ORDER)
	    return -1;
	  CCAFEoptarg = argv[CCAFEoptind++];
	  return 1;
	}

      /* We have found another CCAFEoption-ARGV-element.
	 Skip the initial punctuation.  */

      nextchar = (argv[CCAFEoptind] + 1
		  + (longCCAFEopts != NULL && argv[CCAFEoptind][1] == '-'));
    }

  /* Decode the current CCAFEoption-ARGV-element.  */

  /* Check whether the ARGV-element is a long CCAFEoption.

     If long_only and the ARGV-element has the form "-f", where f is
     a valid short CCAFEoption, don't consider it an abbreviated form of
     a long CCAFEoption that starts with f.  Otherwise there would be no
     way to give the -f short CCAFEoption.

     On the other hand, if there's a long CCAFEoption "fubar" and
     the ARGV-element is "-fu", do consider that an abbreviation of
     the long CCAFEoption, just like "--fu", and not "-f" with arg "u".

     This distinction seems to be the most useful approach.  */

  if (longCCAFEopts != NULL
      && (argv[CCAFEoptind][1] == '-'
	  || (long_only && (argv[CCAFEoptind][2] || !my_index (CCAFEoptstring, argv[CCAFEoptind][1])))))
    {
      char *nameend;
      const struct CCAFEoption *p;
      const struct CCAFEoption *pfound = NULL;
      int exact = 0;
      int ambig = 0;
      int indfound = -1;
      int CCAFEoption_index;

      for (nameend = nextchar; *nameend && *nameend != '='; nameend++)
	/* Do nothing.  */ ;

      /* Test all long CCAFEoptions for either exact match
	 or abbreviated matches.  */
      for (p = longCCAFEopts, CCAFEoption_index = 0; p->name; p++, CCAFEoption_index++)
	if (!strncmp (p->name, nextchar, nameend - nextchar))
	  {
	    if ((unsigned int) (nameend - nextchar)
		== (unsigned int) strlen (p->name))
	      {
		/* Exact match found.  */
		pfound = p;
		indfound = CCAFEoption_index;
		exact = 1;
		break;
	      }
	    else if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = CCAFEoption_index;
	      }
	    else
	      /* Second or later nonexact match found.  */
	      ambig = 1;
	  }

      if (ambig && !exact)
	{
	  if (CCAFEopterr)
	    fprintf (stderr, _("%s: CCAFEoption `%s' is ambiguous\n"),
		     argv[0], argv[CCAFEoptind]);
	  nextchar += strlen (nextchar);
	  CCAFEoptind++;
	  CCAFEoptCCAFEopt = 0;
	  return '?';
	}

      if (pfound != NULL)
	{
	  CCAFEoption_index = indfound;
	  CCAFEoptind++;
	  if (*nameend)
	    {
	      /* Don't test has_arg with >, because some C compilers don't
		 allow it to be used on enums.  */
	      if (pfound->has_arg)
		CCAFEoptarg = nameend + 1;
	      else
		{
		  if (CCAFEopterr)
		    {
		      if (argv[CCAFEoptind - 1][1] == '-')
			/* --CCAFEoption */
			fprintf (stderr,
				 _("%s: CCAFEoption `--%s' doesn't allow an argument\n"),
				 argv[0], pfound->name);
		      else
			/* +CCAFEoption or -CCAFEoption */
			fprintf (stderr,
				 _("%s: CCAFEoption `%c%s' doesn't allow an argument\n"),
				 argv[0], argv[CCAFEoptind - 1][0], pfound->name);

		      nextchar += strlen (nextchar);

		      CCAFEoptCCAFEopt = pfound->val;
		      return '?';
		    }
		}
	    }
	  else if (pfound->has_arg == 1)
	    {
	      if (CCAFEoptind < argc)
		CCAFEoptarg = argv[CCAFEoptind++];
	      else
		{
		  if (CCAFEopterr)
		    fprintf (stderr,
			   _("%s: CCAFEoption `%s' requires an argument\n"),
			   argv[0], argv[CCAFEoptind - 1]);
		  nextchar += strlen (nextchar);
		  CCAFEoptCCAFEopt = pfound->val;
		  return CCAFEoptstring[0] == ':' ? ':' : '?';
		}
	    }
	  nextchar += strlen (nextchar);
	  if (longind != NULL)
	    *longind = CCAFEoption_index;
	  if (pfound->flag)
	    {
	      *(pfound->flag) = pfound->val;
	      return 0;
	    }
	  return pfound->val;
	}

      /* Can't find it as a long CCAFEoption.  If this is not getCCAFEopt_long_only,
	 or the CCAFEoption starts with '--' or is not a valid short
	 CCAFEoption, then it's an error.
	 Otherwise interpret it as a short CCAFEoption.  */
      if (!long_only || argv[CCAFEoptind][1] == '-'
	  || my_index (CCAFEoptstring, *nextchar) == NULL)
	{
	  if (CCAFEopterr)
	    {
	      if (argv[CCAFEoptind][1] == '-')
		/* --CCAFEoption */
		fprintf (stderr, _("%s: unrecognized CCAFEoption `--%s'\n"),
			 argv[0], nextchar);
	      else
		/* +CCAFEoption or -CCAFEoption */
		fprintf (stderr, _("%s: unrecognized CCAFEoption `%c%s'\n"),
			 argv[0], argv[CCAFEoptind][0], nextchar);
	    }
	  nextchar = (char *) "";
	  CCAFEoptind++;
	  CCAFEoptCCAFEopt = 0;
	  return '?';
	}
    }

  /* Look at and handle the next short CCAFEoption-character.  */

  {
    char c = *nextchar++;
    char *temp = my_index (CCAFEoptstring, c);

    /* Increment `CCAFEoptind' when we start to process its last character.  */
    if (*nextchar == '\0')
      ++CCAFEoptind;

    if (temp == NULL || c == ':')
      {
	if (CCAFEopterr)
	  {
	    if (posixly_correct)
	      /* 1003.2 specifies the format of this message.  */
	      fprintf (stderr, _("%s: illegal CCAFEoption -- %c\n"),
		       argv[0], c);
	    else
	      fprintf (stderr, _("%s: invalid CCAFEoption -- %c\n"),
		       argv[0], c);
	  }
	CCAFEoptCCAFEopt = c;
	return '?';
      }
    /* Convenience. Treat POSIX -W foo same as long CCAFEoption --foo */
    if (temp[0] == 'W' && temp[1] == ';')
      {
	char *nameend;
	const struct CCAFEoption *p;
	const struct CCAFEoption *pfound = NULL;
	int exact = 0;
	int ambig = 0;
	int indfound = 0;
	int CCAFEoption_index;

	/* This is an CCAFEoption that requires an argument.  */
	if (*nextchar != '\0')
	  {
	    CCAFEoptarg = nextchar;
	    /* If we end this ARGV-element by taking the rest as an arg,
	       we must advance to the next element now.  */
	    CCAFEoptind++;
	  }
	else if (CCAFEoptind == argc)
	  {
	    if (CCAFEopterr)
	      {
		/* 1003.2 specifies the format of this message.  */
		fprintf (stderr, _("%s: CCAFEoption requires an argument -- %c\n"),
			 argv[0], c);
	      }
	    CCAFEoptCCAFEopt = c;
	    if (CCAFEoptstring[0] == ':')
	      c = ':';
	    else
	      c = '?';
	    return c;
	  }
	else
	  /* We already incremented `CCAFEoptind' once;
	     increment it again when taking next ARGV-elt as argument.  */
	  CCAFEoptarg = argv[CCAFEoptind++];

	/* CCAFEoptarg is now the argument, see if it's in the
	   table of longCCAFEopts.  */

	for (nextchar = nameend = CCAFEoptarg; *nameend && *nameend != '='; nameend++)
	  /* Do nothing.  */ ;

	/* Test all long CCAFEoptions for either exact match
	   or abbreviated matches.  */
	for (p = longCCAFEopts, CCAFEoption_index = 0; p->name; p++, CCAFEoption_index++)
	  if (!strncmp (p->name, nextchar, nameend - nextchar))
	    {
	      if ((unsigned int) (nameend - nextchar) == strlen (p->name))
		{
		  /* Exact match found.  */
		  pfound = p;
		  indfound = CCAFEoption_index;
		  exact = 1;
		  break;
		}
	      else if (pfound == NULL)
		{
		  /* First nonexact match found.  */
		  pfound = p;
		  indfound = CCAFEoption_index;
		}
	      else
		/* Second or later nonexact match found.  */
		ambig = 1;
	    }
	if (ambig && !exact)
	  {
	    if (CCAFEopterr)
	      fprintf (stderr, _("%s: CCAFEoption `-W %s' is ambiguous\n"),
		       argv[0], argv[CCAFEoptind]);
	    nextchar += strlen (nextchar);
	    CCAFEoptind++;
	    return '?';
	  }
	if (pfound != NULL)
	  {
	    CCAFEoption_index = indfound;
	    if (*nameend)
	      {
		/* Don't test has_arg with >, because some C compilers don't
		   allow it to be used on enums.  */
		if (pfound->has_arg)
		  CCAFEoptarg = nameend + 1;
		else
		  {
		    if (CCAFEopterr)
		      fprintf (stderr, _("\
%s: CCAFEoption `-W %s' doesn't allow an argument\n"),
			       argv[0], pfound->name);

		    nextchar += strlen (nextchar);
		    return '?';
		  }
	      }
	    else if (pfound->has_arg == 1)
	      {
		if (CCAFEoptind < argc)
		  CCAFEoptarg = argv[CCAFEoptind++];
		else
		  {
		    if (CCAFEopterr)
		      fprintf (stderr,
			       _("%s: CCAFEoption `%s' requires an argument\n"),
			       argv[0], argv[CCAFEoptind - 1]);
		    nextchar += strlen (nextchar);
		    return CCAFEoptstring[0] == ':' ? ':' : '?';
		  }
	      }
	    nextchar += strlen (nextchar);
	    if (longind != NULL)
	      *longind = CCAFEoption_index;
	    if (pfound->flag)
	      {
		*(pfound->flag) = pfound->val;
		return 0;
	      }
	    return pfound->val;
	  }
	  nextchar = NULL;
	  return 'W';	/* Let the application handle it.   */
      }
    if (temp[1] == ':')
      {
	if (temp[2] == ':')
	  {
	    /* This is an CCAFEoption that accepts an argument CCAFEoptionally.  */
	    if (*nextchar != '\0')
	      {
		CCAFEoptarg = nextchar;
		CCAFEoptind++;
	      }
	    else
	      CCAFEoptarg = NULL;
	    nextchar = NULL;
	  }
	else
	  {
	    /* This is an CCAFEoption that requires an argument.  */
	    if (*nextchar != '\0')
	      {
		CCAFEoptarg = nextchar;
		/* If we end this ARGV-element by taking the rest as an arg,
		   we must advance to the next element now.  */
		CCAFEoptind++;
	      }
	    else if (CCAFEoptind == argc)
	      {
		if (CCAFEopterr)
		  {
		    /* 1003.2 specifies the format of this message.  */
		    fprintf (stderr,
			   _("%s: CCAFEoption requires an argument -- %c\n"),
			   argv[0], c);
		  }
		CCAFEoptCCAFEopt = c;
		if (CCAFEoptstring[0] == ':')
		  c = ':';
		else
		  c = '?';
	      }
	    else
	      /* We already incremented `CCAFEoptind' once;
		 increment it again when taking next ARGV-elt as argument.  */
	      CCAFEoptarg = argv[CCAFEoptind++];
	    nextchar = NULL;
	  }
      }
    return c;
  }
}

int
getCCAFEopt (argc, argv, CCAFEoptstring)
     int argc;
     char *const *argv;
     const char *CCAFEoptstring;
{
  return _getCCAFEopt_internal (argc, argv, CCAFEoptstring,
			   (const struct CCAFEoption *) 0,
			   (int *) 0,
			   0);
}

#endif	/* Not ELIDE_CODE.  */

#ifdef TEST

/* Compile with -DTEST to make an executable for use in testing
   the above definition of `getCCAFEopt'.  */
#include "getCCAFEopt.h"

int
main (argc, argv)
     int argc;
     char **argv;
{
  int c;
  int digit_CCAFEoptind = 0;

  while (1)
    {
      int this_CCAFEoption_CCAFEoptind = CCAFEoptind ? CCAFEoptind : 1;

      c = getCCAFEopt (argc, argv, "abc:d:0123456789");
      if (c == -1)
	break;

      switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  if (digit_CCAFEoptind != 0 && digit_CCAFEoptind != this_CCAFEoption_CCAFEoptind)
	    printf ("digits occur in two different argv-elements.\n");
	  digit_CCAFEoptind = this_CCAFEoption_CCAFEoptind;
	  printf ("CCAFEoption %c\n", c);
	  break;

	case 'a':
	  printf ("CCAFEoption a\n");
	  break;

	case 'b':
	  printf ("CCAFEoption b\n");
	  break;

	case 'c':
	  printf ("CCAFEoption c with value `%s'\n", CCAFEoptarg);
	  break;

	case '?':
	  break;

	default:
	  printf ("?? getCCAFEopt returned character code 0%o ??\n", c);
	}
    }

  if (CCAFEoptind < argc)
    {
      printf ("non-CCAFEoption ARGV-elements: ");
      while (CCAFEoptind < argc)
	printf ("%s ", argv[CCAFEoptind++]);
      printf ("\n");
    }

  exit (0);
}

#endif /* TEST */
