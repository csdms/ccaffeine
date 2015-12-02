dnl macro CCAFE_CATAMOUNT
dnl --------------------------------------------------------------------
dnl Get a hint from the user about the catamount environment,
dnl which is an exercise in cross compiling and disabling
dnl most of posix.
dnl 
dnl Side effects:
dnl defines variable and acsubst CATAMOUNT_COMMENT CATAMOUNT_ARCH
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_CATAMOUNT],
[
AC_ARG_WITH(catamount,
[
Set some flags in the combination needed for catamount:
    --with-catamount=yes [default no]
    At present implies --disable-threads --disable-sockets
] , [with_catamount="yes"] , [with_catamount="no"])


CATAMOUNT_ARCH="OS_CATAMOUNT"
if test "x$with_catamount" = "xyes"; then
	CATAMOUNT_COMMENT=""
	OS_ARCH=$CATAMOUNT_ARCH
else
	CATAMOUNT_COMMENT="#"
fi

AC_SUBST(CATAMOUNT_ARCH)
AC_SUBST(CATAMOUNT_COMMENT)
]
)
