/* 
 * File:   Math.h
 * Author: zhf
 *
 * Created on 2013年5月16日, 下午9:58
 */

#ifndef MATH_MATH_H
#define MATH_MATH_H

#include "../base/common.h"
#include "../io/HFIO.h"

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
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline int64_t random(int64_t min_value, int64_t max_value)
    {
        int64_t ret = min_value + 
                (int64_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline uint32_t random(uint32_t min_value, uint32_t max_value)
    {
        uint32_t ret = min_value + 
                (uint32_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline int32_t random(int32_t min_value, int32_t max_value)
    {
        int32_t ret = min_value + 
                (int32_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline float32_t random(float32_t min_value, float32_t max_value)
    {
        float32_t ret = min_value + 
                (float32_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline float64_t random(float64_t min_value, float64_t max_value)
    {
        float64_t ret = min_value + 
                (float64_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    static inline floatmax_t random(floatmax_t min_value, floatmax_t max_value)
    {
        floatmax_t ret = min_value + 
                (floatmax_t)((max_value - min_value+1)*(random()/(RAND_MAX+1.0)));
        ASSERT(ret >= min_value && ret <= max_value);
        return ret;
    }
    
    
    template<class T>
    static inline void swap(T &a, T &b)
    {
        register T c = a;
        a = b;
        b = c;
    }
    
    template<class T>
    static void qsort(T *output, int32_t size)
    {    
        if(size == 1)
            return;
        
        if(size == 2)
        {
            if(output[0] > output[1])
                CMath::swap(output[0], output[1]);
            return;
        }
        
        T split = output[size/2];
        int32_t left = 0;
        int32_t right = size-1;
        while(left <= right)
        {
            while(output[left] < split)
                left++;
            while(output[right] > split)
                right--;
            
            if(left <= right)
            {
                CMath::swap(output[left], output[right]);
                left++;
                right--;
            }
            
            if(right > 0)
                qsort(output, right+1);
            
            if(left < size-1)
                qsort(output+left, size-left);
        }
    }
    
    template<class T>
    static inline T max(T a, T b)
    {
        return (a <= b) ? b : a;
    }
    
    template<class T>
    static inline T min(T a, T b)
    {
        return (a <=b)? a : b;
    }
    
    template<class T>
    static inline T sign(T a)
    {
        if(a == 0)
            return 0;
        else return (a<0)? -1 : 1;
    }
    
    template<class T>
    static T abs(T a)
    {
        // why not return (a>=0)?a:(-a);
        if(a == 0)
            return 0;
        else if(a > 0)
            return a;
        else
            return -a;
    }
    
private:

};

}

#endif	/* MATH_MATH_H */

