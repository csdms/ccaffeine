/*****************************************************************************
 *
 * File: pth_rwlock.c
 *
 * This package implements a readers/writer lock facility, using the POSIX
 * threads package. This is very similar to readers/writer lock facility that
 * is part of Solaris native threads, so do 'man rwlock_init' for description.
 * I have tried to name calls similarly, adding a "pth_" prefix to indicate
 * that this is associated with, but not part of, the POSIX thread package.
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
#include <assert.h>
#include "pth_rwlock.h"

#define PTHREAD_MUTEXATTR_DEFAULT NULL
#define PTHREAD_CONDATTR_DEFAULT  NULL


/* pth_rwlock_init - Initialize a readers/writer lock.
 */
void pth_rwlock_init(pth_rwlock_t * lock,  const pthread_rwlockattr_t * attr)
{
  lock->active_readers = 0;
  lock->pending_readers = 0;
  lock->pending_writers = 0;
  pthread_mutex_init(&lock->mutex, PTHREAD_MUTEXATTR_DEFAULT);
  pthread_cond_init (&lock->ok_to_read, PTHREAD_CONDATTR_DEFAULT);
  pthread_cond_init (&lock->ok_to_write, PTHREAD_CONDATTR_DEFAULT);
}

/* pth_rwlock_destroy - Destroy a readers/writer lock.
 * The space used by the rwlock is not freed.
 */
void pth_rwlock_destroy(pth_rwlock_t * lock)
{
  pthread_mutex_destroy(&lock->mutex);
  pthread_cond_destroy (&lock->ok_to_read);
  pthread_cond_destroy (&lock->ok_to_write);
}

/* pth_rwlock_rdlock - Acquire a read-only lock.
 */
void pth_rwlock_rdlock(pth_rwlock_t *lock)
{
  pthread_mutex_lock(&lock->mutex);

  lock->pending_readers++;

  /* Wait for pending writers. Comment this out to avoid 
   * deadlocks when readers take the lock recursively.
   */
  if (lock->pending_writers > 0)
    pthread_cond_wait(&lock->ok_to_read, &lock->mutex);

  /* Wait while writers are active */
  while (lock->active_readers < 0)
    pthread_cond_wait(&lock->ok_to_read, &lock->mutex);

  lock->pending_readers--;
  lock->active_readers++;
  pthread_mutex_unlock(&lock->mutex);
}

/* pth_rwlock_rdunlock - Release a read-only lock.
 */
void pth_rwlock_rdunlock(pth_rwlock_t * lock)
{
  pthread_mutex_lock(&lock->mutex);
  assert(lock->active_readers > 0);

  lock->active_readers--;

  /* If we are the last reader out, signal writer.
   */
  if (lock->active_readers == 0)
    pthread_cond_signal(&lock->ok_to_write);

  pthread_mutex_unlock(&lock->mutex);
}

/* pth_rwlock_wrlock - Acquire a write lock.
 */  
void pth_rwlock_wrlock(pth_rwlock_t * lock)
{
  pthread_mutex_lock(&lock->mutex);

  lock->pending_writers++;

  while (lock->active_readers)
    pthread_cond_wait(&lock->ok_to_write, &lock->mutex);

  lock->pending_writers--;
  assert(lock->active_readers == 0);

  lock->active_readers = -1;
  pthread_mutex_unlock(&lock->mutex);
}


/* pth_rwlock_wrtrylock
 *
 * Attempt to immediately acquire a write lock. To make this
 * consistent with the pthread calls, we return 0 on success,
 * and -1 if the lock is busy.
 */  
int pth_rwlock_wrtrylock(pth_rwlock_t * lock)
{
  int result = -1;

  pthread_mutex_lock(&lock->mutex);

  if (lock->active_readers == 0)
    {
      lock->active_readers = -1;
      result = 0;
    }

  pthread_mutex_unlock(&lock->mutex);

  return result;
}


/* pth_rwlock_tryupgrade
 *
 * Attempt to immediately acquire a write lock when you already
 * hold a read lock. This call will fail if there are other active
 * readers. If this call succeeds, you must call pth_rwlock_wrunlock
 * or pth_rwlock_unlock() to yield the lock.
 *
 * To make this consistent with the pthread calls, we return 0 on
 * success, and -1 if the lock is busy.
 */  
int pth_rwlock_tryupgrade(pth_rwlock_t * lock)
{
  int result = -1;

  pthread_mutex_lock(&lock->mutex);

  assert(lock->active_readers > 0);/* caller at least must hold read lock */

  if (lock->active_readers == 1)
    {
      lock->active_readers = -1;
      result = 0;
    }

  pthread_mutex_unlock(&lock->mutex);

  return result;
}


/* pth_rwlock_wrunlock - Release a write lock.
 */
void pth_rwlock_wrunlock(pth_rwlock_t * lock)
{
  pthread_mutex_lock(&lock->mutex);

  assert(lock->active_readers == -1);

  lock->active_readers = 0;

  /* Signal waiters while holding the mutex, to meet the
   * requirements of our pthread_cond_wait emulation for WIN32.
   */
  if (lock->pending_readers != 0)
    /* Wake all readers.
     */
    pthread_cond_broadcast(&lock->ok_to_read);
    else
      /* Wake a single writer.
       */
      pthread_cond_signal(&lock->ok_to_write);

  pthread_mutex_unlock(&lock->mutex);
}



/* pth_rwlock_unlock - Promiscuous lock-release.
 * Releases reader or writer lock, depending on which we hold.
 * This is useful with the try_upgrade call.
 */
void pth_rwlock_unlock(pth_rwlock_t * lock)
{
  pthread_mutex_lock(&lock->mutex);

  assert(lock->active_readers != 0);
  assert(lock->active_readers > -1);

  if (lock->active_readers > 0)
    {
      lock->active_readers--;

      /* If we are the last reader out, signal writer.
       */
      if (lock->active_readers == 0)
	pthread_cond_signal(&lock->ok_to_write);
    }
  else if (lock->active_readers == -1);
  {
    lock->active_readers = 0;

    /* Signal waiters while holding the mutex, to meet the
     * requirements of our pthread_cond_wait emulation for WIN32.
     */
    if (lock->pending_readers != 0)
      /* Wake all readers.
       */
      pthread_cond_broadcast(&lock->ok_to_read);
    else
      /* Wake a single writer.
       */
      pthread_cond_signal(&lock->ok_to_write);
  }

  pthread_mutex_unlock(&lock->mutex);
}
