/*************************************************************************/
/* DUCTAPE Version 2.0                                                   */
/* Copyright (C) 2001                                                    */
/* Forschungszentrum Juelich, Zentralinstitut fuer Angewandte Mathematik */
/*************************************************************************/

#ifndef __PDB_SIMPLE_ITEM_H__
#define __PDB_SIMPLE_ITEM_H__

#include "pdb.h"

class pdbLoc {
public:
  pdbLoc ();
  pdbLoc (pdbFile *file, int line, int col);

  const pdbFile *file() const;
  void file(const pdbFile* file);
  int line() const;
  int col() const;

  void setLoc(pdbFile *file, int line, int col);
  bool operator==(const pdbLoc& rhs) const;
  ostream& printLoc(ostream& ostr) const;

private:
  const pdbFile *fptr;
  int li;
  int co;
};

ostream& operator<<(ostream& ostr, const pdbLoc& l);

class pdbSimpleItem {
public:
  enum dupl_t { NODUPL, OLDDUPL, NEWDUPL };

  static const int UNIQUE = INT_MIN+1;
  static const int NOTDEL = INT_MIN;

  pdbSimpleItem(int id);
  pdbSimpleItem(const string& name, int id);

  virtual ~pdbSimpleItem();

  const string& name() const;
  int id() const;
  int newId() const;

  void name(const string& name);
  void id(int ii);
  void newId(int id);

  virtual const char *desc() const = 0;
  virtual const char *attrPrefix() const;
  virtual ostream& print(ostream& ostr) const = 0;
  virtual void adjustPtrs(PDB*) = 0;

  virtual void process(PDB*);
  virtual dupl_t findDuplicate(pdbSimpleItem* rhs);

  // simple flag / attribute implementation part i
  int flag() const;
  void *attr() const;
  void flag(int flag) const;
  void attr(void *attr) const;

private:
  string nam;
  int    i;
  int    nId;

  // simple flag / attribute implementation part ii
  union {
    mutable int      flg;
    mutable void    *atr;
  };

};

ostream& operator<<(ostream& ostr, const pdbSimpleItem& i);

#ifndef NO_INLINE
#  include "pdbSimpleItem.inl"
#endif
#endif
