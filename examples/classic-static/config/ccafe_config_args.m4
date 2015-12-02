
dnl CCAFE_CONFIG_ARGS(VAR)
dnl --------------------------------------------------------------------
dnl capture the ./configure arguments in VAR.
dnl --------------------------------------------------------------------
AC_DEFUN(CCAFE_CONFIG_ARGS,
[
  if test -z "$1" ; then
    AC_MSG_ERROR([Ccafe_config_args macro requires a variable name.])
  fi
  $1=[$]*
]
)

