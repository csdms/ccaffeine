Notes on converting to babel 0.9.2.
If you have not converted to 0.9.2 yet, we recommend you wait for 0.9.4
instead.
Ben Allan, SNL/CA, May 2004.

Sidl issues, C++ issues, build issues, misc notes.


SIDL issues:
S1) sidl input exception inheritances changed in spec.
S2) ServiceRegistry/ServiceProvider supported.
S3) ParameterPort, BasicParameterPort supported.


C++ issues:
C0) babel 0.9.1 and earlier are NOT supported.
C1) cca-spec-babel v 0.7.0 or later required.
C2) sed /SIDL::/sidl::/g
C3) c++ enum renderings. eg:
  ::gov::cca::Nonstandard --> ::gov::cca::CCAExceptionType_Nonstandard
  ::gov::cca::Double --> ::gov::cca::Type_Double


Build tool issues:

B1) No xml == no dynamic babel loading. 
B2) SIDL_DLL_PATH not needed, mostly.
B3) Until a better solution is found, a deployed babel component consists of:
  X.depl.cca,
  libX.so.scl (or libX.a.scl)
  libX.so (or libX.a),
all put in the same lib directory.

Ideally, .scl and .cca could be combined, but babel chokes and fails to load if 
anything other than scl tags appear in the scl file. 
The XML files (.cca, .scl) get generated with a tool from cca-spec-babel, now.
What was dccafe's genDLIndexXML has been replacedwith genSCLCCA.sh obtainable as:
	CCASPEC_GENSCLCCA_SH=`cca-spec-babel-config --var CCASPEC_GENSCLCCA_SH`
or by including MakeIncl_CCA_Babel_Vars which is obtainable at configure time as:
	CCASPEC_MAKEINCL=`cca-spec-babel-config --var CCASPEC_MAKEINCL`
and then something like:
$CCASPEC_GENSCLCCA_SH scl /installroot/lib/libComponent3.a test3.Component1 Comp3
$CCASPEC_GENSCLCCA_SH cca /installroot/lib/libComponent3.a test3.Component1 Comp3

To support dynamic loading of babel components, $CCASPEC_GENSCLCCA_SH
requires additional arguments. See $CCASPEC_GENSCLCCA_SH --help
for additional examples. If that doesn't do it for you, see also
dccafe/cxx/dc/babel/components/PrinterComponent/Makefile
and search for the uses of CCASPEC_GENSCLCCA_SH.


Misc notes:

0) Babel dynamic class loader where formerly called with just a babel class name,
now has to be poked more carefully:
// find the library for "x.y.z" in .scl files.
DLL dll = Loader::findLibrary("x.y.z", "ior/impl", Scope_SCLSCOPE, Resolve_SCLRESOLVE,);
// invoke the constructor.
if (dll._not_nil()) {
  BaseClass bc = dll.createClass("x.y.z");
}

1) It would be nice to point in the .cca file at all the ports used and
where their sidl/xml definitions reside. At present, this is messy to
automate.
