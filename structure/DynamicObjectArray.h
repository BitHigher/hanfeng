/* 
 * File:   DynamicObjectArray.h
 * Author: zhf
 *
 * Created on 2013年6月5日, 下午3:03
 */

#ifndef DYNAMICOBJECTARRAY_H
#define DYNAMICOBJECTARRAY_H

#include "../base/HFObject.h"
#include "../structure/DynArray.h"
#include "../base/Parameter.h"

namespace hanfeng
{

class CDynamicObjectArray : public CHFObject
{

public:
    CDynamicObjectArray()
    : CHFObject(), name_("Array")
    {
        dim1_size_ = 1;
        dim2_size_ = 1;
        dim3_size_ = 1;
        
        init();
    }
    
    CDynamicObjectArray(int32_t dim1, int32_t dim2=1, int32_t dim3=1)
    : CHFObject(), name_("Array")
    {
        dim1_size_ = dim1;
        dim2_size_ = dim2;
        dim3_size_ = dim3;
        
        init();
    }
    
    virtual ~CDynamicObjectArray(){unref_all();}
    
    virtual const char* get_name() const {return "DynamiacObjectArray";}
    
    inline int32_t set_granularity(int32_t g)
    {
        return array_.set_granularity(g);
    }
    
    inline int32_t get_array_size() const
    {
        return array_.get_array_size();
    }
    
    inline int32_t get_num_elements() const
    {
        return array_.get_num_elements();
    }
    
    inline CHFObject* get_element(int32_t index) const
    {
        CHFObject *ele = array_.get_element(index);
        HF_REF(ele);
        return ele;
    }
    
    inline bool append_element(CHFObject *e)
    {
        bool success = array_.append_element(e);
        if(success)
            HF_REF(e);
        
        return success;
    }
    
    inline bool delete_element(int32_t index)
    {
        CHFObject *ele = array_.get_element(index);
        HF_UNREF(ele);
        array_.set_element(NULL, index);
        
        return array_.delete_element(index);
    }
    
private:
    virtual void init()
    {
        HF_ADD_VECTOR(&array_.array_, &array_.current_num_elements_, "array", 
                        "Memory for dynamic array", MS_NOT_AVAILABLE);
        
        HF_ADD(&array_.num_elements_, "num_elements",
                "Nnumber of ELements", MS_NOT_AVAILABLE);
        
        HF_ADD(&array_.resize_granularity_, "resize_granularity",
                "shrink/grow step size", MS_NOT_AVAILABLE);
        
        HF_ADD(&array_.use_hf_mallocs_, "use_hf_mallocs",  
                "whether HF_MALLOC or malloc should be used", MS_NOT_AVAILABLE);
        
        HF_ADD(&array_.free_array_, "free_array",
                "whether array must be freed", MS_NOT_AVAILABLE);
    }
    
    inline void unref_all()
    {
        for(index_t i = 0; i < array_.get_num_elements(); ++i)
        {
            HF_UNREF(*array_.get_element_ptr(i));
        }
    }
    
private:
    DynArray<CHFObject*> array_;
    
    int32_t dim1_size_;
    int32_t dim2_size_;
    int32_t dim3_size_;
    
    const char* name_;
};

}

#endif	/* DYNAMICOBJECTARRAY_H */

