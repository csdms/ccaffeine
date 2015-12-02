AC_DEFUN([CCAFE_FIND_SHELLS],
[
# ---------------------------------------------------------------------------
# Optional Python installation
# ---------------------------------------------------------------------------
PYTHON_SCRIPTING=0
PYTHON_INCLUDE=""
PYTHON_CPPFLAGS=""
PYTHON_LDFLAGS=""
if test $HAVE_BABEL -eq 1 ; then
if test "$CCASPEC_SUPPORT_PYTHON" = "true"; then
CCAFE_BABEL_PYTHON=$CCASPEC_BABEL_PYTHON
CCAFE_BABEL_PYTHON_VERSION=$CCASPEC_BABEL_PYTHON_VERSION
CCAFE_BABEL_PYTHONINC=$CCASPEC_BABEL_PYTHONINC
CCAFE_BABEL_PYTHONLIB=$CCASPEC_BABEL_PYTHONLIB
CCAFE_BABEL_PYTHON_SHARED_LIBRARY=$CCASPEC_BABEL_PYTHON_SHARED_LIBRARY
PYTHON_SCRIPTING=1
PYTHON_INCLUDE="$CCAFE_BABEL_PYTHONINC"
PYTHON_CPPFLAGS="-I$CCAFE_BABEL_PYTHONINC"
PYTHON_LDFLAGS="-L$CCAFE_BABEL_PYTHONLIB"
fi
fi


AC_ARG_WITH(python-includes,
    [  --with-python-includes=PYTHON_INCLUDE	OBSOLETE: path to Python include files],
    [AC_MSG_WARN([The switch --with-python-includes is obsolete])]
)

AC_ARG_WITH(python-library,
    [  --with-python-library=PYTHON_LIBRARY	OBSOLETE: path to Python library],
    [AC_MSG_WARN([The switch --with-python-includes is obsolete])]
)


#------------------------------------------------------------------------------
#  see if the user gave us the location of clueful make
#------------------------------------------------------------------------------
AC_ARG_WITH(gmake, 
    [Location of gmake:
  --with-gmake=EXECUTABLE
                          The location of gmake.  Give the full path:
                              --with-gmake='/share/bizarre/bin/gmake' ] ,
    , [with_gmake=yes])

case "$with_gmake" in
    no)
        ccafe_have_gmake=no
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_gmake=_searching
        ;;
    *)
        #  Only the library was specified
        GMAKE="$with_gmake"
        ;;
esac

if test "$with_gmake" = _searching ; then
    AC_CHECK_PROG(gmake_1, gmake, gmake, NONE)
    if test ! "$gmake_1" = NONE ; then
        GMAKE="$gmake_1"
    fi
fi


#------------------------------------------------------------------------------
#  see if the user gave us the location of the tclsh
#------------------------------------------------------------------------------
TCLSH=/usr/local/bin/tclsh
AC_ARG_WITH(tclsh, 
    [Location of tclsh:
  --with-tclsh=EXECUTABLE
                          The location of the Tcl8.x or later tclsh.
                          Give the full path:
                              --with-tclsh='/share/bizarre/bin/tclsh' ],
    , [with_tclsh=yes])

case "$with_tclsh" in
    no)
        #  User specified --without-tclsh; this makes no sense,
        #  print a warning and search for it ourselves
        AC_MSG_WARN([Option '--without-tclsh'
        Causes some convenience scripts to be unusable.])
        ccafe_have_tclsh=no
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_tclsh=_searching
        ;;
    *)
        TCLSH="$with_tclsh"
        ccafe_have_tclsh=yes
        ;;
esac

if test "$with_tclsh" = _searching ; then
    AC_CHECK_PROG(tclsh_1, tclsh, tclsh, NONE)
    if test ! "$tclsh_1" = NONE ; then
        TCLSH=`which $tclsh_1`
        ccafe_have_tclsh=yes
    fi
fi

#------------------------------------------------------------------------------
#  see if the user gave us the location of the ruby
#------------------------------------------------------------------------------
RUBY=/usr/bin/ruby
AC_ARG_WITH(ruby, 
    [Location of ruby:
  --with-ruby=EXECUTABLE
                          The location of the ruby-lang binary
                          Give the full path:
                              --with-ruby='/home/rob/bin/ruby' ],
    , [with_ruby=yes])

case "$with_ruby" in
    no)
        #  User specified --without-ruby.
        #  print a warning and search for it ourselves
	if test 0 = 0 ; then
        	RUBY=:
        	AC_MSG_WARN([Option '--without-ruby'
        Causes some convenience scripts to be unusable.])
        	ccafe_have_ruby=no
	fi
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_ruby=_searching
        ;;
    *)
        RUBY="$with_ruby"
        ccafe_have_ruby=yes
        ;;
esac

if test "$with_ruby" = _searching ; then
    AC_CHECK_PROG(ruby_1, ruby, ruby, NONE)
    if test ! "$ruby_1" = NONE ; then
        RUBY=`which $ruby_1`
        ccafe_have_ruby=yes
    else
	if test 0 = 0 ; then
        	AC_MSG_WARN([Unable to locate ruby. Some convenience scripts may be unavailable.])
	fi
    fi
fi

#------------------------------------------------------------------------------
#  see if the user gave us the location of the swig
#------------------------------------------------------------------------------
SWIG=/usr/bin/swig
AC_ARG_WITH(swig, 
    [Location of swig:
  --with-swig=EXECUTABLE
                          The location of the swig executable
                          Give the full path:
                              --with-ruby='/home/rob/bin/swig' ],
    , [with_swig=yes])

case "$with_swig" in
    no)
        #  User specified --without-swig
        #  print a warning and search for it ourselves
        AC_MSG_WARN([Option '--without-swig'
        Causes some convenience scripts and python interfaces to be unusable.])
        ccafe_have_swig=no
        SWIG=""
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_swig=_searching
        ;;
    *)
        SWIG="$with_swig"
        ccafe_have_swig=yes
        ;;
esac

if test "$with_swig" = _searching ; then
    AC_CHECK_PROG(swig_1, swig, swig, NONE)
    if test ! "$swig_1" = NONE ; then
        SWIG=`which $swig_1`
        ccafe_have_swig=yes
    fi
fi
SWIG_HOME="$SWIG"

])

