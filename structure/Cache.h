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
    CCache()
    {
        // TODO HF_UNSTABLE
        
        cache_block = NULL;
        lookup_table = NULL;
        cache_table = NULL;
        cache_is_full = false;
        nr_cache_lines = 0;
        entry_size = 0;
    }
    
    CCache(int64_t cache_size, int64_t obj_size, int64_t num_entries)
    {
        // TODO CCache constructor
    }
    
    virtual ~CCache()
    {
        HF_FREE(cache_block);
        HF_FREE(lookup_table);
        HF_FREE(cache_table);
    }
    
    virtual const char* get_name() const {return "Cache";}
    
    inline bool is_cached(int64_t number)
    {
        return lookup_table && lookup_table[number].obj;
    }
    
    inline T* lock_entry(int64_t num)
    {
        if(lookup_table)
        {
            lookup_table[num].usage_count++;
            lookup_table[num].locked = true;
            return lookup_table[num].obj;
        }
        return NULL;
    }
    
    inline void unlock_entry(int64_t num)
    {
        if(lookup_table)
            lookup_table[num].locked = false;
    }
    
    T* set_entry(int64_t num)
    {
        // TODO set entry
        return NULL;
    }
    

protected:
    bool cache_is_full;
    int64_t entry_size;
    int64_t nr_cache_lines;
    TEntry *lookup_table;
    TEntry *cache_table;
    
    T *cache_block;
    
};

}

#endif	/* STRUCTURE_CACHE_H */

