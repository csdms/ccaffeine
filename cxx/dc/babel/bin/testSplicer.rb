#!/usr/bin/ruby

require 'splicer.rb'

s = Splicer.new("testSplice.cc")
count = 0
s.debug = true
s.each { |splice, code|
  puts "splice "+count.to_s 
  puts
  puts "Here is the splice:"
  puts splice
  puts
  puts "Here is the code:"
  puts code
  count = count + 1
}
