#!/usr/bin/ruby

# usage: $0 <source directory> <destination directory>

# Synchronize given files over given directories
require 'getoptlong'


if $0 == __FILE__

  usage = "
#{$0} <source directory> <destination directory>

 Check to see if _Impl files in the source directory are modified
 later than _Impl files in the destination directory, if so, print
 them on stdout.

"

  opt = GetoptLong.new(
		       ['--file', '-f', GetoptLong::REQUIRED_ARGUMENT],
		       ['--help', '-?', GetoptLong::NO_ARGUMENT] )

  opt.each_option { |name,arg|
    case name
    when '--file'
      @files << arg
    when '--help'
      puts usage
      exit(0)
    end
  }


  if ARGV.size != 2
    puts usage
    exit(-1)
  end

  dirSrc = ARGV[0]
  dirDest = ARGV[1]

  newer = []
  Dir[dirSrc+"/*_Impl*"].each { |sf|
    # ignore bkup and object files.
    if (/~\d*$/ =~ sf) || (/\.o$/ =~ sf)
      next
    end
    dest = dirDest+"/"+File.basename(sf)
    if ! File.exists?(dest)
      # if it doesn't exist it is definitely newer.
      newer << sf
      next
    end
    d = File.stat(dest) 
    s = File.stat(sf);
    ts = s.mtime;
    td = d.mtime;
    if ts > td
      newer << sf
    end
  }
  newer.each {|f| puts f}
end
