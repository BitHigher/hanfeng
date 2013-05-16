/* 
 * File:   Math.h
 * Author: zhf
 *
 * Created on 2013年5月16日, 下午9:58
 */

#ifndef MATH_MATH_H
#define	MATH_MATH_H

#include <cstdlib>
#include <stdint.h>

namespace hanfeng
{

class CMath 
{
public:
    CMath();
    CMath(const CMath& orig);
    virtual ~CMath();
    
    /** inline functions **/
    static inline int64_t random()
    {
#if defined(CYGWIN) || defined(__INTERIX)
        return rand();
#else
        return ::random();
#endif
    }
    
    static inline uint64_t random(uint64_t min_value, uint64_t max_value)
    {
        uint64_t ret = min_value + (
                uint64_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        // TODO ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline int64_t random(int64_t min_value, int64_t max_value)
    {
        int64_t ret = min_value + 
                (int64_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        // TODO ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline uint32_t random(uint32_t min_value, uint32_t max_value)
    {
        uint32_t ret = min_value + 
                (uint32_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        // TODO ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline int32_t random(int32_t min_value, int32_t max_value)
    {
        int32_t ret = min_value + 
                (int32_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        // TODO ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
private:

};

}

#endif	/* MATH_MATH_H */

