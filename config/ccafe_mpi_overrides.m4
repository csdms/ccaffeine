dnl bunch of switches to bypass guessing games.
AC_DEFUN([CCAFE_MPI_OVERRIDES],
[
# overrides after all our guessing junk
# aux mpi switches
# --with-mpi-mpd
# --with-mpi-arch=
# --with-mpi-bin=
# --with-mpi-inc=
#
# --with-mpi-cc=
# --with-mpi-cxx=
# --with-mpi-f77=
# --with-mpi-f90=
# --with-mpi-run=
# --with-mpi-prerun=
#--------------------------------------------------------------------
# mpi mpd flag for launchscripts.
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-mpd,
    [
Machine is mpich mpd:
  --with-mpi-mpd
], , [with_mpi_mpd=no])

case "$with_mpi_mpd" in
    no)
        MPI_IS_MPD=0
        AC_MSG_RESULT([checking mpi is mpd ... nope.])
        ;;
    yes)
        MPI_IS_MPD=1
        AC_MSG_RESULT([checking mpi is mpd ... mpi mpd specified.])
        ;;
    *)
        MPI_IS_MPD=0
        AC_MSG_ERROR([Option --with-mpi-mpd=$with_mpi_arch: value is yes/no only.])
        ;;
esac
#--------------------------------------------------------------------
# mpi arch override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-arch,
    [
=== The following options override those guessed based on --with-mpi, if given.
=== Try specifying them if the defaults don't work for your mpi. Likely needed
=== if you are not using mpich.

Machine architecture of mpi:
  --with-mpi-arch=MPI_ARCH
                          The \$ARCH value for mpi.
                              --with-mpi-arch='LINUX' ],
    , [with_mpi_arch=no])

case "$with_mpi_arch" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-arch=yes': yes not a valid arch value.])        ;;
    *)
        MPI_ARCH="$with_mpi_arch"
        ;;
esac

#--------------------------------------------------------------------
# mpi includes override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-inc,
    [Special -I flags to get mpi headers when not using mpicc/mpiCC:
  --with-mpi-inc="MPI_INCLUDES"
                          The flags for mpi includes in c/c++. e,g,
                              --with-mpi-inc='-I/usr/local/include/mpich-ver'
                    Others, like avoiding a broken c++ binding header:
                    '-I\$MPI/include -I\$MPI/build/\$ARCH/\$DEVICE/include'
 ],
    , [with_mpi_inc=no])

case "$with_mpi_inc" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-inc=yes': yes not a valid value.])
        ;;
    *)
        MPI_INC="$with_mpi_inc"
        ;;
esac

#--------------------------------------------------------------------
# mpi bin override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-bin,
    [Location of mpi bin directory:
  --with-mpi-bin=/path/to/bin/mpi*
                          The full path to the bin/ for mpi-related programs.
                              --with-mpi-bin='/usr/local/mpich-ver/bin' ],
    , [with_mpi_bin=no])

case "$with_mpi_bin" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-bin=yes': yes not a valid path value.])
        ;;
    *)
        if test -x "$with_mpi_bin"/mpicc ; then
            MPICC="$with_mpi_bin"/mpicc
        else
            AC_MSG_WARN([Option '--with-mpi-bin: given bin contains no mpicc.])
        fi
        if test -x "$with_mpi_bin"/mpiCC ; then
            MPICXX="$with_mpi_bin"/mpiCC
        else
            AC_MSG_WARN([Option '--with-mpi-bin: given bin contains no mpiCC.])
        fi
        if test -x "$with_mpi_bin"/mpirun ; then
            MPIRUN="$with_mpi_bin"/mpirun
        else
            AC_MSG_WARN([Option '--with-mpi-bin: given bin contains no mpirun.])
        fi
        if test -x "$with_mpi_bin"/mpif77 ; then
            MPIF77="$with_mpi_bin"/mpif77
        else
            AC_MSG_WARN([Option '--with-mpi-bin: given bin contains no mpif77.])
        fi
        if test -x "$with_mpi_bin"/mpif90 ; then
            MPIF90="$with_mpi_bin"/mpif90
        else
            AC_MSG_WARN([Option '--with-mpi-bin: given bin contains no mpif90.])
        fi
        ;;
esac


#--------------------------------------------------------------------
# mpif77 override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-f77,
    [
 == The following mpi switches override defaults computed from --with-mpi
 == or --with-mpi-bin.

Location of special mpif77 to use
  --with-mpi-f77=MPIF77
                        The full path to mpif77, if not in normal mpi bin/ dir.
                            --with-mpi-f77=/usr/local/bin/odd/mpif77 ],
    , [with_mpi_f77=no])

case "$with_mpi_f77" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-f77=yes': yes not a valid compiler.])
        ;;
    *)
        MPIF77="$with_mpi_f77"
        ;;
esac

#--------------------------------------------------------------------
# mpif90 override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-f90,
    [Location of special mpif90 to use
  --with-mpi-f90=MPIF90
                        The full path to mpif90, if not in normal mpi bin/ dir.
                            --with-mpi-f90=/usr/local/bin/odd/mpif90 ],
    , [with_mpi_f90=no])

case "$with_mpi_f90" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-f90=yes': yes not a valid compiler.])
        ;;
    *)
        MPIF90="$with_mpi_f90"
        ;;
esac

#--------------------------------------------------------------------
# mpicxx override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-cxx,
    [Location of special mpiCC to use
  --with-mpi-cxx=MPICXX
                        The full path to mpiCC, if not in normal mpi bin/ dir.
                            --with-mpi-cxx=/usr/local/bin/odd/mpiCC ],
    , [with_mpi_cxx=no])

case "$with_mpi_cxx" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-cxx=yes': yes not a valid compiler.])
        ;;
    *)
        MPICXX="$with_mpi_cxx"
        ;;
esac

#--------------------------------------------------------------------
# mpicc override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-cc,
    [Location of special mpicc to use
  --with-mpi-cc=MPICC
                          The full path to mpicc, if not in normal mpi bin/ dir.                              --with-mpi-cc=/usr/local/bin/odd/mpicc ],
    , [with_mpi_cc=no])

case "$with_mpi_cc" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-cc=yes': yes not a valid compiler.])
        ;;
    *)
        MPICC="$with_mpi_cc"
        ;;
esac
#--------------------------------------------------------------------
# mpirun override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-run,
    [Location of special mpirun/mpiexec to use
  --with-mpi-run=MPIRUN
                          The full path to mpirun if not in normal mpi bin/ dir.                              --with-mpi-run=/usr/local/bin/odd-mpirun
                          Also used to specify mpiexec or other batch launches],    , [with_mpi_run=no])

case "$with_mpi_run" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-run=yes': yes not a valid launcher.])
        ;;
    *)
        MPIRUN="$with_mpi_run"
        ;;
esac

#--------------------------------------------------------------------
# mpiprerun override
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-prerun,
    [Location of special mpirun to use
  --with-mpi-prerun=MPIPRERUN
                          The full path to prep script to launch before mpirun.
                              --with-mpi-prerun=/usr/local/bin/start-parallel
                          Used to specify mpd or other user-daemon launches],
    , [with_mpi_prerun=no])

case "$with_mpi_prerun" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-prerun=yes': yes not a valid launcher.])        ;;
    *)
        MPIPRERUN="$with_mpi_prerun"
        ;;
esac

# no-wrapper flags
# --with-mpi-lib-static=
# --with-mpi-lib-dynamic=
# --with-mpi-ldflags-static=
# --with-mpi-ldflags-dynamic=
# --with-mpi-cflags=
# --with-mpi-fflags=
# --with-mpi-cxxflags=
#--------------------------------------------------------------------
# mpi-lib-static
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-lib-static,
    [
 == The following mpi switches override miscellaneous folklore used
 == when trying to build an mpi program without using the compiler
 == wrappers mpicc/mpiCC. Sometimes wrapper-avoidance is necessary
 == for complicated, multi-language driver linkage or for working
 == around broken compiler wrappers.

Libraries for linking mpi statically
  --with-mpi-lib-static=MPI_STATIC_LIBS
                        The full paths of libraries needed, e.g.
                            --with-mpi-lib-static='/lib/libmpi.a /lib/libpmpi.a'   ],
    , [with_mpi_lib_static=no])

case "$with_mpi_lib_static" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-lib-static=yes': yes not a valid link item.])
        ;;
    *)
        MPI_STATIC_LIBS="$with_mpi_lib_static"
        MPILIB="$with_mpi_lib_static"
        ;;
esac

#--------------------------------------------------------------------
# mpi-lib-dynamic
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-lib-dynamic,
    [Libraries for linking mpi dynamically
  --with-mpi-lib-dynamic=MPI_SO_LIBS
                     The full paths of libraries needed, e.g.
                         --with-mpi-lib-dynamic='/lib/libmpi.so /lib/libpmpi.so'                     or something like
                     '-L/usr/local/mpi/lib/solaris/ch_p4 -lmpi -L/opt/SUNWspro/SC4.2/lib /usr/local/lib/liblapack.a /usr/local/lib/libblas.a -lnsl -lsocket -lM77 -lF77 -lsunmath'
   ],
    , [with_mpi_lib_dynamic=no])

case "$with_mpi_lib_dynamic" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-lib-dynamic=yes': yes not a valid link item.])
        ;;
    *)
        MPI_SO_LIBS="$with_mpi_lib_dynamic"
        ;;
esac

#--------------------------------------------------------------------
# mpi-lib-libtool
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-lib-libtool,
    [Libraries for linking mpi libtoolwise
  --with-mpi-lib-libtool=MPI_LIBTOOL_LIBS
                     The full paths of libraries needed, e.g.
                         --with-mpi-lib-libtool='/lib/libmpi.la /lib/libpmpi.la'                     or something like
                     '-L/usr/local/mpi/lib/solaris/ch_p4 -lmpi'
   ],
    , [with_mpi_lib_libtool=no])

case "$with_mpi_lib_libtool" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-lib-libtool=yes': yes not a valid link item.])
        ;;
    *)
        MPI_LIBTOOL_LIBS="$with_mpi_lib_libtool"
        ;;
esac

#--------------------------------------------------------------------
# mpi-ldflags-dynamic
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-ldflags-dynamic,
    [LD_FLAGS for linking mpi dynamically, other than the libraries
  --with-mpi-ldflags-dynamic=MPI_SO_LDFLAGS
                    The flags to appear in the link line well before libraries.
   ],
    , [with_mpi_ldflags_dynamic=no])

case "$with_mpi_ldflags_dynamic" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-ldflags-dynamic=yes': yes not a valid flag.])
        ;;
    *)
        MPI_SO_LDFLAGS="$with_mpi_ldflags_dynamic"
        ;;
esac

#--------------------------------------------------------------------
# mpi-ldflags-static
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-ldflags-static,
    [LD_FLAGS for linking mpi statically, other than the libraries
  --with-mpi-ldflags-static=MPI_STATIC_LDFLAGS
                   The flags to appear in the link line well before libraries.
   ],
    , [with_mpi_ldflags_static=no])

case "$with_mpi_ldflags_static" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-ldflags-static=yes': yes not a valid flag.])
        ;;
    *)
        MPI_STATIC_LDFLAGS="$with_mpi_ldflags_static"
        ;;
esac

#--------------------------------------------------------------------
# mpi-cflags
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-cflags,
    [Additional CFLAGS for compiling C with mpi.h but no mpicc wrapper.
  --with-mpi-cflags=MPI_CFLAGS
                        ],
    , [with_mpi_cflags=no])

case "$with_mpi_cflags" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-cflags=yes': yes not a valid flag.])
        ;;
    *)
        MPI_CFLAGS="$with_mpi_cflags"
        ;;
esac

#--------------------------------------------------------------------
# mpi-fflags
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-fflags,
    [Additional FFLAGS for compiling FORTRAN without mpif*
  --with-mpi-fflags=MPI_FFLAGS
                        ],
    , [with_mpi_fflags=no])

case "$with_mpi_fflags" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-fflags=yes': yes not a valid flag.])
        ;;
    *)
        MPI_FFLAGS="$with_mpi_fflags"
        ;;
esac
#--------------------------------------------------------------------
# mpi-cxxflags -- this needs to be the last mpi thing so that
# the comment appearing in configure --help is correct.
#--------------------------------------------------------------------
AC_ARG_WITH(mpi-cxxflags,
    [Additional CXXFLAGS for compiling C++ with mpi but no mpiCC wrapper.
  --with-mpi-cxxflags=MPI_CXXFLAGS

=== end of mpi-related switches.
===],
    , [with_mpi_cxxflags=no])

case "$with_mpi_cxxflags" in
    no)
        # so nothing
        ;;
    yes)
        AC_MSG_WARN([Option '--with-mpi-cxxflags=yes': yes not a valid flag.])
        ;;
    *)
        MPI_CXXFLAGS="$with_mpi_cxxflags"
        ;;
esac

])
