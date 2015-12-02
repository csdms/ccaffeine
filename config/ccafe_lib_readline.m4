AC_DEFUN([CCAFE_LIB_READLINE], [
  LIBREADLINE_LIBS=""
  NO_HAVE_LIBREADLINE="//"
  NO_HAVE_READLINE_READLINE_H="//"
  NO_HAVE_READLINE_H="//"
  NO_HAVE_READLINE_HISTORY="//"
  NO_HAVE_HISTORY_H="//"
  NO_HAVE_READLINE_HISTORY_H="//"

  HAVE_LIBREADLINE=0
  HAVE_READLINE_READLINE_H=0
  HAVE_READLINE_H=0
  HAVE_READLINE_HISTORY=0
  HAVE_HISTORY_H=0
  HAVE_READLINE_HISTORY_H=0
  AC_ARG_WITH(readline,
      [Probing for GNU readline:
  --without-readline will disable probing for GNU readline.],,
      [with_readline=yes]) dnl default is to enable GNU readline

  if test "$with_readline" != "no"; then
    AC_LANG_PUSH(C)
  
    AC_CACHE_CHECK([for a readline compatible library],
                   ccafe_cv_lib_readline, [
      ORIG_LIBS="$LIBS"
      for readline_lib in readline edit editline; do
        for termcap_lib in "" termcap curses ncurses; do
          if test -z "$termcap_lib"; then
            TRY_LIB="-l$readline_lib"
          else
            TRY_LIB="-l$readline_lib -l$termcap_lib"
          fi
          LIBS="$ORIG_LIBS $TRY_LIB"
          AC_TRY_LINK_FUNC(readline, ccafe_cv_lib_readline="$TRY_LIB")
          if test -n "$ccafe_cv_lib_readline"; then
            break
          fi
        done
        if test -n "$ccafe_cv_lib_readline"; then
          break
        fi
      done
      if test -z "$ccafe_cv_lib_readline"; then
        ccafe_cv_lib_readline="no"
      fi
      LIBS="$ORIG_LIBS"
    ])

    if test "$ccafe_cv_lib_readline" != "no"; then
      HAVE_LIBREADLINE=1
      LIBREADLINE_LIBS="$ccafe_cv_lib_readline"
      ORIG_LIBS="$LIBS"
      LIBS="$LIBS $ccafe_cv_lib_readline"
dnl      AC_LANG_C already set
      AC_TRY_COMPILE([#include <stdio.h>
#include <readline.h>],
         [char *c = readline("prompt:");],
        [HAVE_READLINE_H=1],
        [AC_TRY_COMPILE([#include <stdio.h>
#include <readline/readline.h>],
           [char *c = readline("prompt:");],
           [HAVE_READLINE_READLINE_H=1],)])
      AC_CACHE_CHECK([whether readline supports history],
                     ccafe_cv_lib_readline_history, [
        ccafe_cv_lib_readline_history="no"
        AC_TRY_LINK_FUNC(add_history, ccafe_cv_lib_readline_history="yes")
      ])
      if test "$ccafe_cv_lib_readline_history" = "yes"; then
        HAVE_READLINE_HISTORY=1
        AC_TRY_COMPILE([#include <stdio.h>
#include <history.h>],
          [add_history("prompt:");],
          [HAVE_HISTORY_H=1],
          [AC_TRY_COMPILE([#include <stdio.h>
#include <readline/history.h>],
             [add_history("prompt:");],
             [HAVE_READLINE_HISTORY_H=1],)])
      fi
      LIBS="$ORIG_LIBS"
    fi
    AC_LANG_POP(C)
  fi
# turn on the #defines we need for config.hh
  if test "x$HAVE_LIBREADLINE" = "x1" ; then
    NO_HAVE_LIBREADLINE=""
    if test "x$HAVE_READLINE_READLINE_H" = "x1" ; then
      NO_HAVE_READLINE_READLINE_H=""
    else
      if test "x$HAVE_READLINE_H" = "x1"; then
        NO_HAVE_READLINE_H=""
      fi
    fi
    if test "x$HAVE_READLINE_HISTORY" = "x1" ; then
      NO_HAVE_READLINE_HISTORY=""
      if test "x$HAVE_READLINE_HISTORY_H" = "x1" ; then
        NO_HAVE_READLINE_HISTORY_H=""
      else
        if test "x$HAVE_HISTORY_H" = "x1" ; then
          NO_HAVE_HISTORY_H=""
        fi
      fi
    fi
  fi

  AC_SUBST(LIBREADLINE_LIBS)
  AC_SUBST(HAVE_LIBREADLINE)
  AC_SUBST(HAVE_READLINE_READLINE_H)
  AC_SUBST(HAVE_READLINE_H)
  AC_SUBST(HAVE_READLINE_HISTORY)
  AC_SUBST(HAVE_HISTORY_H)
  AC_SUBST(HAVE_READLINE_HISTORY_H)

  AC_SUBST(NO_HAVE_LIBREADLINE)
  AC_SUBST(NO_HAVE_READLINE_READLINE_H)
  AC_SUBST(NO_HAVE_READLINE_H)
  AC_SUBST(NO_HAVE_READLINE_HISTORY)
  AC_SUBST(NO_HAVE_HISTORY_H)
  AC_SUBST(NO_HAVE_READLINE_HISTORY_H)
])dnl
