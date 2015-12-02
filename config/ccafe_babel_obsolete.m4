dnl macro CCAFE_BABEL_OBSOLETE,
dnl --------------------------------------------------------------------
dnl Error about a dead with-babel option.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_BABEL_OBSOLETE],
[
AC_ARG_WITH(babel, 
    [Obsolete check: 
  --with-babel=babel_installation (OBSOLETE. Use
            --with-csb-config=prefix_spec/bin/cca-spec-babel-config[-version]
            or --with-cca-babel=prefix_spec or --with-cca-babel=no) ] ,
    , [with_babel=no])

case "$with_babel" in
    no)
        ;;
    *)
	AC_MSG_ERROR(
[--with-babel is OBSOLETE. You must specify 
            --with-csb-config=prefix_spec/bin/cca-spec-babel-config[-version]
            or --with-cca-babel=prefix_spec or --with-cca-babel=no
])
        ;;
esac

]
)

