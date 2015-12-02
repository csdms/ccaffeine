require 'ftools'


class BkupFile

  def BkupFile.createBkup(path)
    bpath = findNonExistentName(path)
    if(! File.syscopy(path, bpath))
      return nil;
    end
    true
  end

  def BkupFile.findNonExistentName(path)
    return path if ! File.exists?(path) 
    npath = path+'~'
    count = 0
    while(File.exists?(npath))
      count += 1
      npath = path + '~' + count.to_s
    end
    npath
  end

  def BkupFile.expungeBkups(path)
    file = File.basename(path)
    dir = File.dirname(path)
    re = Regexp.new(Regexp.escape(file+'~')+'\d*')
    Dir.foreach(dir) { |f|
      if re =~ f
	p = dir+"/"+f
	File.unlink(p) if File.exists? p
      end
    }
  end

end
