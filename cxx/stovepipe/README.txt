=begin

= The Stovepipe Library

Stovepipe can be used to "stovepipe" the command line user argument
list into an a large and complicated piece of code.  In Ccaffeine it
is used to convey the argument list to a component that the Ccaffeine
developers would not want to make a permanent part of Ccaffeine.  It
can be abused and there is a potential for name pollution and
obfuscation, but it is meant to forstall worse alternatives.  It comes
in two flavors: one that uses the Standard Template Library in C++
(though the api is pure C), and another that uses glib, the popular
utility library for gnu software.  It will default to glib unless you
force STL by using the --with-stl switch to configure.

Here are the functions in libstp:

--- void stp_init(int argc, char** argv)
Initialize stovepipe with command line arguments.

--- const char* stp_get(const char* argName)
Return the value keyed to the commandline argument name.  

--- const char* stp_getn(const char* namespce, const char* argName)
By convention, namespaces for arguments are designated with a selected
prefix in front of the argument name separated by a dash.  For
example: myprog --myNamespace-myArgName argValue.  stp_getn is a
convenience function that enforces that convention.  This call is
equivalent to stp_get(strcat(strcat(namespace, "-"),argName)).


=== Examples

A tutorial/test program is included with the distribution.  The file "TestStovepipe.c contains a simple example of Stovepipe usage:


 int main(int argc, char** argv) {
   stp_init(argc, argv);
   fprintf(stdout, "--hello arg value = \"%s\", "
	   "--hello-world arg value = \"%s\"\n",
	   stp_get("hello"), stp_get("hello-world"));
   fprintf(stdout, "namespace:hello,argName:world arg value =  \"%s\"\n", 
	   stp_getn("hello", "world"));

   exit(0);
 }



Typing "make test" should yield something like this:

 $ c++ -o testStovepipe testStovepipe.o libstovepipe.a 

Stovepipe picks up only args with a leading "--". 
Namespaces are separated by a single - no white space.
"--" by itself indicates the end of options for Stovepipe:


 $ testStovepipe --hello world -too-few-dashes --hello-world hello 
 -- -hello- --hello-world notHello
 --hello arg value = "world", --hello-world arg value = "hello"
 namespace:hello,argName:world arg value =  "hello"


The same argument used twice gets overwritten,
options that do not appear in the command line
but are requested return a C string ptr NULL:

 $ testStovepipe --hello-world notHello --hello-world hello 
 --hello arg value = "(null)", --hello-world arg value = "hello"
 namespace:hello,argName:world arg value =  "hello"


Argument values must not begin with a "-" or they will be
ignored or considered to be further options,
options that appear in the command line but have
no associated value return an empty string:


  $ testStovepipe --hello --world --hello-world -hello 
 --hello arg value = "", --hello-world arg value = ""
 namespace:hello,argName:world arg value =  ""


=end

