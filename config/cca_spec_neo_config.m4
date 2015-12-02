dnl NEW 4/1/2003

dnl    NEOCCA_PATH_TO_CONFIG_VER(VARIABLE, BINVAR, PATH, TEST_FILE,
dnl      [ RUN_IF_FOUND], [RUN_IF_NOT_FOUND])
dnl    Test for the presence of file(s) (TEST_FILE) in the given colon
dnl    separated list of directory paths (PATH).  If all the file 
dnl    is found, it sets VARIABLE to the matching PATH element and
dnl    BINVAR to script found.
dnl    The last two arguments are run if a path to the
dnl    files is found or not found respectively.
dnl Side effects:
dnl   If variable NEOCCA_PATH_TO_CONFIG is predefined to contain
dnl   the name of an appropriate executable, then we get
dnl   that as BINVAR and its root as VARIABLE.

AC_DEFUN([NEOCCA_PATH_TO_CONFIG_VER],
[

  
dnl AC_MSG_RESULT([entering cca_path_to_config_ver])
p2cv_var="$1"
p2cv_binvar="$2"
p2cv_path="$3"
p2cv_testFile="$4"
p2cv_config="no"
#p2cv_testFile=bin/cca-spec-neo-config
#p2cv_path="."
p2cv_ok=no

if test "x$NEOCCA_PATH_TO_CONFIG" != "x" ; then
  if test -x $NEOCCA_PATH_TO_CONFIG ; then
    p2cv_config=$NEOCCA_PATH_TO_CONFIG
    p2cv_path=`$NEOCCA_PATH_TO_CONFIG --var NEOCCA_INSTALL_ROOT`
    p2cv_result=$p2cv_path
    $1=$p2cv_result
    $2=$p2cv_config
    p2cv_ok=yes
    if test -n '$5' ; then
      # if found
      $5 
    fi
dnl    AC_MSG_RESULT([found $NEOCCA_PATH_TO_CONFIG])
  else
    AC_MSG_WARN([Ignoring env NEOCCA_PATH_TO_CONFIG pointing to non-executable $NEOCCA_PATH_TO_CONFIG.])
  fi
fi

if test "$p2cv_ok" = "no" ; then

  p2cv_tmpfile=`pwd`/.p2cv_tmpfile

  # for path elements
  # if ! element/testfile exists, res=search
  # for file-* w/ver number, try highest number
  # and work down. ver must end in a digit

  p2cv_result=_searching
  p2cv_paths=`echo $p2cv_path|tr ":" " "`
  for chome in $p2cv_paths ; do
dnl    AC_MSG_RESULT([trying $chome])
    if test -x $chome/$p2cv_testFile ; then
        p2cv_result=$chome
        p2cv_config=$chome/$p2cv_testFile
        $1=$p2cv_result
        $2=$p2cv_config
        if test -n '$5' ; then
            # if found
              $5 
        fi
dnl        AC_MSG_RESULT([found basenamed file])
        break
    fi  

    if test -d $chome ; then
        pushd $chome > /dev/null
        flist="${p2cv_testFile}-*[0-9]"
        popd > /dev/null
        /bin/rm -f $p2cv_tmpfile
        for fname in $flist ; do
          echo $fname >> $p2cv_tmpfile
        done
        flist=`cat $p2cv_tmpfile | sort -n -r`
        /bin/rm -f $p2cv_tmpfile
        for fname in $flist ; do
            if test -x $chome/$fname ; then
                p2cv_result=$chome
                p2cv_config=$chome/$fname
                $1=$p2cv_result
                $2=$p2cv_config
                if test -n '$5' ; then
                    # if found
                  $5 
                fi
dnl                AC_MSG_RESULT([       found: $p2cv_result/$fname])
                break;
            fi
        done
    fi
  done
  # not found anywhere
  if test "$p2cv_result" = _searching ; then
dnl    AC_MSG_RESULT([        nothing found])
    p2cv_result=no
    if test -n '$6' ; then
      #if not found
        $6
    fi
  fi
  # end of search for config with ver.

dnl end of p2cv_ok no test
fi
dnl AC_MSG_RESULT([leaving cca_path_to_config_ver])
]
)

dnl CCA_SPEC_NEO_CONFIG(DISTROOT, PATH, TESTFILE, NOTFOUNDWARNING, CONFIGBIN)
dnl input
dnl DISTROOT- input: the variable to set with the result
dnl PATH- the directories to check for cca-spec-neo by finding cca-spec-neo-config
dnl TESTFILE- the script file we require to exist.
dnl output/sideeffects
dnl DISTROOT becomes defined as  no, or a directory
dnl CONFIGBIN becomes defined as no, or the name of the cca-spec-neo-config-$ver
dnl
dnl See if the user gave us the location of cca-spec-neo
dnl We have to do this one first, because it tells us where boost is.
dnl
dnl This macro does discovery and is reusable. 
dnl policy matters such as paths checked
dnl and fatal or not are specific to the configure that includes this macro.
dnl
dnl eg CCA_SPEC_NEO_CONFIG(NEOCCA_ROOT, testpaths, bin/cca-spec-neo-config, msg, CCAFE_CCA_SPEC_NEO_CONFIG)
AC_DEFUN([CCA_SPEC_NEO_CONFIG],
[
CCA_NEO_TEST=""
CCA_NEO=""
AC_ARG_WITH(cca-neo,
    [
Location of cca-spec-neo:
  --with-cca-neo=SPEC_TREE
            The location of neoclassic CCA specification.
              Give the full path:
                  --with-cca-neo='/where/is/cca-spec-neo/installed'
              The install prefix of cca-spec-neo will be the same
              as the build location unless it was configured with --prefix.
              Remember that for cca-spec-neo you must do make;make install.
              or
              give --with-cca-neo=no ] ,
    , [with_cca_neo=yes])

case "$with_cca_neo" in
    no)
        CCA_NEO="no"
        AC_MSG_WARN([Neoclassic CCA spec option disabled. 
   Use --with-cca-neo=/where/is/cca-spec-neo/installed if wanted.])
        ;;
    yes)
        #  User didn't give the option or didn't give useful
        #  information, search for it ourselves
        with_cca_neo="yes"
        CCA_NEO="yes"
  AC_MSG_CHECKING([cca-spec-neo])
        ;;
    *)
        CCA_NEO="$with_cca_neo"
  AC_MSG_CHECKING([cca-spec-neo])
        ;;
esac

dnl    cCA_PATH_TO_CONFIG_VER(VARIABLE, BINVAR, PATH, TEST_FILE, [ RUN_IF_FOUND], [RUN_IF_NOT_FOUND])
dnl cCA_SPEC_NEO_CONFIG(DISTROOT, PATH, TESTFILE, NOTFOUNDWARNING, CONFIGBIN)

CCA_NEO_TEST="$CCA_NEO"
CCA_NEO_CONFIG_TEST="no"
if test "$CCA_NEO" != "no"; then
        CCA_NEO_TEST=""
        NEOCCA_PATH_TO_CONFIG_VER(CCA_NEO_TEST, CCA_NEO_CONFIG_TEST, $with_cca_neo:$2, $3,
                CCA_NEO="$CCA_NEO_TEST" 
                CCA_NEO_CONFIG="$CCA_NEO_CONFIG_TEST" ,
                CCA_NEO_TEST="no"
                CCA_NEO="no"
                CCA_NEO_CONFIG_TEST=no
                CCA_NEO_CONFIG=no
                [AC_MSG_WARN([$4])]
        )
fi

$1="$CCA_NEO"
$5="$CCA_NEO_CONFIG"
dnl AC_MSG_RESULT([root $CCA_NEO , config $CCA_NEO_CONFIG])


]
)

AC_DEFUN([CCA_NEO_CONFIG_FORCE],
[
AC_ARG_WITH(neo-config,
[
Location of cca-spec-neo-config program:
  --with-neo-config=/usr/local/bin/cca-spec-neo-config[-version_numbers]
            Specify the particular neoclassic CCA specification config 
            info script.
            This is not normally needed unless multiple versions 
            of cca-spec-neo are installed in the same location.
            This option overrides environment variable NEOCCA_PATH_TO_CONFIG.
] , , [with_neo_config=no])

case "$with_neo_config" in
    no)
        ;;
    yes)
        with_neo_config="no"
        AC_MSG_ERROR([--with-neo-config must be given the path of the script.])
        ;;
    *)
        if test -d $with_neo_config ; then
          AC_MSG_ERROR([--with-neo-config must be given the path of the script, not a directory.])
        fi
        if ! test -x $with_neo_config ; then
          AC_MSG_ERROR([--with-neo-config=$with_neo_config: $with_neo_config not executable])
        fi
        NEOCCA_PATH_TO_CONFIG=$with_neo_config
        ;;
esac

]
)

