/* 
 * File:   DynArray.h
 * Author: zhf
 *
 * Created on 2013年6月6日, 下午10:44
 */

#ifndef DYNARRAY_H
#define DYNARRAY_H

#include "../base/common.h"

namespace hanfeng
{

template<class T>
class DynArray
{
public:
    DynArray(int32_t resize_granularity=128, bool tracable=true)
    {
        resize_granularity_ = resize_granularity;
        free_array_ = true;
        use_hf_mallocs_ = tracable;
        
        if(use_hf_mallocs_)
            array_ = HF_MALLOC(T, resize_granularity);
        else
            array_ = (T*) malloc(size_t(resize_granularity)*sizeof(T));
        
        num_elements_ = resize_granularity;
        current_num_elements_ = 0;
    }
    
    virtual ~DynArray()
    {
        if(array_ && free_array_)
        {
            if(use_hf_mallocs_)
                HF_FREE(array_);
            else
                free(array_);
        }
    }

private:

protected:
    int32_t resize_granularity_;
    T *array_;
    
    int32_t num_elements_;
    int32_t current_num_elements_;
    bool use_hf_mallocs_;
    bool free_array_;
};

}

#endif	/* DYNARRAY_H */

