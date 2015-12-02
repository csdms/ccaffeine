dnl macro CCAFE_CCA_OBSOLETE,
dnl --------------------------------------------------------------------
dnl Error about a dead with-cca option.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_CCA_OBSOLETE],
[
#------------------------------------------------------------------------------
# CCA_ROOT: deprecated, the value now reverts to CLASSIC_CCA_ROOT
#------------------------------------------------------------------------------
AC_ARG_WITH(cca,
    [Obsolete check:
  --with-cca=SPEC_TREE (OBSOLETE. Use --with-csb-config and/or --with-cca-classic) ] ,
    , [with_cca=no])

case "$with_cca" in
    no)
        ;;
    *)
        AC_MSG_ERROR(
[--with-cca is OBSOLETE. You must specify  --with-cca-classic and/or
  --with-cca-babel.]
                    )
        ;;
esac
]
)

