Notes on converting to babel 0.9.4 from 0.8.x.
Ben Allan, SNL/CA, August 2004.

Sidl issues, C++ issues, build issues, misc notes.


SIDL issues:
S1) sidl input exception inheritances changed in spec.
S2) ServiceRegistry/ServiceProvider supported.
S3) ParameterPort, BasicParameterPort supported.


C++ issues:
C(-1)) gcc 2.96 is NOT supported. (3.x and 2.95.3 are).
C0) babel 0.9.2 and earlier are NOT supported.
C1) cca-spec-babel v 0.7.0 or later required.
C2) sed /SIDL::/sidl::/g
C3) c++ enum renderings. eg:
  ::gov::cca::Nonstandard --> ::gov::cca::CCAExceptionType_Nonstandard
  ::gov::cca::Double --> ::gov::cca::Type_Double


Build tool issues:

B1) No libxml2 == no dynamic babel loading. 
B2) SIDL_DLL_PATH not needed, mostly.
B3) Until a better solution is found, a deployed babel component consists of:
  X.depl.cca,
  libX.so (or libX.a),
all put in the same lib directory.

Babel and CCA xml data are combined.
The XML file (.cca) gea generated with a tool installed from cca-spec-babel.
What was dccafe's genDLIndexXML has been replaced with genSCLCCA.sh as:
	CCASPEC_GENSCLCCA_SH=`cca-spec-babel-config --var CCASPEC_GENSCLCCA_SH`
or by including MakeIncl_CCA_Babel_Vars which at configure time is:
	CCASPEC_MAKEINCL=`cca-spec-babel-config --var CCASPEC_MAKEINCL`
and then something like (for static library):
$CCASPEC_GENSCLCCA_SH cca /installroot/lib/libComponent3.a test3.Component1 Comp3

To support dynamic loading of babel components, $CCASPEC_GENSCLCCA_SH
requires additional arguments. See $CCASPEC_GENSCLCCA_SH --help
for additional examples. If that doesn't do it for you, see also
dccafe/cxx/dc/babel/components/PrinterComponent/Makefile
and search for the uses of CCASPEC_GENSCLCCA_SH.


Misc notes:

0) The Babel dynamic class loader where formerly called with 
just a babel class name, now has to be poked more carefully:
// find the library for "x.y.z" in .scl files.
DLL dll = Loader::findLibrary("x.y.z", "ior/impl", Scope_SCLSCOPE, Resolve_SCLRESOLVE,);
// invoke the constructor.
if (dll._not_nil()) {
  BaseClass bc = dll.createClass("x.y.z");
}

1) It would be nice to point in the .cca file at all the ports used and
where their sidl/xml definitions reside. At present, this is messy to
automate.
