dnl Simple example for configuring a package
dnl that uses ccaffeine to find the rest of the basic
dnl cca environment
dnl
dnl Written by Benjamin Allan, Sandia Laboratories, 12/2004

AC_INIT(classic-static, 0.1.0, ccafe-help@cca-forum.org)
AC_PREREQ(2.53)

#    information on the package
AC_CONFIG_SRCDIR(StaticCmdLineClientMain.cxx)
CCAFE_CONFIG_ARGS(CONFIG_ARGS)
AC_SUBST(CONFIG_ARGS)

#    checks for programs 
CCAFE_CCAFE_CONFIG_REQUIRED

CCAFE_MAKEINCL=`$CCAFE_CONFIG --var CCAFE_MAKEINCL`
AC_SUBST(CCAFE_MAKEINCL)

#    checks for libraries
#    checks for header files
#    checks for types
#    checks for structures
#    checks for compiler characteristics
#    checks for library functions
#    checks for system services

AC_CONFIG_FILES([Makefile reconfigure])
AC_CONFIG_COMMANDS([reconfigure],[chmod a+x reconfigure])
AC_OUTPUT

