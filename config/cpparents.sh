# make a directory path and all missing intermediate
# directories ala x11 mkdirhier
mkdirhier() {
	prog=mkdirhier
	save_ifs="$IFS"
	if test $# -ne 1; then
		echo "$prog: usage: $prog dirpath" 1>&2
		return 1 ; # exit?
	fi
	olddir=`pwd`
	fullpath=1
	xpath=`echo $1 | sed -e 's%^/%%g'`
	if test "x$xpath" = "x$1"; then
		fullpath=0
	fi
	# if fullpath, start at /,
	# otherwise, start in pwd
	if test $fullpath -eq 1; then
		cd /
	fi
	IFS="/"
	for idir in $1 ; do
		if ! test "x$idir" = "x" ; then
			if test -d $idir; then
				cd $idir
			else
				if test -w . ; then
					mkdir $idir
					cd $idir
				else
					echo "$prog: `pwd` not writable" 1>&2
					IFS=$save_ifs
					cd $olddir
					return 1
				fi
			fi
		fi
	done
	IFS=$save_ifs

	cd $olddir
	return 0
}

#
# this is an emulator of gnu cp --parents <srcs> target
# it does not support -r or other switches.
# syntax:
#    Form the name of each destination file by appending to the target
#     directory a slash and the specified name of the source file.  The
#     last argument given to `cp' must be the name of an existing
#     directory.  For example, the command:
#
#          cp --parents a/b/c existing_dir
#
#     copies the file `a/b/c' to `existing_dir/a/b/c', creating any
#     missing intermediate directories.
#
cpparents() {
	prog=cpparents
	if test $# -lt 2; then
		echo "$prog: need source and destination." 1>&2
		return 1 ; # exit?
	fi
	for i in /dev/null $* ; do
		target=$i
	done
	if ! test -d $target ; then
		echo "$prog: destination is not a directory." 1>&2
		return 1 ; # exit?
	fi
	if ! test -w $target ; then
		echo "$prog: destination directory is not writable." 1>&2
		return 2; # exit?
	fi
	ncp=1
	ncpmax=$#
	for i in $* ; do
		if test $ncp -eq $ncpmax ; then
			break;
		fi
		ncp=`expr $ncp + 1`;
		if ! test -e $i; then
			echo "$prog: nonexistent input $i" 1>&2
			continue;
		fi
		if test -d $i; then
			echo "$prog: ignoring input that is directory $i" 1>&2
			continue;
		fi
		src=$i;
		tfile=`echo $src |sed -e 's%.*/%%g'`
		tdir=`echo $target/$src |sed -e 's%[^/]*$%%g'`
		mkdirhier $tdir
		cp $src $tdir
	done
}
