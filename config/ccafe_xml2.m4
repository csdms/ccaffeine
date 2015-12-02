dnl macro CCAFE_LIBXML2
dnl --------------------------------------------------------------------
dnl See if we can find libxml2.
dnl accepts --with-xml2-config, --with-xml-includes, --with-xml-libs
dnl
dnl Side effects:
dnl defines variables (but not acsubst)
dnl as the values given or the ones commputed from xml2-config.
dnl XMLLIB, XMLINC, HAVE_XML, XML2CONFIG
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_LIBXML2],
[
HAVE_XML=1
AC_ARG_WITH(xml2-config,
    [  --with-xml2-config=XML2-CONFIG  The full path to the xml2-config
     script that come with libxml2, or no.], , [with_xml2_config=yes])
if test "X$with_xml2_config" = Xyes; then
    AC_PATH_PROG(bogoXML2config, xml2-config, NO_XML)
    if test "X$bogoXML2config" = XNO_XML; then
      AC_MSG_WARN([Cannot find xml2-config. xml-dependent functions
    will be disabled. If libxml2 is installed, try adding 
    --with-xml2-config=XML2-CONFIG to your configure options.])
        XML2CONFIG=:
        HAVE_XML=0
    else
        XML2CONFIG=$bogoXML2config
    fi
else
    XML2CONFIG=$with_xml2_config
    if test "X$with_xml2_config" = Xno; then
        XML2CONFIG=:
        HAVE_XML=0
    fi
fi
XMLLIB=
XMLINC="-DHAVE_XML=0"

if test "x$HAVE_XML" = "x1"; then
    XMLLIB=`$XML2CONFIG --libs`
    XMLINC="`$XML2CONFIG --cflags` -DHAVE_XML=1"
fi
AC_ARG_WITH(xml2-includes,
    [  --with-xml2-includes='-I/path/to/libxml2/headers'
      that come with libxml2.], , [with_xml2_includes="no"])
if test "x$with_xml2_includes" = "xno"; then
    :
else
    XMLINC=$with_xml2_includes
fi
AC_ARG_WITH(xml2-libs,
    [  --with-xml2-libs='-L/path/to/libxml2/lib -lxml2 -lz'
     or --with-xml2-libs='/path/to/lib/libxml2.la'
      ], , [with_xml2_libs="no"])
if test "x$with_xml2_libs" = "xno"; then
    :
else
    XMLLIB=$with_xml2_libs
fi
]
)

