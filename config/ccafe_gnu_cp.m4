dnl macro CCAFE_CP_PARENTS
dnl --------------------------------------------------------------------
dnl See if we can find a gnu cp --parents cp or had one given
dnl
dnl Side effects:
dnl defines variable (but not acsubst)
dnl CCAFE_GNU_CP
dnl as the cp given or the one found if the one found works.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_CP_PARENTS],
[
AC_ARG_WITH(gnu_cp,
     [GNU cp:
    --with-cp=/path/of/gnu/bin/cp (cp that supports the --parents option)
 ] ,
    , [with_gnu_cp=search_cp])

ccafe_test_cp=search_cp
case "$with_gnu_cp" in
    search_cp)
        if test -x /usr/local/bin/cp; then
	  ccafe_test_cp=/usr/local/bin/cp
	fi
	if test -x /bin/cp; then
	  ccafe_test_cp=/bin/cp
	fi
        ;;
    *)
        ccafe_test_cp=$with_gnu_cp
        ;;
esac   

AC_MSG_CHECKING([for gnu cp --parents])
if test -x $ccafe_test_cp; then
  cd config;
  rm -rf gnu_cp_test_dir_1 gnu_cp_test_dir_2
  mkdir gnu_cp_test_dir_1
  touch gnu_cp_test_dir_1/fred
  mkdir gnu_cp_test_dir_2
  $ccafe_test_cp --parents gnu_cp_test_dir_1/fred gnu_cp_test_dir_2/
  if test -e gnu_cp_test_dir_2/gnu_cp_test_dir_1/fred ; then
    CCAFE_GNU_CP=$ccafe_test_cp
  else
    with_gnu_cp=no
    CCAFE_GNU_CP=""
  fi
  rm -rf gnu_cp_test_dir_1 gnu_cp_test_dir_2
  cd ..
else
  with_gnu_cp=no
  CCAFE_GNU_CP=""
fi
if test "x$CCAFE_GNU_CP" = "x" ; then
  AC_MSG_RESULT(no)
else
  AC_MSG_RESULT(yes)
fi
]
)

