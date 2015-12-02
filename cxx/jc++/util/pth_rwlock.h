/****************************************************************************
 *
 *
 * File:  pth_rwlock.h
 *
 * Public functions for pth_rwlock.lib
 *
 * PURPOSE
 *
 * This package implements a readers/writer lock facility, using the POSIX
 * threads package. This is very similar to readers/writer lock facility
 * that is part of Solaris native threads, so do 'man rwlock_init' for a
 * description. I have tried to name calls similarly, adding a "pth_" prefix
 * to indicate that this is associated with, but not part of, the POSIX thread
 * package.
 *
 * This package does not prevent a thread from acquiring the read lock twice,
 * such as when a function in your package that holds the lock calls another
 * function which tries to acquire the lock. It is important to ensure that
 * your application does not do this, as a deadlock can result.
 * 
 * It happens in this way: a thread first takes a read lock, and subsequently
 * another thread attempts to acquire a write lock. The writer must wait for
 * all readers to yield the lock before proceeding. When the reader tries to
 * acquire the read lock again, it notices that a writer is pending, and waits
 * to let the write occur. Since it is holding a read lock already, the write
 * cannot proceed, and the threads deadlock.
 *
 * Therefore, you can recognize the deadlock in this way: there are one or
 * more active readers, pending readers and pending writers, and the total
 * will be more than the number of threads that share the data structure.
 *
 *****************************************************************************
 */
#ifndef PTH_RWLOCK_H
#define PTH_RWLOCK_H

#include <pthread.h>

#define pthread_rwlockattr_t void

#ifdef __cplusplus
extern "C" {
#endif


typedef struct pth_rwlock
{
  int    active_readers;/*  -1 when writer active */
  int    pending_readers;
  int    pending_writers;

  pthread_mutex_t mutex;
  pthread_cond_t  ok_to_read;
  pthread_cond_t  ok_to_write; 
} pth_rwlock_t;


/* Initialize a readers/writer lock.
 */
void pth_rwlock_init(pth_rwlock_t * lock, const pthread_rwlockattr_t * attr);


/* Destroy a readers/writer lock. The space used by the rwlock is not freed.
 */
void pth_rwlock_destroy(pth_rwlock_t * lock);


/* Acquire a read-only lock.
 */
void pth_rwlock_rdlock(pth_rwlock_t *lock);


/* Release a read-only lock.
 */
void pth_rwlock_rdunlock(pth_rwlock_t * lock);


/* Acquire a write lock.
 */  
void pth_rwlock_wrlock(pth_rwlock_t * lock);


/* Try to get a write lock, without waiting.
 * As with pthread_mutex_trylock(), returns 0 on success.
 */
int pth_rwlock_wrtrylock(pth_rwlock_t * lock);


/* pth_rwlock_tryupgrade
 *
 * Try to upgrade a read lock to a write lock. 
 * Returns 0 on success, and -1 if there are other active readers.
 */  
int pth_rwlock_tryupgrade(pth_rwlock_t * lock);


/* Release a write lock.
 */
void pth_rwlock_wrunlock(pth_rwlock_t * lock);


/* Release a read-only or write lock.
 */
void pth_rwlock_unlock(pth_rwlock_t * lock);

#ifdef __cplusplus
}
#endif


/*
 * Some useful macros to put in assert()s.
 */
#define READ_LOCK_HELD(lock)(lock.active_readers > 0)

#define WRITE_LOCK_HELD(lock)(lock.active_readers == -1)

/*
 * define pthread_XXX to appropriate symbol defined above
 */

#endif
