dnl macro CCAFE_TOOLS_SETTING
dnl --------------------------------------------------------------------
dnl Get a hint from the user about the TOOLS setting in
dnl cxx/Makefile.Rules. Has nothing to do with the rest
dnl of the tests in configure and can utterly befuddle
dnl the build if setting given not consistent with babel build.
dnl 
dnl Side effects:
dnl defines variable and acsubst CCAFE_TOOLS CCAFE_TOOLS_COMMENT
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_TOOLS_SETTING],
[
AC_ARG_WITH(tools,
     [Override to Makefile.Rules for compiler flag heuristics:
    --with-tools={sgi,intel,solaris,portland,pgi,kai-alpha,aix,gnu}
        Mainly useful for portland group, aix, and other odd environments.
  ] , , [with_tools=""])


if test "x$with_tools" = "x"; then
    CCAFE_TOOLS_COMMENT="#"
    CCAFE_TOOLS=""
else
    CCAFE_TOOLS_COMMENT=""
    CCAFE_TOOLS="$with_tools"
fi
if test "x$CCAFE_TOOLS" = "xpgi"; then
    CCAFE_TOOLs=portland
fi

AC_SUBST(CCAFE_TOOLS)
AC_SUBST(CCAFE_TOOLS_COMMENT)
]
)
