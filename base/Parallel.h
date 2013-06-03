/* 
 * File:   Parallel.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午7:13
 */

#ifndef BASE_PARALLEL_H
#define BASE_PARALLEL_H

#include "../base/common.h"

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

