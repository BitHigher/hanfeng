/* 
 * File:   DynArray.h
 * Author: zhf
 *
 * Created on 2013年6月6日, 下午10:44
 */

#ifndef DYNARRAY_H
#define DYNARRAY_H

#include "../base/common.h"
#include "../io/HFIO.h"

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
    
    inline int32_t get_num_elements() const
    {
        return current_num_elements_;
    }
    
    inline T get_element(int32_t index) const
    {
        return array_[index];
    }
    
    inline bool resize_array(int32_t n, bool exact_resize = false)
    {
        int32_t new_num_elments = n;
        
        // TODO
        HF_SNOTIMPLEMENTED
    }
    
    inline bool set_element(T element, int32_t index)
    {
        if(index < 0)
            return false;
        else if(index < current_num_elements_)
        {
            array_[index] = element;
            return true;
        }
        else if(index < num_elements_)
        {
            array_[index] = element;
            current_num_elements_ = index+1;
            return true;
        }
        else
        {
            if(free_array_ && resize_array(index))
                return set_element(element, index);
            else
                return false;
        }
    }
    
    inline bool append_element(T element)
    {
        return set_element(element, current_num_elements_);
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

