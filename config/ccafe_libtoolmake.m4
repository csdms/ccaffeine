dnl macro CCAFE_PURESINGLE
dnl --------------------------------------------------------------------
dnl PURESINGLE defined as yes or ""
dnl Turn on ccafe-single or not? Mostly useful in debugging.
dnl --------------------------------------------------------------------
dnl Side effects:
dnl defines variable (but not acsubst) PURESINGLE
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_PURESINGLE],
[

AC_ARG_ENABLE(single, [  --enable-single           Should ccafe-single be mpi-free
                                 in an mpi environment?],
              [enable_single=$enableval], [enable_single=no])
PURESINGLE=
if test ! "X$enable_single" = "Xno"; then
  enable_single=yes
fi
if test "X$enable_single" = "Xyes"; then
  PURESINGLE=yes
fi

]
)


dnl macro CCAFE_MAKEDEBUG
dnl ------------------------------------------------------------------------------
dnl  MAKEDEBUG - defines HAVE_NOISE as noise or ""
dnl  turn on MAKEDEBUG or not? Useful in debugging our makefiles.
dnl ------------------------------------------------------------------------------
AC_DEFUN([CCAFE_MAKEDEBUG],
[
AC_ARG_ENABLE(makedebug, [  --enable-makedebug           Should make-related
                                 debugging info be printed/filed?],
              [enable_makedebug=$enableval], [enable_makedebug=no])
HAVE_NOISE=
if test ! "X$enable_makedebug" = "Xno"; then
  enable_makedebug=noise
fi
if test "X$enable_makedebug" = "Xyes"; then
  HAVE_NOISE=noise
fi

]
)

dnl macro CCAFE_HIDELIBTOOL
dnl ------------------------------------------------------------------------------
dnl  HIDELIBTOOL defined as @ or ""
dnl  show libtool in make or not? Useful in debugging our makefiles.
dnl ------------------------------------------------------------------------------
AC_DEFUN([CCAFE_HIDELIBTOOL],
[
AC_ARG_ENABLE(showlibtool, [  --enable-showlibtool    Should libtool invocations
                                 be printed?],
              [enable_showlibtool=$enableval], [enable_showlibtool=no])
HIDELIBTOOL=@
if test ! "X$enable_showlibtool" = "Xno"; then
  enable_showlibtool=yes
fi
if test "X$enable_showlibtool" = "Xyes"; then
  HIDELIBTOOL=
fi

]
)

dnl macro CCAFE_HIDECOMPILE
dnl ------------------------------------------------------------------------------
dnl  HIDECOMPILE defined as --quiet or ""
dnl  show libtool generated compiler invocations or not? 
dnl  Useful in debugging our makefiles.
dnl ------------------------------------------------------------------------------
AC_DEFUN([CCAFE_HIDECOMPILE],
[
AC_ARG_ENABLE(showcompile, [  --enable-showcompile    Should compiler invocations
                                 be printed?],
              [enable_showcompile=$enableval], [enable_showcompile=no])
HIDECOMPILE=--quiet
if test ! "X$enable_showcompile" = "Xno"; then
  enable_showcompile=yes
fi
if test "X$enable_showcompile" = "Xyes"; then
  HIDECOMPILE=
fi

]
)

