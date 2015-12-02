#!/usr/bin/tclsh
if {$argc != 2} {
	puts stderr "$argv0 needs input file name"
	exit 1
}


####################################
# the first set of functions map logged gui commands to 
# their tcl simplifier calls 1:1.
####################################

proc commandCount {args} {}

# accumulate the global screen size
# throwing out all but last spec
# note it doesn't matter
proc setSize {x y} {
  global simpler
  set simpler(sizeX) $x
  set simpler(sizeY) $y
}


proc setDropLocation {x y} {
  global simpler
  set simpler(nextDropX) $x
  set simpler(nextDropY) $y
}

proc go {args} {
	global simpler literals
	set literals($simpler(nliterals)) "go $args"
	incr simpler(nliterals)
}

proc move {c x y} {
	global locations
	set locations($c) "$x $y"
}
# just log the lines in a sequence we can repeat exactly later
proc setMaximum {args} {
	global simpler literals
	set literals($simpler(nliterals)) "setMaximum $args"
	incr simpler(nliterals)
}
proc connect {args} {
	global simpler literals
	set literals($simpler(nliterals)) "connect $args"
	incr simpler(nliterals)
}
proc disconnect {args} {
	global simpler literals
	set literals($simpler(nliterals)) "disconnect $args"
	incr simpler(nliterals)
}
proc parameters {args} {
	global simpler literals
	set literals($simpler(nliterals)) "parameters $args"
	incr simpler(nliterals)
}
proc pulldown {type c} {
	global ctypes simpler locations
	set ctypes($c) $type
	set locations($c) "$simpler(nextDropX) $simpler(nextDropY)"
}
	
proc create {type c} {
	global ctypes simpler locations
	set ctypes($c) $type
	set locations($c) "$simpler(nextDropX) $simpler(nextDropY)"
}
	
proc eof {} {
	# set geometry
	Simp_GenWindow
	# put components in final locations
	Simp_GenComponents
	# make dis/connections and set parameters
	Simp_GenLiterals
	# make finished marker
	Simp_GenEOF
	exit 0
}

####################################
# the second set of functions generates the simplified output
####################################

proc Simp_Init {} {
	global locations simpler ctypes literals
	# nextDropX,Y are the results of colins global drop variable
	set simpler(nextDropX) 0
	set simpler(nextDropY) 0
	# locations is the array of final locations indexed by instance name
	set locations(-) 0
	# types is the array of types indexed by instance name
	set ctypes(-) 0
	set simpler(nliterals) 0
	set literals(-) 0
}

proc Simp_GenEOF {} {
  puts stdout eof
}

proc Simp_GenWindow {} {
  global simpler
  puts stdout "setSize $simpler(sizeX) $simpler(sizeY)"
}

proc Simp_GenComponents {} {
	global locations ctypes
	foreach c [array names locations] {
		if {$c != "-"} {
			puts stdout "setDropLocation $locations($c)"
			puts stdout "pulldown $ctypes($c) $c"
		}
	}
}

proc Simp_GenLiterals {} {
	global simpler literals;
	for {set i 0} {$i < $simpler(nliterals)} {incr i} {
		puts stdout $literals($i)
	}
}

####################################
# main
####################################

Simp_Init
source [lindex $argv 1]
