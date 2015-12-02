dnl #####################################################
dnl big pile of cruft for mpich, if explicitly enabled.
dnl #####################################################
AC_DEFUN([MPICH_CRUFT],
[

dnl ################## mpich specific crap; gone unless explicitly enabled.
dnl a not bad heuristic for meta-configure scripts would be to check if
dnl running linux before giving --enable-mpich to our options.

    if test "$with_mpi" = _searching ; then
        ccafe_have_mpi=no
        AC_MSG_CHECKING([for mpich])
        for mhome in $ccafe_mpich_dirs ; do
        echo "checking for mpi in $mhome ..."
            if test -x $mhome/bin/mpirun; then
                MPI=$mhome
                MPIRUN=$MPI/bin/mpirun
                MPI_ARCH=`$mhome/bin/tarch`
                AC_MSG_RESULT([$mhome ($MPI_ARCH) found.])
                ccafe_have_mpi=yes
                break
            fi
        done
        if test -z "$MPI" ; then
            ccafe_have_mpi=no
            AC_MSG_RESULT([mpi not found. mpi-based interfaces disabled.
               --with-mpi=/path/of/mpi to enable them.
               See configure --help for additional mpi options management.])
        fi
    fi
    
    # we think we have something. check that it runs
    # and if not, sigh and go to folklore.
    if test ! "X$ccafe_have_mpi" = Xno ; then
        if test -x $MPI/bin/mpirun ; then
            MPIRUN=$MPI/bin/mpirun
        else
            MPIRUN=broken
            AC_MSG_WARN([mpirun executable not found. Specify using --with-mpi-run.])
        fi
        if test -x $MPI/bin/tarch ; then
            MPI_ARCH=`$MPI/bin/tarch`
        else
            MPI_ARCH="Set_MPI_ARCH_in_Makefile.Vars_manually"
            AC_MSG_WARN([tarch executable not found. Specify using --with-mpi-arch.])
        fi
        if test -x $MPI/bin/mpicc ; then
            AC_MSG_CHECKING([mpicc])
            $MPI/bin/mpicc $CFLAGS -o config.cpi.exe $srcdir/config/cpi.c
            if test -x config.cpi.exe ; then
                AC_MSG_RESULT(yes)
                MPICC=$MPI/bin/mpicc
            else
                MPICC=broken
                BROKEN_MPICC=$MPI/bin/mpicc
                AC_MSG_RESULT(broken.)
                AC_MSG_WARN([mpicc found appears broken. Override using --with-mpi-cc=path.])
            fi
            rm -f config.cpi.exe cpi.o
        fi
        if test -x $MPI/bin/mpiCC ; then
            AC_MSG_CHECKING([mpiCC])
            $MPI/bin/mpiCC $CXXFLAGS -o config.cppi.exe $srcdir/config/cpi.cpp
            if test -x config.cppi.exe ; then
                AC_MSG_RESULT(yes)
                MPICXX=$MPI/bin/mpiCC
            else
                MPICXX=broken
                BROKEN_MPICXX=$MPI/bin/mpiCC
                AC_MSG_RESULT(broken.)
                AC_MSG_WARN([mpiCC found appears broken. Override using --with-mpi-cxx=path.])
            fi
            rm -f config.cppi.exe cpi.o
        fi
        MPI_HOME=$MPI
        if test -d $MPI/include ; then
            MPI_INC=-I$MPI/include
        fi
        if test -d $MPI/bin ; then
            MPI_BIN=$MPI/bin
            if test -x $MPI/bin/mpif77 ; then
                MPIF77=$MPI/bin/mpif77
            fi
            if test -x $MPI/bin/mpif90 ; then
                MPIF90=$MPI/bin/mpif90
            fi
        fi
    fi
    # hack around mpich 1.2.4 pmpich library bug
    if test -s "$MPI/lib/libmpich.a" ; then
        MPI_LIBDIR="$MPI/lib"
        MPILIB="$MPI/lib/libmpich.a"
            if test -s "$MPI_LIBDIR/libpmpich.a" ; then
                    MPILIB="$MPILIB $MPI_LIBDIR/libpmpich.a"
                    MPILIB="$MPILIB $MPILIB"
            fi
    fi
    # guess out the darned .so for rob
    if test -s "$MPI_LIBDIR/libmpi.so"; then
        MPI_SO_LIBDIR="$MPI_SO_LIBDIR"
        MPILD_SO_FLAGS="$MPI_LIBDIR/libmpi.so";
    fi
    if test -s "$MPI_LIBDIR/libmpich.so"; then
        MPI_SO_LIBDIR="$MPI_SO_LIBDIR"
        MPILD_SO_FLAGS="$MPI_LIBDIR/libmpich.so";
    fi
    if test -s "$MPI_LIBDIR/shared/libmpi.so"; then
        MPI_SO_LIBDIR="$MPI_SO_LIBDIR/shared"
        MPILD_SO_FLAGS="$MPI_LIBDIR/shared/libmpi.so";
    fi
    if test -s "$MPI_LIBDIR/shared/libmpich.so"; then
        MPI_SO_LIBDIR="$MPI_SO_LIBDIR/shared"
        MPILD_SO_FLAGS="$MPI_LIBDIR/shared/libmpich.so";
    fi
    if test -s "$MPI_LIBDIR/shared/libmpich.so"; then
        MPI_SO_LIBDIR="$MPI_SO_LIBDIR/shared"
        MPILD_SO_FLAGS="$MPI_LIBDIR/shared/libmpich.so";
    fi
    MPI_STATIC_LIBS=$MPILIB
    MPI_SO_LIBS=$MPILD_SO_FLAGS
    

])
