#!/usr/bin/ruby -w

require 'splicer'

class TypeMapGen

  def initialize(typeArray, file)
    @types = typeArray
    @tTable =  Hash[*@types.flatten]
    @file = file
    @splcr = Splicer.new(file)
  end

  def substTempl(name, tmpl)
    s = tmpl
    l = [["%name%", name], ["%type%", @tTable[name]]]
    l.each { |tok|
      replc = tok[0]
      replcmt = tok[1]
      re = Regexp.new(Regexp.escape(replc))
      s = s.gsub(re, replcmt)
    }
    s
  end

  def getTemplFromFile(templFile)
    templ = File.new(templFile).read
    ms = Regexp.new(/prefix = '(.*)'\s+/).match(templ)
    if ! ms || ! ms[0] ||! ms[1]
      $stderr.puts ":-( Template file format error: no detectable "+
	"prefix = expression"
      return nil
    end
    prefix = ms[1]
    #remove the regexp string from the template
    endx = templ.index(/\n/, ms.begin(0)) #end of line
    start = templ.rindex(/\n/, ms.begin(0))
    if ! start 
      start = -1
    end
    start = start + 1
    templ.slice!(start..endx) # range deletes inclusively
    [prefix, templ]
  end

  def doSubstForName(templ,name)
    prefix = templ[0]
    tmpl = templ[1]
    t = substTempl(name, tmpl)
    splicerId = prefix+name
    if ! @splcr.replace(splicerId, t)
      return nil
    end
    true
  end

  def doSubst(templArray)
    templArray.each { |template|
      templ = getTemplFromFile(template)
      @tTable.each_key { |k|
	doSubstForName(templ, k)
      }
    }
  end

  def getFileAsString
    @splcr.getBufferAsString
  end

end


if $0 == __FILE__

  require 'getoptlong'

  opt = GetoptLong.new(
		       ['--overwrite', '-o', GetoptLong::REQUIRED_ARGUMENT],
		       ['--help', '-?', GetoptLong::NO_ARGUMENT] )
  @usage = $0 + ' [--help] [--overwrite <file to patch in place>]'
  @file = nil
  opt.each do |name, arg|
    case name
    when '--help'
      puts @usage
      exit(0)
    when '--overwrite'
      if ! arg
	puts @usage
	exit(-1)
      end
      @file = arg
    end
  end


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

  if @file
    require 'bkupFile'
    f = File.new(@file, 'r')
    gen = TypeMapGen.new(types, f)
    f.close
    gen.doSubst(["get.tmpl", "put.tmpl"])
    BkupFile.createBkup(@file)
    f = File.new(@file, 'w')
    f.puts gen.getFileAsString
  else
    gen = TypeMapGen.new(types, $stdin)
    gen.doSubst(["get.tmpl", "put.tmpl"])
    puts gen.getFileAsString
  end
end



