dnl #####################################################
dnl test of an mpi c++ compiler by name.
dnl if works, sets MPICXX to a value, else leaves alone.
dnl arg 1 is name of compiler to test.
dnl #####################################################
AC_DEFUN([CCAFE_CHECK_MPI_CXX],
[
            AC_MSG_CHECKING([$1 for mpi support])
            AC_LANG_PUSH(C++)
#####
# the following little gem brought to you by the fact that
# some idiot in older versions of autoconf is just broken wrt c++.
# (specifically, things like size_t are redefined unwisely)
# We exclude the confdefs.h for our next test. ugh.
#		AdnlC_TRY_COMPILE([#include "mpi.h"],[
# #ifndef MPI_SUCCESS
# #error "mpi c++ compile fails header check"
# #endif
# ], MPICXX=$CXX)
cat >conftest.$ac_ext <<_ACEOF
#include "mpi.h"
int
main ()
{
                                                                                
#ifndef MPI_SUCCESS
#error "mpi c++ compile fails header check"
#endif
                                                                                
  ;
  return 0;
}
_ACEOF
            my_compile='$1 -c $CXXFLAGS $CPPFLAGS -o conftest.$ac_objext conftest.$ac_ext >&5'
#            cp conftest.$ac_ext bct.$ac_ext
            rm -f conftest.$ac_objext
            (eval echo "$as_me:$LINENO: \"$my_compile\"") >&5
            (eval $my_compile) 2>&5
            if test -s conftest.$ac_objext ; then
                MPICXX=$1
                AC_MSG_RESULT([yes.])
            else
                AC_MSG_RESULT([no.])
            fi

            AC_LANG_POP(C++)
###### end little gem.

]
)

dnl #####################################################
dnl test of an mpi cc compiler by name.
dnl if works, sets MPICC to a value, else leaves alone.
dnl arg 1 is name of compiler to test.
dnl #####################################################
AC_DEFUN([CCAFE_CHECK_MPI_CC],
[

            AC_MSG_CHECKING([$1 for mpi support])
            AC_LANG_PUSH(C)
#####
# the following little gem brought to you by symmetry w/the c++ test above.
cat >conftest.$ac_ext <<_ACEOF
#include "mpi.h"
int
main ()
{
                                                                                
#ifndef MPI_SUCCESS
#error "mpi c compile fails header check"
#endif
                                                                                
  ;
  return 0;
}
_ACEOF
            my_compile='$1 -c $CFLAGS $CPPFLAGS -o conftest.$ac_objext conftest.$ac_ext >&5'
            # cp conftest.$ac_ext bct.$ac_ext
            rm -f conftest.$ac_objext
            (eval echo "$as_me:$LINENO: \"$my_compile\"") >&5
            (eval $my_compile) 2>&5
            if test -s conftest.$ac_objext ; then
                MPICC=$1
                AC_MSG_RESULT([yes.])
            else
                AC_MSG_RESULT([no.])
            fi

            AC_LANG_POP(C)
###### end little gem.

]
)

dnl #####################################################
dnl big pile of cruft for mpi. This differs from the neo specification
dnl version in that babel may be available in ccaffeine
dnl while this is not assumed in neo.
dnl if --enable-mpich, use mpich cruft
dnl if not, try babel compilers if defined,
dnl if not, try $MPI/bin/compiler wrappers if found.
dnl if not found, try plain $CC, $CXX compilers.
dnl #####################################################
AC_DEFUN([CCAFE_CHECK_MPI],
[
if test "x$MPICXX" = "x" ; then
	MPICXX=_none
fi
if test "x$MPICC" = "x" ; then
	MPICC=_none
fi
# c++ compiler wrappers
ccafe_mpicxx_bins="
    mpCC
    mpic++
    mpicxx
    mpiCC
"
# c compiler wrappers
ccafe_mpicc_bins="
    mpcc
    mpicc
"
# places to look
ccafe_mpich_dirs="
    $MPI_HOME
    $CCAFE_PARENT/mpi
    $CCAFE_ANCESTOR/mpi
    $CCAFE_PARENT/mpich
    $CCAFE_ANCESTOR/mpich
    $prefix/cca
    $prefix/mpich
    $prefix/mpi
    $HOME/mpich
    /usr/local/mpich
    /usr/local/mpi
"
AC_ARG_WITH(mpi,
    [Location of mpi:
  --with-mpi=MPI_HOME
                          The location of mpi 1.2 compatible mpi.
                          The dir given contains bin/* where * is some
                          mpi compiler or compiler wrapper.
                          Give the full path:
                              --with-mpi='/share/bizarre/mpi' ],
    , [with_mpi=yes])

AC_ARG_ENABLE(mpich, [  --enable-mpich           Try mpich specific configure hacks? ],
              [enable_mpich=$enableval], [enable_mpich=no])
if test ! "X$enable_mpich" = "Xno"; then
  enable_mpich=yes
fi

case "$with_mpi" in
    no)
        ccafe_have_mpi=no
        ;;
    yes)
        with_mpi=_searching
        ;;
    *)
        MPI="$with_mpi"
        ;;
esac

dnl ################## mpich specific crap; gone unless explicitly enabled.
if test "X$enable_mpich" = "Xyes"; then
    MPICH_CRUFT
fi
# end ######### mpich specific crap

# The next should catch aix, open-mpi, and mpich on a good day,
# but may require runtime library path flags added later.

if test "X$enable_mpich" = "Xno"; then
    if test "$with_mpi" = "_searching" ; then
dnl case with CXX set

        if ! test "x$CXX" = "x"; then
            CCAFE_CHECK_MPI_CXX($CXX)
		:
	fi
dnl case with MPICXX set or fail from above: check paths
        if test "X$MPICXX" = "X_none" ;  then
            AC_PATH_PROGS(MPICXX, $ccafe_mpicxx_bins , _none)
            if ! test "X$MPICXX" = "X_none" ;  then
                CCAFE_CHECK_MPI_CXX($MPICXX)
		:
            fi
        fi
        if test "X$MPICXX" = "X_none" ;  then
            AC_MSG_ERROR([Cannot find an MPI-capable c++ compiler, though mpi requested.
    Try adding --with-mpi=no if MPI not needed.])
	fi

        if ! test "x$CC" = "x"; then
            CCAFE_CHECK_MPI_CC($CC)
		:
	fi
        if test "X$MPICC" = "X_none" ;  then
            AC_PATH_PROGS(MPICC, $ccafe_mpicc_bins , _none)
            if ! test "X$MPICC" = "X_none" ;  then
                CCAFE_CHECK_MPI_CC($MPICC)
		:
            fi
        fi
        if test "X$MPICC" = "X_none" ;  then
            AC_MSG_ERROR([Cannot find an MPI-capable C compiler, though mpi requested.
    Try adding --with-mpi=no if MPI not needed.])
		:
	fi
    else
dnl case where --with-mpi given: should be rationalized with mpicxx macro above
dnl sometime.
	if ! test "x$with_mpi" = "xno"; then
            for i in $ccafe_mpicxx_bins ; do
                if test -x $MPI/bin/$i ; then
                    AC_MSG_CHECKING([$i])
                    $MPI/bin/$i $CXXFLAGS $CPPFLAGS -o config.cppi.exe $srcdir/config/cpi.cpp
                    if test -x config.cppi.exe ; then
                        AC_MSG_RESULT(yes)
                        MPICXX=$MPI/bin/$i
        	        MPI_HOME=$MPI
                        rm -f config.cppi.exe cpi.o
		        break;
                    fi
                fi
            done
        fi
    fi
    rm -f config.cppi.exe cpi.o
fi

# now try to fish up an mpi launcher
# start from MPICC and look for mpirun, mpiexec
mpirun_options="mpiexec mpirun"
if ! test "x$MPICC" = "x_none"; then
	mdir=`dirname $MPICC`
	if test "x$MPIRUN" = "x" ; then
		AC_PATH_PROGS(MPIRUN,  $mpirun_options, _none, $mdir:$PATH:$MPI/bin:$MPI_HOME)
	fi
	if test "x$MPIRUN" = "x_none" ; then
		AC_MSG_ERROR([Found MPI compilers but not mpirun or mpiexec. Please specify
          --with-mpi-run=/path/to/launch/script for mpi.
If working on a system with poe, slurm, or yod, specify
          --with-mpi-run=MPIRUN_FIXME
and then after installing, fix the installed shell scripts which 
contain MPIRUN_FIXME to use your launcher syntax.])
	fi
fi
		
CCAFE_MPI_OVERRIDES 

if test "${ccafe_have_mpi}" = "no"; then
    USEMPI=0
    MPI_TARGET=""
    AC_MSG_WARN([Configured without MPI. Hope that is what you meant.
  See configure --help for other mpi switches if it is not what you meant.])
else
    AC_MSG_RESULT([Configured with MPI. 'grep MPI neo/src/varlist' for details.])
    USEMPI=1
    MPI_TARGET=mpi
fi

AC_SUBST(USEMPI)
AC_SUBST(MPI_TARGET)
AC_SUBST(MPI)
AC_SUBST(MPI_IS_MPD)
AC_SUBST(MPIRUN)
AC_SUBST(MPIPRERUN)
AC_SUBST(MPIF77)
AC_SUBST(MPIF90)
AC_SUBST(MPICC)
AC_SUBST(MPICXX)
AC_SUBST(MPI_ARCH)
AC_SUBST(MPI_HOME)
AC_SUBST(MPI_INC)
AC_SUBST(MPI_BIN)
AC_SUBST(MPI_STATIC_LIBS)
AC_SUBST(MPI_STATIC_LDFLAGS)
AC_SUBST(MPI_LIBTOOL_LIBS)
AC_SUBST(MPI_SO_LIBS)
AC_SUBST(MPI_SO_LDFLAGS)
AC_SUBST(MPI_CFLAGS)
AC_SUBST(MPI_FFLAGS)
AC_SUBST(MPI_CXXFLAGS)

]
)

