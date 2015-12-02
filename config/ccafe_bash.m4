dnl macro CCAFE_BASH_SHELL
dnl --------------------------------------------------------------------
dnl See if we can find a bash shell (we want an sh w/popd).
dnl accepts --with-bash if given, or does path search for
dnl bash, bash2.
dnl
dnl Side effects:
dnl defines variable (but not acsubst) CCAFE_BASH
dnl as the bash given or the one found.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_BASH_SHELL],
[
AC_ARG_WITH(bash,
     [Bash shell w/pushd:
    --with-bash=/opt/gnu/bash (where is a bash shell?)
  ] ,
    , [with_bash=search_bash])

ccafe_bash_locs=/usr/local/bin:/usr/gnu/bin:/opt/bin
ccafe_test_bash=search_bash
case "$with_bash" in
    search_bash)
        AC_PATH_PROG(ccafe_test_bash, bash, search_bash, $PATH:$ccafe_bash_locs)
        if test "$ccafe_test_bash" = "search_bash"; then
          AC_PATH_PROG(ccafe_test_bash, bash3, search_bash, $PATH:$ccafe_bash_locs)
        fi
        if test "$ccafe_test_bash" = "search_bash"; then
          AC_PATH_PROG(ccafe_test_bash, bash2, search_bash, $PATH:$ccafe_bash_locs)
        fi
        ;;
    *)
        ccafe_test_bash=$with_bash
        ;;
esac   
if ! test "x$BASH" = "x"; then
	if test "$ccafe_test_bash" = "search_bash"; then
		ccafe_test_bash=$BASH
	fi
fi

if test -x $ccafe_test_bash; then
    CCAFE_BASH=$ccafe_test_bash
else
  with_bash=no
  CCAFE_BASH=""
fi
]
)

