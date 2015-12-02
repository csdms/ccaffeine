require "tst"

# Note that ruby will always capitalize the class (Swig calls it
# "module") name regardless of whether you declared it as such in the
# ".i" file.

puts "Here is the string: "+Tst.getString()


