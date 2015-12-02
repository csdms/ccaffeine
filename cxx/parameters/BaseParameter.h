#ifndef BaseParameter_h_seen
#define BaseParameter_h_seen

// package parameters;


/** This interface is DEPRECATED.
Documentation for all parameter types:
The toString function for all parameters converts the fields of the 
parameter to a single string which is a & separated list. The fields
of this list are:
<type>
<name>
<current value>
<help>
<prompt> (which is often no more than a parameter name)
<Default> (value to be assigned by the UI if no input received --
           as the current value may simply be uninitialized.)
[additional fields]

The additional depends on the type.

For numeric types (INT,LONG,FLOAT,DOUBLE) we have
<low>
<high>

For STRING types we have
Nchoices=<list len>
<choice 1>
...
<choice len-1>
(If len = 0, any string is allowed)

For BOOL types we have no optional fields.

BUGS:
:&@ are considered special by some downstream users
of these parameters in stringified form. The user is
not prevented from entering these characters in
choiceless STRING values. Development of a suitable
escaping convention is desirable.

*/
class BaseParameter 
{
public:

  virtual ~BaseParameter(){}

  /** Get the bounds, etc as a curiously formatted string */
  /*CFREE*/ virtual char *toString()=0;

  /** Return the simple string (no whitespace) name/key identifying
   this parameter uniquely within a collection of parameters.
   We own this string; don't free it. */
  virtual char *getName() =0;

  /** parse the ascii form of the value. returns 0 if ok, -1 if error. */
  virtual int setValue(char *value) =0;

  /** Get value printed into a string in the usual way.
   We own this string; don't free it (or keep it beyond
   the life of the parameter object).
   In some obscure cases, this may come back as "UNDEFINED". */
  virtual char *getValueString() = 0;

  /** Return the string form of the parameter using infix as part of
    the formatting. We own this string. */
  virtual char *toString(char *infix) =0;

protected:
  /** Expand s by the address of this and returns as a newly malloced string. */
  char *fillString(char *s);
  char *name;
  char *valueString;
};
#endif // BaseParameter_h_seen
