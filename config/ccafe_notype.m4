dnl macro CCAFE_CHECK_NOTYPE(file)
dnl --------------------------------------------------------------------
dnl See if we can find NoType in a babel cca spec header file given.
dnl defines variable (but not acsubst) CCAFE_NOTYPE
dnl with the result.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_CHECK_NOTYPE],
[
# grep check for notype.
AC_EGREP_CPP([NoType], [#include "$1"] , CCAFE_NOTYPE=1, CCAFE_NOTYPE=0)
# grep check for notype finised

]
)

