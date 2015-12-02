/*************************************************************************/
/* DUCTAPE Version 2.0                                                   */
/* Copyright (C) 2001                                                    */
/* Forschungszentrum Juelich, Zentralinstitut fuer Angewandte Mathematik */
/*************************************************************************/

#ifndef __PDB_FILE_H__
#define __PDB_FILE_H__

#include "pdbSimpleItem.h"

class pdbFile : public pdbSimpleItem {
public:
  pdbFile(int id);
  pdbFile(const string& name, int id);

  typedef vector<pdbFile *> incvec;

  virtual const char *desc() const;
  virtual ostream& print(ostream& ostr) const;
  virtual void adjustPtrs(PDB* p);
  virtual void process(PDB* p);

  incvec& includes();
  const incvec& includes() const;
  int numCalled() const;
  bool isSystemFile() const;

  void addInclude(pdbFile *inc);
  void isSystemFile(bool s);

private:
  incvec incls;
  int    ncall;
  bool   sys;
};

#ifndef NO_INLINE
#  include "pdbFile.inl"
#endif
#endif
