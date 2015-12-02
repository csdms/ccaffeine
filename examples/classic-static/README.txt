This is an example of static linking a set of classic
components into a ccaffeine runtime. It is intended
to be built (or copied and built) only after ccaffeine
is installed.

You will need to run configure to set the appropriate
ccafe-config determined variables.

ExampleStaticFactory and Makefile (APPL_* variables)
is all that needs customizing. If you wish to use
a name other than ExampleStaticFactory, replaces all
occurrences of 'ExampleStaticFactory' appropriately in
StaticCmdLineClientMain.cxx.

The .a files of the components must be supplied in
the makefile and must include the create_ functions
from the generated wrapper code.

The framework takes a pointer to a
StaticFactory vtable interface in a setting function. 
If that function is not called, the factory will be ignored.

./run is an example (non-mpi, add your own queue) of
running it.

No translation of ccaffeine scripts is needed. benscript
is read by this version.
