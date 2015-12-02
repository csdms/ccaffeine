#ifndef  freefree_seen
/**
  This very pernicious little file is intended to bypass all calls
  to free, so that for creating demos on a crash basis, we simply
  drop memory on the floor. this is considered superior to
  creating crashing demos on reusable code basis. ugh.
  Hand purify to a summer student and have them clean up the
  mem management.

  This header must be included absolutely last to avoid potential
  system header conflicts or redefinitions.
*/
#define freefree_seen

/** if compiled -D_FREEFREE, this header is active. */
#ifdef _FREEFREE
/* do the deed. If freefree.h is seen, free(X) gets defined away. */
#define free(x)
#endif /*_FREEFREE*/
/** free if you really want it .*/
extern void Free(void *); 
/* function body is defined in IO.cxx */
#endif /*freefree_seen*/
