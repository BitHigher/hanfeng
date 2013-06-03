/* 
 * File:   Cache.h
 * Author: zhf
 *
 * Created on 2013年6月3日, 上午9:09
 */

#ifndef STRUCTURE_CACHE_H
#define STRUCTURE_CACHE_H

#include "../base/HFObject.h"

namespace hanfeng
{

template<class T> class CCache : public CHFObject 
{
    struct TEntry
    {
        int64_t usage_count;
        bool locked;
        T *obj;
    };
    
    
public:
    CCache() : CHFObject()
    {
        // TODO
    }
    
    CCache(const CCache& orig);
    virtual ~CCache();
    
    
    inline T* lock_entry(int64_t num)
    {
        // TODO
        return NULL;
    }
    
    T* set_entry(int64_t num)
    {
        // TODO
        return NULL;
    }
    
private:

};

}

#endif	/* STRUCTURE_CACHE_H */

