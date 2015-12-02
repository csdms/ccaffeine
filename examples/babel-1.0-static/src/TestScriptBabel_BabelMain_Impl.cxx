// 
// File:          TestScriptBabel_BabelMain_Impl.cxx
// Symbol:        TestScriptBabel.BabelMain-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.BabelMain
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "TestScriptBabel_BabelMain_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_TestScriptBabel_StringMap_hxx
#include "TestScriptBabel_StringMap.hxx"
#endif
#ifndef included_gov_cca_AbstractFramework_hxx
#include "gov_cca_AbstractFramework.hxx"
#endif
#ifndef included_gov_cca_ComponentID_hxx
#include "gov_cca_ComponentID.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_ports_BuilderService_hxx
#include "gov_cca_ports_BuilderService.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._includes)
// Put additional includes or other arbitrary code here...
#define WHINE(s) \
gov::cca::CCAException gex; \
 TestScriptBabel::Exception ex = TestScriptBabel::Exception::_create(); \
 ex.setNote(s); \
 gex = ex; \
 throw gex

#define WHINE2(t,s) \
gov::cca::CCAException gex; \
 TestScriptBabel::Exception ex = TestScriptBabel::Exception::_create(); \
 ex.setNote(s); \
 ex.setType(t); \
 gex = ex; \
 throw gex

#include "gov_cca.hh"
#include "gov_cca_ports.hh"
#include "TestScriptBabel.hh"
#include <iostream>


/** For keys in both tm and values, copy values to tm in the
appropriate format.
*/
void
TestScriptBabel::BabelMain_impl::setParamsFromString(gov::cca::TypeMap & tm, std::map< std::string, std::string > & values)
{
	std::map< std::string, std::string >::const_iterator it;
	std::string key;
	std::string val;
	gov::cca::Type dt;
	for ( it = values.begin(); it != values.end(); ++it ){
            	key =  it->first;
		val = it->second;
		dt = tm.typeOf(key);
		if (dt != gov::cca::Type_NoType) {
			transformString(key, dt, val, tm);
		}
	}
}

//====================== stuff stolen from ccaffeine ================
#if 0
#define REFIX(x,y) if (typeName == y)  return gov::cca::Type_##x
::gov::cca::Type 
TestScriptBabel::BabelMain_impl::typeFromString( const ::std::string &typeName)
{
	REFIX(NoType,"NoType");
	REFIX(Int,"Int");
	REFIX(Long,"Long");
	REFIX(Float,"Float");
	REFIX(Double,"Double");
	REFIX(Dcomplex,"Dcomplex");
	REFIX(Fcomplex,"Fcomplex");
	REFIX(Bool,"Bool");
	REFIX(String,"String");
	REFIX(IntArray,"IntArray");
	REFIX(LongArray,"LongArray");
	REFIX(FloatArray,"FloatArray");
	REFIX(DoubleArray,"DoubleArray");
	REFIX(DcomplexArray,"DcomplexArray");
	REFIX(FcomplexArray,"FcomplexArray");
	REFIX(BoolArray,"BoolArray");
	REFIX(StringArray,"StringArray");
	return gov::cca::NoType;
}
#undef REFIX
#endif
/** key, tm, the destination info. dt, the required type.
 * v, the value to parse into type dt. 
*/
void TestScriptBabel::BabelMain_impl::transformString(const ::std::string & key,
		::gov::cca::Type dt,
		const ::std::string & v, ::gov::cca::TypeMap & tm)
{
	// fixme. try parsing string v to type dt and put it in tm
	// at present this has the effect of dropping the string onthe floor
	// if the parse is not supported.
	if (!tm) { return; }
	::std::istringstream ist(v);
#define UNSTRINGVAL(FTYPE,PRIM) \
    case ::gov::cca::Type_##FTYPE: \
    { PRIM val = 0; \
      ist >> val; \
      tm.put##FTYPE(key, val); \
    } \
    return 
	switch(dt) 
	{
	case ::gov::cca::Type_String: 
		tm.putString(key, v); 
		return;
	UNSTRINGVAL(Int, int32_t);
	UNSTRINGVAL(Long,  int64_t);
	UNSTRINGVAL(Double, double);
	UNSTRINGVAL(Float, float);
	UNSTRINGVAL(Bool, bool);
	UNSTRINGVAL(Dcomplex, ::std::complex<double> );
	UNSTRINGVAL(Fcomplex, ::std::complex<float> );
	case ::gov::cca::Type_NoType: return ;
	case ::gov::cca::Type_IntArray:
	case ::gov::cca::Type_LongArray:
	case ::gov::cca::Type_FloatArray:
	case ::gov::cca::Type_DoubleArray:
	case ::gov::cca::Type_DcomplexArray:
	case ::gov::cca::Type_FcomplexArray:
	case ::gov::cca::Type_BoolArray: 
	case ::gov::cca::Type_StringArray:
	// fixme whine here.
	default:
		return;
	}
#undef UNSTRINGVAL
}

#if 0
int TestScriptBabel::BabelMain_impl::putValueByStrings( ::gov::cca::TypeMap t, const ::std::string & key, const ::std::string &vtype, const ::std::string & val)
{
	if (!t || key.size() == 0) { return -1; }
	::gov::cca::Type kt = typeFromString(vtype); 
	if (kt ==  ::gov::cca::Type_NoType) { return -1; }
	try {
		TestScriptBabel::BabelMain_impl::transformString( key, kt, val, t);
		return 0;
	}
	catch ( std::exception &e )
	{
		return -1;
	}

}

//---------------------------------------------------------- 
const ::std::string 
TestScriptBabel::BabelMain_impl::typeToName( ::gov::cca::Type t) { 
	switch(t) 
	{
		case ::gov::cca::Type_NoType: return "NoType"; 
		case ::gov::cca::Type_Int: return "Int"; 
		case ::gov::cca::Type_Long: return "Long"; 
		case ::gov::cca::Type_Float: return "Float"; 
		case ::gov::cca::Type_Double: return "Double"; 
		case ::gov::cca::Type_Dcomplex: return "Dcomplex"; 
		case ::gov::cca::Type_Fcomplex: return "Fcomplex"; 
		case ::gov::cca::Type_Bool: return "Bool"; 
		case ::gov::cca::Type_String: return "String"; 

		case ::gov::cca::Type_IntArray: return "IntArray"; 
		case ::gov::cca::Type_LongArray: return "LongArray"; 
		case ::gov::cca::Type_FloatArray: return "FloatArray"; 
		case ::gov::cca::Type_DoubleArray: return "DoubleArray"; 
		case ::gov::cca::Type_DcomplexArray: return "DcomplexArray"; 
		case ::gov::cca::Type_FcomplexArray: return "FcomplexArray"; 
		case ::gov::cca::Type_BoolArray: return "BoolArray"; 
		case ::gov::cca::Type_StringArray: return "StringArray"; 
		default: return "unknown";
	}
}
//
//
//---------------------------------------------------------- 
//
::std::string 
TestScriptBabel::BabelMain_impl::stringType( ::gov::cca::TypeMap t, const ::std::string &key)
{
	if (!t) {
		return "";
	}
	enum ::gov::cca::Type kt = t.typeOf(key);
	return TestScriptBabel::BabelMain_impl::typeToName(kt);
}

#endif

//---------------------------------------------------------- 
// there's a nice nonportable way to do this with strstream
#define STRINGVAL(BTYPE, FTYPE, DEFVAL, FMT) \
  case ::gov::cca::Type_##FTYPE: \
    { \
      BTYPE v = t.get##FTYPE(key, DEFVAL); \
      sprintf(buf, FMT, v); \
      s += buf; \
      return s; \
    } \
  break
#undef STRINGVAL
#define STRINGVAL(FTYPE,DEFVAL) \
  case ::gov::cca::Type_##FTYPE: \
    ost << t.get##FTYPE(key, DEFVAL); \
    return ost.str(); \
  break
        
#define ARRAYVAL(FTYPE,VTYPE) \
  case ::gov::cca::Type_##FTYPE##Array: \
  { \
    ::sidl::array< VTYPE > v; \
    v = t.get##FTYPE##Array( key, v ); \
    for (int i = v.lower(0); i <= v.upper(0); i++) \
    { \
      ost << v[i] << " "; \
    } \
    return ost.str(); \
  } \
  break
        
::std::string 
TestScriptBabel::BabelMain_impl::stringValue( ::gov::cca::TypeMap t, const ::std::string &key)
{
	::std::string s;
	if (!t) { return s; }
	::std::ostringstream ost;
	enum ::gov::cca::Type kt = t.typeOf(key);
	// char buf[128];
	switch (kt) {
	case ::gov::cca::Type_NoType: return s;
	STRINGVAL(Int,0);
	STRINGVAL(Long, 0);
	STRINGVAL(Double, 0);
	STRINGVAL(Float, 0);
	STRINGVAL(Bool, false);
	STRINGVAL(String, "");
	STRINGVAL(Dcomplex, ::std::complex<double>(0,0) );
	STRINGVAL(Fcomplex, ::std::complex<float>(0,0) );
	ARRAYVAL(Int, int32_t);
	ARRAYVAL(Long, int64_t);
	ARRAYVAL(Double, double);
	ARRAYVAL(Float, float);
	ARRAYVAL(Bool, bool);
	ARRAYVAL(String, ::std::string );
	ARRAYVAL(Dcomplex, ::std::complex<double> );
	ARRAYVAL(Fcomplex, ::std::complex<float> );
	default:
		return s;
	}
}
#undef STRINGVAL
#undef ARRAYVAL


#if 0

void 
TestScriptBabel::BabelMain_impl::dumpTypeMapStdout(::gov::cca::TypeMap t)
{
	std::vector< std::string > keys = t.getAllKeys( ::gov::cca::Type_NoType );
	std::sort(keys.begin(), keys.end());
	for (size_t i = 0; i < keys.size(); i++) {
		::std::cout << "["<< keys[i] << "](" <<
		       	TestScriptBabel::BabelMain_impl::stringType(t,keys[i]) << ") " <<
			TestScriptBabel::BabelMain_impl::stringValue(t,keys[i]) << std::endl;
	}
}
#endif 

// DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
TestScriptBabel::BabelMain_impl::BabelMain_impl() : StubBase(reinterpret_cast< 
  void*>(::TestScriptBabel::BabelMain::_wrapObj(reinterpret_cast< 
  void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._ctor2)
  // Insert-Code-Here {TestScriptBabel.BabelMain._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._ctor2)
}

// user defined constructor
void TestScriptBabel::BabelMain_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._ctor)
}

// user defined destructor
void TestScriptBabel::BabelMain_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._dtor)
}

// static class initializer
void TestScriptBabel::BabelMain_impl::_load() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._load)
  // Insert-Code-Here {TestScriptBabel.BabelMain._load} (class initialization)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  invokeGo[]
 */
int32_t
TestScriptBabel::BabelMain_impl::invokeGo_impl (
  /* in */const ::std::string& component,
  /* in */const ::std::string& port,
  /* in */::gov::cca::ComponentID c,
  /* in */::gov::cca::Services services,
  /* in */::gov::cca::ports::BuilderService bs ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain.invokeGo)

        std::string pname = component;
        pname += "_";
        pname += port;
        gov::cca::Port p_go;
	gov::cca::TypeMap dummy;
        services.registerUsesPort(pname, "gov.cca.ports.GoPort",dummy);
        gov::cca::ComponentID myself = services.getComponentID();
        gov::cca::ConnectionID goConn = bs.connect(myself, pname, c, port);
        p_go = services.getPort(pname);
        gov::cca::ports::GoPort go = p_go;
        if (go._is_nil() ) {
                WHINE2( gov::cca::CCAExceptionType_BadPortType, "Port is not of expected type GoPort.") ;
        }
        int result;
        result = go.go();
        if (result != 0) {
                std::cerr << pname <<" returned error code: " << result << std::endl;
        }
        services.releasePort(pname);
        bs.disconnect(goConn, 0.0);
        services.unregisterUsesPort(pname);
	return result;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain.invokeGo)
}

/**
 *  This function handles the configuring of 
 * parameters when all we know is the
 * info available from a ccaffeine script (which hides 
 * parameter and port types).
 * If component port and config information were 
 * ubiquitous at code generation time, this wouldn't be needed.
 * @param compName name of the component being configured.
 * @param port name of the port being configured.
 * @param comp ComponentID of the component being configured.
 * @param bs BuilderService controlling the frame.
 * @param services Services of the component/driver 
 * doing the parameter setting.
 * @param values  map of keys and values to assign.
 */
void
TestScriptBabel::BabelMain_impl::setParameters_impl (
  /* in */const ::std::string& component,
  /* in */const ::std::string& port,
  /* in */::gov::cca::ComponentID c,
  /* in */::gov::cca::ports::BuilderService bs,
  /* in */::gov::cca::Services services,
  /* in */::TestScriptBabel::StringMap sm ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain.setParameters)
	std::string compName = component;
	gov::cca::ComponentID myself = services.getComponentID();
	gov::cca::TypeMap dummy;
	gov::cca::TypeMap pProps = bs.getPortProperties(c, port);
	std::string portType = pProps.getString("cca.portType", "undefined");
 	gov::cca::Port p_param = 0;
	std::string pname = compName;
	pname += "_";
	pname += port;
	if ( portType == "gov::cca::ports::BasicParameterPort" ||
		portType == "::gov::cca::ports::BasicParameterPort" ||
		// portType == "::ccafeopq::ports::BasicParameterPort" ||
		portType ==  "gov.cca.ports.BasicParameterPort") 
	{
		gov::cca::ports::BasicParameterPort  bpp ;
		services.registerUsesPort(pname, "gov::cca::ports::BasicParameterPort", dummy);
		gov::cca::ConnectionID bppconn =
			bs.connect(myself, pname, c, port);
		p_param = services.getPort(pname);
		bpp = (p_param); //CAST
		if (bpp._not_nil()) {
			gov::cca::TypeMap params = bpp.readConfigurationMap();
			std::map< std::string, std::string > & stdsm = 
				*(static_cast< std::map< std::string, std::string > * >(sm.getUnderlyingStdMap())) ;
			setParamsFromString(params, stdsm);
			bpp.writeConfigurationMap(params);
		} else {
			std::string msg = "Port ";
			msg += compName; msg += "."; msg += port;
			msg += " is not of expected type BasicParameterPort (cast fail)";
			WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
		}
		services.releasePort(pname);
		bs.disconnect(bppconn, 0.0);
		services.unregisterUsesPort(pname);
		return;
	}
	if ( portType == "gov::cca::ports::ParameterPort" ||
		portType == "::gov::cca::ports::ParameterPort" ||
		// portType == "::ccafeopq::ports::ParameterPort" ||
		portType ==  "gov.cca.ports.ParameterPort") 
	{
		gov::cca::ports::ParameterPort  pp;
		services.registerUsesPort(pname, "gov::cca::ports::ParameterPort", dummy);
		gov::cca::ConnectionID ppconn =
			bs.connect(myself, pname, c, port);
		p_param = services.getPort(pname);
		pp = p_param; //CAST
		if (pp._not_nil() ) {
			gov::cca::TypeMap params = pp.readConfigurationMap();
			std::map< std::string, std::string > & stdsm2 = 
				*(static_cast< std::map< std::string, std::string > * >(sm.getUnderlyingStdMap())) ;
			setParamsFromString(params, stdsm2);
			pp.writeConfigurationMap(params);
		} else {
			std::string msg = "Port ";
			msg += compName; msg += "."; msg += port;
			msg += " is not of expected type ParameterPort (cast fail)";
			WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
		}
		services.releasePort(pname);
		bs.disconnect(ppconn, 0.0);
		services.unregisterUsesPort(pname);
		return;
	}
	std::string msg = "Port ";
	msg += compName; msg += "."; msg += port;
	msg += " is not a parameter port. seems to be a ";
	msg += portType;
	WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
  

  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain.setParameters)
}

/**
 *  This function returns a stringified version of a parameter value.
 */
::std::string
TestScriptBabel::BabelMain_impl::getParameterValue_impl (
  /* in */::gov::cca::ComponentID c,
  /* in */const ::std::string& portName,
  /* in */const ::std::string& var,
  /* in */::gov::cca::Services services,
  /* in */::gov::cca::ports::BuilderService bs ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain.getParameterValue)
	std::string compName = c.getInstanceName();
	std::string port = portName;

	gov::cca::ComponentID myself = services.getComponentID();
	gov::cca::TypeMap dummy;
	gov::cca::TypeMap pProps = bs.getPortProperties(c, port);
	std::string portType = pProps.getString("cca.portType", "undefined");
 	gov::cca::Port p_param = 0;
	std::string pname = compName;
	pname += "_";
	pname += port;
	std::string result;
	if ( portType == "gov::cca::ports::BasicParameterPort" ||
		portType == "::gov::cca::ports::BasicParameterPort" ||
		// portType == "::ccafeopq::ports::BasicParameterPort" ||
		portType ==  "gov.cca.ports.BasicParameterPort") 
	{
		gov::cca::ports::BasicParameterPort  bpp ;
		services.registerUsesPort(pname, "gov::cca::ports::BasicParameterPort", dummy);
		gov::cca::ConnectionID bppconn =
			bs.connect(myself, pname, c, port);
		p_param = services.getPort(pname);
		bpp = (p_param); //CAST
		if (bpp._not_nil()) {
			gov::cca::TypeMap params = bpp.readConfigurationMap();
			result = stringValue(params,var);
		} else {
			std::string msg = "Port ";
			msg += compName; msg += "."; msg += port;
			msg += " is not of expected type BasicParameterPort (cast fail)";
			services.releasePort(pname);
			bs.disconnect(bppconn, 0.0);
			services.unregisterUsesPort(pname);
			WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
			return result ; // not reached we hope.
		}
		services.releasePort(pname);
		bs.disconnect(bppconn, 0.0);
		services.unregisterUsesPort(pname);
		return result;
	}
	if ( portType == "gov::cca::ports::ParameterPort" ||
		portType == "::gov::cca::ports::ParameterPort" ||
		// portType == "::ccafeopq::ports::ParameterPort" ||
		portType ==  "gov.cca.ports.ParameterPort") 
	{
		gov::cca::ports::ParameterPort  pp;
		services.registerUsesPort(pname, "gov::cca::ports::ParameterPort", dummy);
		gov::cca::ConnectionID ppconn =
			bs.connect(myself, pname, c, port);
		p_param = services.getPort(pname);
		pp = p_param; //CAST
		if (pp._not_nil() ) {
			gov::cca::TypeMap params = pp.readConfigurationMap();
			result = stringValue(params,var);
		} else {
			std::string msg = "Port ";
			msg += compName; msg += "."; msg += port;
			msg += " is not of expected type ParameterPort (cast fail)";
			services.releasePort(pname);
			bs.disconnect(ppconn, 0.0);
			services.unregisterUsesPort(pname);
			WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
			return result;  // not reached we hope.
		}
		services.releasePort(pname);
		bs.disconnect(ppconn, 0.0);
		services.unregisterUsesPort(pname);
		return result;
	}
	std::string msg = "Port ";
	msg += compName; msg += "."; msg += port;
	msg += " is not a parameter port. seems to be a ";
	msg += portType;
	WHINE2(gov::cca::CCAExceptionType_BadPortType, msg);
	return result; // notreached we hope
  
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain.getParameterValue)
}

/**
 * Method:  driverBody[]
 */
void
TestScriptBabel::BabelMain_impl::driverBody_impl (
  /* inout */::gov::cca::AbstractFramework& af ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain.driverBody)
	gov::cca::TypeMap dummy;
	dummy = af.createTypeMap();

	gov::cca::ports::BuilderService bs, dummybs;
	TestScriptBabel::PrivateRepository pr;
	pr = TestScriptBabel::PrivateRepository::_create();

	gov::cca::Services services;
	// set the script up as a component in the frame it receives.
	services = af.getServices("TestScriptBabel_BabelMain", "TestScriptBabel_BabelMain", dummy);
	// and find its id tag in the frame.
	gov::cca::ComponentID myself = services.getComponentID();

	// tell the framework about the components that come with the driver.
	// the components from PrivateRepository will now be available from
	// the BuilderService port.
	
	services.addProvidesPort(pr, "TestScriptBabel_PrivateRepository", "ccaffeine.ports.ComponentFactory", dummy);

	services.registerUsesPort("bs", "gov.cca.ports.BuilderService", dummy);

	gov::cca::Port dummyp;
	gov::cca::Port p;
	p = services.getPort("bs");
	if ( p._is_nil() ) {
		WHINE("Service port bs is missing!");
	}
	bs = p; // CAST
	if ( bs._is_nil() ) {
		WHINE2(gov::cca::CCAExceptionType_BadPortType, "Service port bs is not of expected type neo::cca::ports::BuilderService");
	}
	// scripted source here

#include "TestScriptBabel.BabelMain.driverBody.guts.hh"

	// end script source
	bs = dummybs;
	p = dummyp;
	services.releasePort("bs");
	services.unregisterUsesPort("bs");
	services.removeProvidesPort("TestScriptBabel_PrivateRepository");
	// remove ourselves from the frame.
	af.releaseServices(services);


  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain.driverBody)
}


// DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._misc)

