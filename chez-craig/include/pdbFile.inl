/*************************************************************************/
/* DUCTAPE Version 2.0                                                   */
/* Copyright (C) 2001                                                    */
/* Forschungszentrum Juelich, Zentralinstitut fuer Angewandte Mathematik */
/*************************************************************************/

inline pdbFile::pdbFile(int id)
       : pdbSimpleItem(id), ncall(0), sys(false) {}
inline pdbFile::pdbFile(const string& name, int id)
       : pdbSimpleItem(name, id), ncall(0), sys(false) {}

inline const char *pdbFile::desc() const { return "source file"; }

inline pdbFile::incvec& pdbFile::includes() { return incls; }
inline const pdbFile::incvec& pdbFile::includes() const { return incls; }
inline int pdbFile::numCalled() const { return ncall; }
inline bool pdbFile::isSystemFile() const { return sys; }

inline void pdbFile::addInclude(pdbFile *inc) {
  incls.push_back(inc);
  inc->ncall++;
}
inline void pdbFile::isSystemFile(bool s) { sys = s; }
