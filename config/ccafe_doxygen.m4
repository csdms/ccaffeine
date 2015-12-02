dnl macro CCAFE_DOXYGEN
dnl --------------------------------------------------------------------
dnl See if we can find doxygen, dot.
dnl accepts --with-doxygen=binary full path name, --with-dot=dirname with dot
dnl
dnl Side effects:
dnl defines variables (but not acsubst) DOXYGEN DOT DOXYGENTARG DOTTARG
dnl DOXYGENTARG : 'dox' or ''
dnl DOTTARG : YES or NO
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_DOXYGEN],
[
AC_ARG_WITH(doxygen,
    [Location of doxygen:
  --with-doxygen=EXECUTABLE
                          The location of the doxygen binary.
                          Give the full path:
                              --with-doxygen='/share/bizarre/bin/doxygen' ],
    , [with_doxygen=yes])

case "$with_doxygen" in
    no)
        #  User specified --without-doxygen;
        AC_MSG_WARN([Option '--without-doxygen'
        Causes some c++ documentation generation to be skipped.])
        cca_have_doxygen=no
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_doxygen=_searching
        ;;
    *)
        DOXYGEN="$with_doxygen"
        cca_have_doxygen=yes
        ;;
esac

if test "$with_doxygen" = _searching ; then
    AC_CHECK_PROG(doxygen_1, doxygen, doxygen, NONE)
    if test ! "$doxygen_1" = NONE ; then
        DOXYGEN=`which $doxygen_1`
        cca_have_doxygen=yes
    fi
fi

DOXYGENTARG="dox"
if test -z "$DOXYGEN" ; then
    AC_MSG_RESULT([Building without doxygen.
                  Use --with-doygen=/doxygen/location/executableName.])
    DOXYGENTARG=""
    DOXYGEN="@echo no-doxygen"
fi

DOT=""
AC_ARG_WITH(dot,
    [Location of dot:
  --with-dot=path to executable
                          The directory location of the dot binary.
                          Give the full path:
                              --with-dot='/share/bizarre/bin' ],
    , [with_dot=yes])

case "$with_dot" in
    no)
        #  User specified --without-dot;
        AC_MSG_WARN([Option '--without-dot'
        Causes c++ documentation graph generation to be skipped.])
        cca_have_dot=no
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_dot=_searching
        ;;
    *)
        DOT="$with_dot"
        cca_have_dot=yes
	if test ! -d $DOT; then
		AC_MSG_ERROR([
--with-dot requires no, yes, or the name of a directory containing the program dot.
])
	fi
	if test ! -x $DOT/dot; then
		AC_MSG_WARN([
  --with-dot=$DOT: directory given does not contain dot program. Checking the path.
])
        	with_dot=_searching
		DOT=""
	fi
        ;;
esac

if test "$with_dot" = _searching ; then
    AC_CHECK_PROG(dot_1, dot, dot, NONE)
    if test ! "$dot_1" = NONE ; then
        DOT=`which $dot_1`
        cca_have_dot=yes
    fi
fi

DOTTARG="YES"
if test -z "$DOT" ; then
    AC_MSG_RESULT([Building without dot for doxygen documentation.
                  Use --with-dot=/dot/location/bin.])
    DOTTARG="NO"
    DOT="@echo no-dot"
fi

]
)

