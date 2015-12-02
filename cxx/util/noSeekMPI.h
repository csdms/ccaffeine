#ifndef noSeekMPI_h_seen
#define noSeekMPI_h_seen
/* a workaround to allow mpi.h and stdio/iostream in the same file.
 * in the presence of *GOOFY* mpi 2 SEEK binding.
 */
#ifdef SEEK_SET
#undef SEEK_SET
#endif
#ifdef SEEK_CUR
#undef SEEK_CUR
#endif
#ifdef SEEK_END
#undef SEEK_END
#endif
#endif /* noSeekMPI_h_seen */
