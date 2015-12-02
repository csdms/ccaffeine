dnl macro CCAFE_CCAFE_CONFIG
dnl --------------------------------------------------------------------
dnl See if we can find a ccafe-config.
dnl
dnl Side effects:
dnl defines variable (but not acsubst) CCAFE_CONFIG
dnl as that given or the one found (in path or environment) or 
dnl empty if neither found nor given.
dnl If predefined, CCAFE_CONFIG is checked for validity and
dnl if found to be bogus an error is issued.
dnl --------------------------------------------------------------------
AC_DEFUN(CCAFE_CCAFE_CONFIG,
[
	
AC_ARG_WITH(ccafe-config,
	[  
  --with-ccafe-config=/path/to/ccafe-config       full path to ccafe-config executable], , [with_ccafe_config=try_path])

dnl if not given and env var set, check the env value before searching.
if ! test "x$CCAFE_CONFIG" = "x"; then
	if test "x$with_ccafe_config" = "xtry_path"; then
		if test -d $CCAFE_CONFIG ; then
			AC_MSG_ERROR([CCAFE_CONFIG must contain the path of the script, not a directory.])
		fi
		if ! test -f $CCAFE_CONFIG ; then
			AC_MSG_ERROR([$CCAFE_CONFIG executable not found, use --with-ccafe-config or CCAFE_CONFIG to specify the full path location.])
		fi
		if ! test -x $CCAFE_CONFIG ; then
			AC_MSG_ERROR([CCAFE_CONFIG=$CCAFE_CONFIG: $CCAFE_CONFIG not executable.])
		fi
		with_ccafe_config=$CCAFE_CONFIG
	fi
fi
		

if test "x$with_ccafe_config" = "xtry_path" ; then
	AC_PATH_PROG(pathccafeconfig, ccafe-config, no-ccafe-config, $PATH:/usr/local/CCAtk/bin:/usr/local/cca/bin )
	if test "x$pathccafeconfig" = "xno-ccafe-config"; then
		AC_MSG_RESULT([ccafe-config not in path or given.])
	else
		with_ccafe_config=$pathccafeconfig
	fi
fi

if test "x$with_ccafe_config" = "xtry_path" ; then
	AC_MSG_RESULT([ccafe-config not in path, environment, or given.])
	CCAFE_CONFIG=""
else

	if test -d $with_ccafe_config ; then
		AC_MSG_ERROR([--with-ccafe-config must be given the path of the script, not a directory.])
	fi
	if ! test -x $with_ccafe_config ; then
		AC_MSG_ERROR([--with-ccafe-config=$with_ccafe_config: $with_ccafe_config not executable.])
	fi
	if ! test -f $with_ccafe_config ; then
		AC_MSG_ERROR([$with_ccafe_config executable not found, use --with-ccafe-config to specify the full path location.])
	fi

	CCAFE_CONFIG="$with_ccafe_config"
fi
]
)

dnl macro CCAFE_CCAFE_CONFIG_REQUIRED
dnl --------------------------------------------------------------------
dnl See if we can find a ccafe-config and error if not.
dnl
dnl Side effects: As CCAFE_CCAFE_CONFIG.
dnl --------------------------------------------------------------------
AC_DEFUN(CCAFE_CCAFE_CONFIG_REQUIRED,
[
CCAFE_CCAFE_CONFIG
if test "x$CCAFE_CONFIG" = "x" ; then
	AC_MSG_ERROR([ccafe-config could not be found in path nor CCAFE_CONFIG in environment, nor --with-ccafe-config in argument list. ])
fi

]
)
