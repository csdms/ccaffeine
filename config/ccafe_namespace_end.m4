dnl --------------------------------------------------------------------
dnl See if we must end a namespace with }; or just }
dnl
dnl Requires:
dnl   CXX needs to be determined first.
dnl
dnl Side effects:
dnl defines variable (but not acsubst)
dnl NAMESPACE_NEEDS_ENDSEMI 
dnl as the empty string or as ";" if test succeeds.
dnl attempts to bomb if namespaces are unsupported at all.
dnl --------------------------------------------------------------------
AC_DEFUN([CCAFE_NAMESPACE_END],
[
AC_LANG_PUSH(C++)

NAMESPACE_NEEDS_ENDSEMI="broken"
NAMESPACE_TEST_DONE="no"

AC_MSG_CHECKING([C++ for namespaces closed with ;])

# create test code
cat > conftest.$ac_ext <<EOF
namespace cca {
  class NSTest {
  public:
    NSTest() {}
    ~NSTest() {}
  private:
    int y;
  };
}
#ifdef NAMESPACE_NEEDS_ENDSEMI
;
#endif // NAMESPACE_NEEDS_ENDSEMI

class NoNSTest {
  public:
    NoNSTest() {}
    ~NoNSTest() {}
  private:
    int y;
};

int main() {
  ::cca::NSTest foo1;
  NoNSTest foo2;
  return 0;
}
EOF
# end test code

# try compiling both ways
$CXX $CXXFLAGS -DNAMESPACE_NEEDS_ENDSEMI -o config.nsWithSemi.exe conftest.$ac_ext
$CXX $CXXFLAGS -o config.nsWithoutSemi.exe conftest.$ac_ext

if test -x config.nsWithoutSemi.exe ; then
    AC_MSG_RESULT(yes)
    NAMESPACE_NEEDS_ENDSEMI=""
    NAMESPACE_TEST_DONE="yes"
fi
# if test "$NAMESPACE_NEEDS_ENDSEMI" = broken -a -x config.nsWithSemi.exe ; then
# if compiler allows it, use it.
if test "$NAMESPACE_TEST_DONE" = "no" ;  then
  if test -x config.nsWithSemi.exe ; then
    AC_MSG_RESULT(yes)
    NAMESPACE_NEEDS_ENDSEMI=";"
  fi
fi
if test "NAMESPACE_NEEDS_ENDSEMI" = broken ; then
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([C++ compiler {$CXX}cannot compile namespaces. Bye!.])
fi
rm -f config.nsWithoutSemi.exe config.nsWithSemi.exe conftest.$ac_ext

AC_LANG_POP(C++)

]
)

