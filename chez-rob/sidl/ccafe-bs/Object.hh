#include <stdlib.h>
#include <stdio.h>
#include <string>

namespace ccaffeine {

  class ObjectBase {

  private:

    gov::cca::Type__enum type;

  protected:

    void setType(gov::cca::Type__enum type) {
      this->type = type;
    }

  public:

    ObjectBase() {
      type = None;
    }
    
    ObjectBase(gov::cca::Type__enum type) {
      this->type = type;
    }

    virtual ~ObjectBase(){}
    
    gov::cca::Type__enum getType() {
      return type;
    }

    std::string getTypeAsString() {
      return getTypeAsString(type);
    }

    static std::string getTypeAsString(gov::cca::Type__enum t) {
      switch(t) {
      case None:
	return std::string("None");
	break;
      case Int:
	return std::string("Int");
	break;
      case Long:
	return std::string("Long");
	break;
      case Float:
	return std::string("Float");
	break;
      case Double:
	return std::string("Double");
	break;
      case Fcomplex:
	return std::string("Fcomplex");
	break;
      case Dcomplex:
	return std::string("Dcomplex");
	break;
      case String:
	return std::string("String");
	break;
      case Bool:
	return std::string("Bool");
	break;
      case IntArray:
	return std::string("IntArray");
	break;
      case LongArray:
	return std::string("LongArray");
	break;
      case FloatArray:
	return std::string("FloatArray");
	break;
      case DoubleArray:
	return std::string("DoubleArray");
	break;
      case FcomplexArray:
	return std::string("FcomplexArray");
	break;
      case DcomplexArray:
	return std::string("DcomplexArray");
	break;
      case StringArray:
	return std::string("StringArray");
	break;
      case BoolArray:
	return std::string("BoolArray");
	break;
      default:
	return std::string("No such type");
      }
    }
//     union {
//       bool Bool;
//       SIDL::array<bool>* BoolArray;
//       char Char;
//       int32_t Int;
//       SIDL::array<int>* IntArray;
//       int64_t Long;
//       SIDL::array<long>* LongArray;
//       float Float;
//       SIDL::array<float>* FloatArray;
//       double Double;
//       SIDL::array<double>* DoubleArray;
//       std::complex<float>* Fcomplex;
//       SIDL::array<SIDL::fcomplex>* FcomplexArray;
//       std::complex<double>* Dcomplex;
//       SIDL::array<SIDL::dcomplex>* DcomplexArray;
//       std::string* String;
//       SIDL::array<std::string>* StringArray;

//     } data;
    
  };

  template< typename theType > class Object : public ObjectBase {
    
  private:

    theType val;

  public:

    Object(gov::cca::Type__enum type) : ObjectBase(type) {}

    virtual ~Object(){}

    theType get() {
      return val;
    }

    void set(theType val) {
      this->val = val;
    }
  };


} // end namespace ccaffeine
