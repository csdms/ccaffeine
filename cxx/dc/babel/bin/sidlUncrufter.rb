#!/usr/bin/ruby -w

require 'getoptlong'
require 'ftools'

@debug = nil

if $0 == __FILE__
  def doMake(file, regexp)
    puts "processing #{file} ..." if @debug
    File.mv(file, file+"~")
    inFile = open(file+"~", "r")
    outFile = open(file, "w")
    regx = []
    regexp.each do |re|
      s = re.source
      s = '\S*'+s+'\S*'
      puts "regexp = "+s if @debug
      regx << Regexp.new(s)
    end
    inFile.each do |line|
      regx.each { |rx|
	line.gsub!(rx) { |sx|
	  puts "deleting #{sx} from line \"#{line}\"" if @debug
	  puts "because of regexp = #{rx.source}" if @debug
	  ""
	}
      }
      outFile.puts(line);
    end
  end

  @re = []
  opt = GetoptLong.new(
		       ['--re-to-delete', '-x', GetoptLong::REQUIRED_ARGUMENT],
		       ['--help', '-h', GetoptLong::NO_ARGUMENT],
		       ['--debug', '-d', GetoptLong::NO_ARGUMENT]
		       )
  opt.each do |key, val|
    case key
    when '--re-to-delete'
      @re << Regexp.new(val)
    when '--help'
      puts "
      #{$0} [--re-to-delete] [--help]
        --re-to-delete - remove sidl gen\'d file matching this re
        --debug - print out helpful, if confusing, debug info
        --help - this message
"
      exit
    when '--debug'
      @debug = 1
    end
  end
  @re.each { |rx|
    Dir::foreach(".") { |f|
      if f == ".." || f == "."
	next
      end
      if /babel.make$/ =~ f
	@babelFile = f
	next
      end
      if rx =~ f
	File.delete(f)
      end
    }
  }
  if ! @babelFile
    $stderr.puts ":-( no make.babel found, you may be running this in the wrong place!"
    exit(-1)
  end
  doMake(@babelFile, @re)
end
