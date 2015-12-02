#ifndef __DEFAULTKEYVALUEPORT_H__
#define __DEFAULTKEYVALUEPORT_H__


/** A keyvalue port implementation. 
    In a reasonable framework, each component will just be
    automatically decorated with one of these if that framework
    exposes the component to external agents.

    The keys may not contain whitespace or =. The values may be
    anything in a CONST char * .

The const variants of functions exist to shut up solaris.
shut up the Solaris compilers.
*/
class DefaultKeyValuePort 
#ifdef HAVE_CLASSIC
: public virtual classic::gov::cca::KeyValuePort
#endif // HAVE_CLASSIC
{

private:
	::ccafeopq::TypeMap_shared tm;

public:

  DefaultKeyValuePort( ::ccafeopq::TypeMap_shared tm);
  DefaultKeyValuePort();
  void setMap( ::ccafeopq::TypeMap_shared tm);

  virtual ~DefaultKeyValuePort();

  /** Return the value of the requested key.  If key unknown, returns NULL.  */
  virtual const ::std::string getValue(const ::std::string & key);

  /** Store the value for the given key, possibly replacing previous.
      Keys cannot contain the whitespace or '='. Returns nonzero on
      bogus input or other error. */
  virtual void setValue( const ::std::string & key, const ::std::string & value) ;

  /** Delete a key and associated value. The deleted value is returned.
      Returns NULL if key not defined. */
  virtual const ::std::string remove( const ::std::string & key) ;

  /** Return all known keys. May be the empty list. */
  virtual ::std::vector< ::std::string > getKeys(); 

};
#endif //__DEFAULTKEYVALUEPORT_H__
