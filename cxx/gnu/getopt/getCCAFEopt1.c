/* getCCAFEopt_long and getCCAFEopt_long_only entry points for GNU getCCAFEopt.
   Copyright (C) 1987,88,89,90,91,92,93,94,96,97,98
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

#include "getCCAFEopt.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#if !defined __STDC__ || !__STDC__
/* This is a separate conditional since some stdc systems
   reject `defined (const)'.  */
#ifndef const
#define const
#endif
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
#include <gnu-versions.h>
#if _GNU_GETOPT_INTERFACE_VERSION == GETOPT_INTERFACE_VERSION
#define ELIDE_CODE
#endif
#endif

#undef ELIDE_CODE /* we're not in gnuland anymore but in ccafe */
#ifndef ELIDE_CODE


/* This needs to come after some library #include
   to get __GNU_LIBRARY__ defined.  */
#ifdef __GNU_LIBRARY__
#include <stdlib.h>
#endif

#ifndef	NULL
#define NULL 0
#endif

int
getCCAFEopt_long (argc, argv, CCAFEoptions, long_CCAFEoptions, CCAFEopt_index)
     int argc;
     char *const *argv;
     const char *CCAFEoptions;
     const struct CCAFEoption *long_CCAFEoptions;
     int *CCAFEopt_index;
{
  return _getCCAFEopt_internal (argc, argv, CCAFEoptions, long_CCAFEoptions, CCAFEopt_index, 0);
}

/* Like getCCAFEopt_long, but '-' as well as '--' can indicate a long CCAFEoption.
   If an CCAFEoption that starts with '-' (not '--') doesn't match a long CCAFEoption,
   but does match a short CCAFEoption, it is parsed as a short CCAFEoption
   instead.  */

int
getCCAFEopt_long_only (argc, argv, CCAFEoptions, long_CCAFEoptions, CCAFEopt_index)
     int argc;
     char *const *argv;
     const char *CCAFEoptions;
     const struct CCAFEoption *long_CCAFEoptions;
     int *CCAFEopt_index;
{
  return _getCCAFEopt_internal (argc, argv, CCAFEoptions, long_CCAFEoptions, CCAFEopt_index, 1);
}


#endif	/* Not ELIDE_CODE.  */

#ifdef TEST

#include <stdio.h>

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
      int CCAFEoption_index = 0;
      static struct CCAFEoption long_CCAFEoptions[] =
      {
	{"add", 1, 0, 0},
	{"append", 0, 0, 0},
	{"delete", 1, 0, 0},
	{"verbose", 0, 0, 0},
	{"create", 0, 0, 0},
	{"file", 1, 0, 0},
	{0, 0, 0, 0}
      };

      c = getCCAFEopt_long (argc, argv, "abc:d:0123456789",
		       long_CCAFEoptions, &CCAFEoption_index);
      if (c == -1)
	break;

      switch (c)
	{
	case 0:
	  printf ("CCAFEoption %s", long_CCAFEoptions[CCAFEoption_index].name);
	  if (CCAFEoptarg)
	    printf (" with arg %s", CCAFEoptarg);
	  printf ("\n");
	  break;

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

	case 'd':
	  printf ("CCAFEoption d with value `%s'\n", CCAFEoptarg);
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
