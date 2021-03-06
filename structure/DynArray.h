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
#include "../math/Math.h"

namespace hanfeng
{

template<class T>
class DynArray
{
    friend class CDynamicObjectArray;
    
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
    
    
    inline int32_t set_granularity(int32_t g)
    {
        g = CMath::max(g, 128);
        this->resize_granularity_ = g;
        return g;
    }
    
    inline int32_t get_array_size() const
    {
        return num_elements_;
    }
    
    inline int32_t get_num_elements() const
    {
        return current_num_elements_;
    }
    
    inline T get_element(int32_t index) const
    {
        return array_[index];
    }
    
    inline T* get_element_ptr(int32_t index)
    {
        return &array_[index];
    }
    
    inline bool resize_array(int32_t n, bool exact_resize = false)
    {
        int32_t new_num_elements = n;
        
        if(!exact_resize)
            new_num_elements=((n/resize_granularity_)+1) * resize_granularity_;
        
        T *p;
        
        if(use_hf_mallocs_)
            p = HF_REALLOC(T, array_, num_elements_, new_num_elements);
        else
            p = (T*)realloc(array_, new_num_elements*sizeof(T));
        
        if(p || new_num_elements == 0)
        {
            array_ = p;
            
            if(n-1 < current_num_elements_-1)
                current_num_elements_ = n;
            
            num_elements_ = new_num_elements;
            return true;
        }
        else
            return false;
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
    
    inline bool delete_element(int32_t index)
    {
        if(index >= 0 && index < current_num_elements_)
        {
            for(index_t i = index; i < current_num_elements_-1; ++i)
                array_[i] = array_[i+1];
            
            current_num_elements_--;
            
            if(num_elements_ - current_num_elements_ - 1 > resize_granularity_)
                resize_array(current_num_elements_);
            
            return true;
        }
        
        return false;
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

