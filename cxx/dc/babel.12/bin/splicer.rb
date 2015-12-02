#!/usr/bin/ruby  -w -I /home/rob/cca/dccafe/chez-rob/sidl/bin

class Splicer

  attr_accessor :debug

# Create a new Splicer and intialize the buffer with the contents of
# the given file which can be either a string file name or an object
# of type File.

  def initialize(file)
    @debug = nil
    if file.kind_of? String
      @file = File.new(file).read
      return
    end
    if file.kind_of? IO
      @file = file.read
      return
    end
    puts ":-( Splicer needs a String file name or an IO stream to read"
    +" in order to initialize.   Splicer is *not* initialized/"
  end

  def lineNumber(positionInFile) 
    line = 1
    while(@file.index("\n") <= positionInFile) 
      line += 1
    end
  end


# Find the range of characters in the buffer that correspond to the
# splice identified by splicerName, returns nil if no such slice
# exists.

  def findRange(splicerName)
    s = 'splicer.begin('+splicerName+')'
    reS = Regexp.new('//.*'+Regexp.escape(s)+"\n")
    s = 'splicer.end('+splicerName+')'
    reE = Regexp.new('//.*'+Regexp.escape(s)+"\n")
    beg = @file.index(reS)
    return nil if ! beg
    start = @file.index(/\n/, beg) + 1
    return nil if ! start 
    beg = @file.index(reE)
    return nil if ! beg
    endx = @file.rindex(/\n/, beg)
    return nil if ! endx
    start..endx
  end


  def findNextRange()
    s = Regexp.escape('splicer.begin(')+'\s*(\S+)\s*'+Regexp.escape(')')
    reS = Regexp.new('//.*'+s+"\n")
    s = Regexp.escape('splicer.end(')+'\s*(\S+)\s*'+Regexp.escape(')')
    reE = Regexp.new('//.*'+s+"\n")
    beg = @file.index(reS, @rangePtr)
    m1 = Regexp.last_match
    return [nil,nil] if ! beg
    start = @file.index(/\n/, beg) + 1
    puts "start = "+start.to_s if @debug
    return [nil,nil] if ! start 
    beg = @file.index(reE, start)
    m2 = Regexp.last_match
    return [nil,nil] if ! beg
    endx = @file.rindex(/\n/, beg)
    puts "endx = "+endx.to_s if @debug
    return [nil,nil] if ! endx
    # advance the ptr to after this splice
    @rangePtr = @file.index(/\n/, beg)
    puts "ptr = "+@rangePtr.to_s if @debug
    if m1[1] != m2[1]
      puts ":-( found unmatched splicer statements"
      puts "first = "+m1[1]+" second = "+m2[1]
      return [nil,nil]
    end
    [start..endx, m1[1]]
  end


# Replace the splice identified by splicerName with the given string.
# Returns true if the operation succeeded, nil otherwise.  The old
# string will be overwritten.

  def replace(splicerName, newString)
    r = findRange(splicerName)
    return nil if ! r
    @file[r] = newString
    true
  end


# Iterates through each splice detected in the buffer starting from
# the given position.  Yields two strings: the splicer name and the
# current text in the splicer field.  The return value by each iterate
# is ignored.  Returns the total number of splices found.

  def each(pos = 0)
    puts "Splicer::each entry, pos = "+pos.to_s if @debug
    @rangePtr = pos
    count = 0
    while(true) do
      rng, splicerName = findNextRange()
      puts "rangePtr = "+@rangePtr.to_s if @debug
      if ! rng
	break
      end

      # Stash rangePtr for safe keeping, I wish there was a way to
      # alter args in ruby
      savPtr = @rangePtr.clone();

      yield splicerName, @file[rng]

      @rangePtr = savPtr
      count = count + 1
    end
    return count
  end

# Iterates through each splice detected in the buffer starting from
# the given character position.  Yields two strings: the splicer
# name and the current text in the splicer field.  The value returned
# by each iterate replaces the field.  Returns the total number of
# splices encountered.

  def replace_each(pos = 0)
    @rangePtr = pos
    count = 0
    while(true) do
      rng, splicerName = findNextRange()
      puts "rangePtr = "+@rangePtr.to_s if @debug
      if ! rng
	break
      end

      # Stash rangePtr for safe keeping, I wish there was a way to
      # alter args in ruby
      savPtr = @rangePtr.clone();

      str = yield splicerName, @file[rng]

      @rangePtr = savPtr
      if str
	@file[rng] = str
      end
      count = count + 1
    end
    return count
  end



# Return the buffer in this Splicer as a string.

  def getBufferAsString
    return @file
  end


# Retrieve the splice identified by the name splicerName, or returns
# nil if no such splice exists.

  def get(splicerName)
    r = findRange(splicerName)
    return nil if ! r
    @file[r]
  end
end


if $0 == __FILE__

require 'getoptlong'

opt = GetoptLong.new(
		     ['--help', '-h', GetoptLong::NO_ARGUMENT],
		     ['--map', '-m', GetoptLong::NO_ARGUMENT],
		     ['--to', '-t', GetoptLong::REQUIRED_ARGUMENT],
		     ['--from', '-f', GetoptLong::REQUIRED_ARGUMENT],
		     ['--topat', '-s', GetoptLong::REQUIRED_ARGUMENT],
		     ['--frompat', '-p', GetoptLong::REQUIRED_ARGUMENT],
		     ['--debug', '-d', GetoptLong::NO_ARGUMENT],
		     ['--extract', '-x', GetoptLong::NO_ARGUMENT]
		     )

  @usage = "
#{$0} --map --frompat <pattern> [--from <srcFile>] [--topat <pattern>] [--to <destFile>]
#{$0} --extract [--frompat <pattern>] [--from <srcFile>]
 
       --help          - this message
       --debug         - print out lots of debugging info.

=========================================================================

       --extract       - indicates an extract operation to extract specific 
                         splice from the input and print it on stdout.
       --frompat       - splices are only taken from the source that match
                          this regular expression in the splice name.

========================================================================

       --map           - Indicates a map operation to transfer splices 
                         from one file to another according to optional 
                         patterns.
       --from          - source file, default is stdin.
       --to            - output file, default is stdout.
       --frompat       - splices are only taken from the source that match
                         this regular expression in the splice name.
       --topat         - splices are only substituted in the output if the
                         output splice name matches the substitution of 
                         --topat arg for --frompat match.

=========================================================================
For example:

$0 --map --frompat \"decaf.\"  --from decaf_TypeMap_Impl.cc  \
         --topat \"ccaffeine.\" --to ccaffeine_TypeMap_Impl.cc

This lifts all of the implementation splices in the babel generated
TypeMap implementation for decaf and neatly stuffs it into the
ccaffeine implementation.

The splice resident in the decaf_TypeMap_Impl.cc file:

  // DO-NOT-DELETE splicer.begin(decaf.TypeMap.getInt)
  return getType( d_key2int, key, cca::Int, dflt );
  // DO-NOT-DELETE splicer.end(decaf.TypeMap.getInt)

gets mapped into the following splice in the ccaffeine_TypeMap_Impl.cc
file:

  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMap.clone_)
  return getType( d_key2int, key, cca::Int, dflt );
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMap.clone_)

A backup file of the old data is created in a file named
ccaffeine_TypeMap_Impl.cc~.

If --to <destFile> argument is neglected, the --topat argument is
substituted into the splice names and just the matches from the
inputfile are printed on stdout.  This is useful to corroborate what
actually happens to what is intended.  If --topat is neglected then
the original splice names are printed out.

"
  def usage()
    puts @usage
    exit(-1)
  end

map_operation = nil
extract_operation = nil
fromFile = nil
toFile = nil
toPat = nil
fromPat = nil
debug = nil

  opt.each_option { |name,arg|
    case name
    when '--help'
      puts @usage
      exit(0)
    when '--debug'
      debug = true
    when '--map'
      map_operation = true
    when '--from'
      fromFile = arg
    when '--to'
      toFile = arg
    when '--topat'
      toPat = arg
    when '--frompat'
      fromPat = arg
    when '--extract'
      extract_operation = true
    end
  }
  if extract_operation 
    puts "extracting ..." if debug
    usage if map_operation || toFile || toPat
    fromPat = '.*' if ! fromPat
  end

  if map_operation || extract_operation
    fromSp = nil
    if ! fromFile
      fromSp = Splicer.new($stdin)
    else
      fromSp = Splicer.new(fromFile)
    end

    toSp = nil
    if toFile
      puts "to --> "+toFile if debug
      toSp = Splicer.new(toFile)
    end
    
    fromRe = nil
    if fromPat
      fromRe = Regexp.new(fromPat)
    end

    subStr = toPat
    fromSp.debug = true if debug
    toSp.debug = true if toSp && debug

    fromSp.each { |name,text|
      puts "processing input splice name: "+name if debug
      puts "fromRe = "+fromRe.to_s if debug
      puts "subStr = "+subStr.to_s if debug
      if fromRe 
	if fromRe =~ name
	  if subStr
	    sname = name.sub(fromRe, subStr)
	  else 
	    sname = name
	  end
	  if toSp
	    toSp.replace(sname, text) # replace the splice in the toFile
	  else
	    $stdout.puts "// DO-NOT-DELETE splicer.begin("+sname+")"
	    $stdout.puts text
	    $stdout.puts "// DO-NOT-DELETE splicer.end("+sname+")"
	  end
	else # no match to this splice name
	  next
	end
      end
    }
    if toSp
      if ! require 'bkupFile'
	$stderr.puts ":-( could not fine library bkupFile.rb"
	exit(-1)
      end
      BkupFile.createBkup(toFile)
      f = File.new(toFile,'w')
      f.puts toSp.getBufferAsString
      f.close
    end
    
  end # if @map_operation
end
