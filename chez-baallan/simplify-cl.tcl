#!/usr/bin/tclsh
# This file simplifies the log file from the gui.
# - Creates and drops all components, stripping graphic layout stuff.
# - Preserves order of connect, parameter go commands
# Bugs:
# Clueless about remove/remove-all commands.
if {$argc != 2} {
	puts stderr "$argv0 needs input file name"
	exit 1
}


########################################################################
# the first set of functions map logged gui commands to their tcl simplifier calls 1:1.
########################################################################

# Accumulate the global screen size throwing out all but last.
# Note it doesn't matter which is x and which y, so long as we
# preserve order of the arguments in our later output
proc setSize {x y} {
  global simpler
  set simpler(sizeX) $x
  set simpler(sizeY) $y
}

proc commandCount {args} {
}

proc setDropLocation {x y} {
	global simpler
	set simpler(nextDropX) $x
	set simpler(nextDropY) $y
}

proc move {c x y} {
	global locations
	set locations($c) "$x $y"
}

# just log the lines in a sequence we can repeat exactly later
proc setMaximum {args} {
}

proc connect {args} {
	global simpler literals
	set literals($simpler(nliterals)) "connect $args"
	incr simpler(nliterals)
}
proc parameters {args} {
	global simpler literals
	set literals($simpler(nliterals)) "parameters $args"
	incr simpler(nliterals)
}
proc go {args} {
        global simpler literals
        set literals($simpler(nliterals)) "go $args"
        incr simpler(nliterals)
}

# add to the arena
proc pulldown {type c} {
	global ctypes simpler locations
	set ctypes($c) $type
	set locations($c) "x"
}
	
proc eof {} {
	# make components 
	Simp_GenComponents
	# make connections and set parameters
	Simp_GenLiterals
	exit 0
}

########################################################################
# the second set of functions generates the simplified output
########################################################################

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

proc Simp_GenComponents {} {
	global locations ctypes
	foreach c [array names locations] {
		if {$c != "-"} {
			puts stdout "create $ctypes($c) $c"
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
