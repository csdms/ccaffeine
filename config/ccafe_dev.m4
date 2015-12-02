dnl macro CCAFEDEVELOPER
dnl --------------------------------------------------------------------
dnl DEVELOPER defined as yes or no
dnl Turn on developer build features or not? 
dnl initially will control dependency generation, not
dnl needed for production mode.
dnl --------------------------------------------------------------------
dnl Side effects:
dnl defines variable (but not acsubst) CCAFE_DEVELOPER.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFEDEVELOPER],
[

AC_ARG_ENABLE(developer, [  --enable-developer           Should make depend
                                 and other developer builds be done?],
              [enable_developer=$enableval], [enable_developer=no])
CCAFE_DEVELOPER=no
if test ! "X$enable_developer" = "Xno"; then
  enable_developer=yes
fi
if test "X$enable_developer" = "Xyes"; then
  CCAFE_DEVELOPER=yes
fi

]
)
AC_DEFUN([CCAFECMDSHELL],
[

AC_ARG_ENABLE(cmdshell, [  --enable-shell           Should command line 
                                 allow shell call to system()?],
              [enable_cmdshell=$enableval], [enable_cmdshell=no])
CCAFE_CMDSHELL=no
if test ! "X$enable_cmdshell" = "Xyes"; then
  enable_cmdshell=no
fi
if test "X$enable_cmdshell" = "Xyes"; then
  CCAFE_CMDSHELL=1
else
  CCAFE_CMDSHELL=0
fi

]
)

