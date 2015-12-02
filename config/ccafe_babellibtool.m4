dnl macro CCAFE_BABEL_LIBTOOL
dnl --------------------------------------------------------------------
dnl See if we can find a babel-libtool
dnl
dnl Side effects:
dnl defines variable BABEL_LIBTOOL as the libtool given or the one found.
dnl bombs if none given or found.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_BABEL_LIBTOOL],
[
# take babel-libtool from neo spec if present.
if ! test "x$NEOCCA_BABEL_LIBTOOL" = "x"; then
	if test -x $NEOCCA_BABEL_LIBTOOL; then
		with_babel_libtool=$NEOCCA_BABEL_LIBTOOL
	fi
fi
# take babel-libtool from cca-spec if present.
if ! test "x$CCASPEC_BABEL_BABEL_LIBTOOL" = "x"; then
	if test -x $CCASPEC_BABEL_BABEL_LIBTOOL; then
		with_babel_libtool=$CCASPEC_BABEL_BABEL_LIBTOOL
	fi
fi
AC_ARG_WITH(babel-libtool,
     [
Location of babel-libtool program.
    --with-babel-libtool=/usr/local/babel/bin/babel-libtool (where is babel-libtool?)
        On some platforms, a regular GNU libtool may also work if specifed, but this is 
        not generally supported by ccaffeine. In particular, on many 64 bit platforms
	libtool before version 1.5.10+patches does not work well for shared libraries.
  ] ,
    , [with_babel_libtool=no])

ccafe_babel_libtool_locs=/usr/local/babel/bin:$HOME/babel/bin:/$HOME/cca/babel/bin:$HOME/cca/install/babel/bin
#
case "$with_babel_libtool" in
    no)
        AC_PATH_PROG(ccafe_test_babel_libtool, babel-libtool, no, $PATH:$ccafe_babel_libtool_locs)
        ;;
#
    *)
        ccafe_test_babel_libtool=$with_babel_libtool
	AC_MSG_CHECKING([babel-libtool])
	AC_MSG_RESULT([$ccafe_test_babel_libtool])
        ;;
esac   
#
if test -x $ccafe_test_babel_libtool; then
	BABEL_LIBTOOL=$ccafe_test_babel_libtool
else
	AC_MSG_ERROR([Please specify --with-babel-libtool=/path/to/babel-libtool.
  If you do not have babel installed and cannot install it,
  you may attempt compiling Ccaffeine by specifying any other
  libtool that happens to exist. This is not guaranteed to work,
  especially if you mix Fortran in your code.])
fi
[bltversion=`$BABEL_LIBTOOL --version | grep libtool | sed -e 's%^[^0-9]*%%g' |sed -e 's% .*%%g'`]
bltbad=no
case "$bltversion" in
	0.*) bltbad=yes
	;;
	[1.[0-4].*) bltbad=yes]
	;;
esac
if test "$bltbad" = "yes" ; then
	AC_MSG_ERROR([The babel-libtool or libtool found is based on a too old
		version of libtool ($bltversion). 
        We prefer 1.5.10 or later, and need at least 1.5.])
fi
AC_SUBST(BABEL_LIBTOOL)
]
)

