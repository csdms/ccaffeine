dnl macro CCAFE_ENABLE_SOCKETS
dnl --------------------------------------------------------------------
dnl CCAFE_SOCKETS defined as 1 or 0.
dnl Enable sockets (client/server) or not?
dnl --------------------------------------------------------------------
dnl Side effects:
dnl defines variable and subst CCAFE_SOCKETS, NO_CCAFE_SOCKETS
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_ENABLE_SOCKETS],
[

AC_ARG_ENABLE(sockets, [  --enable-sockets           Should socket code be used?],
              [enable_sockets=$enableval], [enable_sockets=yes])
CCAFE_SOCKETS=1
NO_CCAFE_SOCKETS=""
if test "X$enable_sockets" = "Xno"; then
  CCAFE_SOCKETS=0
  NO_CCAFE_SOCKETS="// "
fi

AC_SUBST(CCAFE_SOCKETS)
AC_SUBST(NO_CCAFE_SOCKETS)
]
)

