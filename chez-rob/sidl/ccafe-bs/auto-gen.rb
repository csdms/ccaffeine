#!/usr/bin/ruby -w

def reShow(a, re)
  q = a.gsub(re) { |t|
    m = Regexp.last_match
    puts "m0 = #{m[0]}; m1 = #{m[1]}; m2 = #{m[2]}"
    m[0]
  }
  q
end

def showRE(a, re)
  if a =~ re
    "#{$`}<<#{$&}>>#{$'}"
  else
    "no match"
  end
end


class AutoGen
  def initialize(typeArray, file)
    @types = typeArray
    @tTable =  Hash[*@types.flatten]
    @file = file
  end

  # An array of [Regexp, String] pairs where Regexp is the thing being
  # replaced and String is the substitution.

  def AutoGen.substTypeInText(substArray, text)
    substArray.each{ |re, str|
      text.gsub!(re, str)
    }
    text
  end
  
  def doXFills()
    #Parse the template file.

    # Start of region to match

    ms = Regexp.new(/regExpStart = '(.*)'\s/).match(templ)
    if ! ms || ! ms[0] ||! ms[1]
      $stderr.puts ":-( Template file format error: no detectable "+
                   "regExp = expression"
      return nil
    end
    reStart = Regexp.new(ms[1])
    #remove the regexp string from the template
    templ.slice!(0..ms.end(0))

    # Now check for sanity and check to see if it is in the table, if
    # so, do the fill if not continue.

    # end of region to match
    me = Regexp.new(/regExpEnd = '(.*)'\s/).match(templ)
    if ! me || ! me[0] ||! me[1]
      $stderr.puts ":-( Template file format error: no detectable "+
                   "regExp = expression"
      return nil
    end
    reEnd = Regexp.new(me[1])
    #remove the regexp string from the template
    templ.slice!(0..me.end(0))



  end

  def doAllFills(templ)

# Start of region to match

    ms = Regexp.new(/regExpStart = '(.*)'\s/).match(templ)
    if ! ms || ! ms[0] ||! ms[1]
      $stderr.puts ":-( Template file format error: no detectable "+
                   "regExp = expression"
      return nil
    end
    reStart = Regexp.new(ms[1])
    #remove the regexp string from the template
    templ.slice!(0..ms.end(0))

    @file.gsub(reStart) { |mStr|
      m = Regexp.last_match
      doOneFill(m, templ)
    }
    @file
  end

  def doOneFill(match, templ)

    m = match
    key = m[1]
    if ! (type = @tTable[key])
      puts ":-( bad match found in doFill"
      exit(-1)
    end
    if type != m[2]
      # fails sanity check
      puts ":-( sanity check fails in doFill"
      exit(-1)
    end
    str = substTempl([["%name%", key], ["%type%", type]], templ)
    # advance to the end.
    insertStart = @file.index("// insert implementation here", m.end(0))
# Find out why this goes to the end of the file
    insertEnd = @file.index(/\n/, insertStart)
#    puts "insertEnd = "+insertEnd.to_s+" insertStart = "+insertStart.to_s
#    puts "str to be inserted over"
#    puts @file[insertStart..insertEnd]
#    puts "-----------------------"
    @file[insertStart..insertEnd] = str
    @file
  end

  def substTempl(tokenList, templ)
    s = templ
    tokenList.each {|tok|
      replc = tok[0]
      replcmt = tok[1]
      re = Regexp.new(Regexp.escape(replc))
      s = s.gsub(re, replcmt)
    }
    s
  end
end

if $0 == __FILE__
  types = [  # [CCAName, C++Type]
    ["None","Invalid"],
    ["Bool", "bool"],
    ["Int","int"],
    ["Long","long"],
    ["Float","float"],
    ["Double","double"],
    ["Fcomplex","std::complex<float>"],
    ["Dcomplex","std::complex<double>"],
    ["String","std::string"],
    ["IntArray","SIDL::array<int>"],
    ["LongArray","SIDL::array<long>"],
    ["FloatArray","SIDL::array<float>"],
    ["DoubleArray","SIDL::array<double>"],
    ["FcomplexArray","SIDL::array<SIDL::fcomplex>"],
    ["DcomplexArray","SIDL::array<SIDL::dcomplex>"],
    ["StringArray","SIDL::array<std::string>"],
    ["BoolArray","SIDL::array<bool>"]
  ]

  reStr = 'void\sccaffeine::CcafeTypeMap_impl::put(.*) \(\s.*std::string key,\s  \/\*in\*\/ (.*) value'
  re = Regexp.new(reStr)
  fromTempl = open('put.tmpl').read
  
  fileToFill = $stdin.read

  a = AutoGen.new(types, fileToFill)

  puts "---------------------------------------"
  puts a.doAllFills(fromTempl)
  puts "---------------------------------------"

end
