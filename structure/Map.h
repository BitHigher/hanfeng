/* 
 * File:   Map.h
 * Author: zhf
 *
 * Created on 2013年6月7日, 下午8:19
 */

#ifndef MAP_H
#define MAP_H

#include "../base/HFObject.h"
#include "../base/Parallel.h"

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

namespace hanfeng
{

template<class K, class T>
class CMap : public CHFObject
{
public:
    CMap(int32_t size=41, int32_t reserved=128, bool tracable=true)
    {
        hash_size_ = size;
        free_index_ = 0;
        num_elements_ = 0;
        use_hf_mallocs_ = tracable;
        
        // TODO
    }
    
    CMap(const CMap& orig);
    virtual ~CMap();

protected:
    bool use_hf_mallocs_;
    
    int32_t hash_size_;
    int32_t free_index_;
    int32_t num_elements_;
    
    // TODO
    
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK_T lock_;
#endif

};

}

#endif	/* MAP_H */

