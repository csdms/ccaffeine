#!/usr/bin/ruby -w

class Splicer


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
# the given character position.  Yields two variables: the splicer
# name and the current text in the splicer field.  Returns the total
# number of splices encountered.

  def replace_each(pos = 0)
    @rangePtr = pos
    count = 0
    while(true) do
      rng, splicerName = findNextRange()
      puts "rangePtr = "+@rangePtr.to_s if @debug
      if ! rng
	break
      end
      str = yield splicerName, @file[rng]
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


# need to have a map option for mapping splices from one file to
# another.  This could be all splices or splices based on a regexp.

# need to have an insert option that inserts named splices from one
# file to another

end
