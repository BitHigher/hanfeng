/* 
 * File:   Parallel.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午7:13
 */

#ifndef BASE_PARALLEL_H
#define BASE_PARALLEL_H

#include "../base/common.h"

#ifdef HAVE_PTHREAD
#ifdef USE_SPINLOCKS
    #define PTHREAD_LOCK_T pthread_spinlock_t
    #define PTHREAD_LOCK_INIT(lock) pthread_spinlock_init(lock, NULL)
    #define PTHREAD_LOCK_DESTROY(lock) pthread_spinlock_destroy(lock)
    #define PTHREAD_LOCK(lock) pthread_spinlock_lock(lock)
    #define PTHREAD_UNLOCK(lock) pthread_spinlock_unlock(lock)
#else
    #define PTHREAD_LOCK_T pthread_mutex_t
    #define PTHREAD_LOCK_INIT(lock) pthread_mutex_init(lock, NULL)
    #define PTHREAD_LOCK_DESTROY(lock) pthread_mutex_destroy(lock)
    #define PTHREAD_LOCK(lock) pthread_mutex_lock(lock)
    #define PTHREAD_UNLOCK(lock) pthread_mutex_unlock(lock)
#endif /* USE_SPINLOCKS */
#endif /* HAVE_PTHREAD */


namespace hanfeng
{

class Parallel {
public:
    Parallel();
    Parallel(const Parallel& orig);
    virtual ~Parallel();
    
    int32_t get_num_cpus() const;
    void set_num_threads(int32_t n);
    int32_t get_num_threads() const;

    inline int32_t ref_count(){return refcount_;}
    int32_t ref();
    int32_t unref();
    
    
private:
    int32_t refcount_;
    int32_t num_threads_;
};

}
#endif	/* BASE_PARALLEL_H */

