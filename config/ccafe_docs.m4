dnl macro CCAFE_DOCS
dnl --------------------------------------------------------------------
dnl See if we should build docs.
dnl accepts --disable-doc --enable-doc
dnl
dnl Side effects:
dnl defines variables (but not acsubst)
dnl BUILDDOCS as docs or empty
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_DOCS],
[
BUILDDOCS=doc
AC_ARG_ENABLE(doc,
    [  --disable-doc  Suppress doc generation [default is to have docs]
    ], [doc_ok=$enableval], [doc_ok=yes])

    if test "${enable_doc+set}" = set; then
	enableval="$enable_doc"
	doc_ok=$enableval
    else
	doc_ok=yes
    fi

    if test "$doc_ok" = "yes" ; then
	BUILDDOCS=doc
    else
	BUILDDOCS=""
    fi
]
)

