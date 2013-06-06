/* 
 * File:   DynamicObjectArray.h
 * Author: zhf
 *
 * Created on 2013年6月5日, 下午3:03
 */

#ifndef DYNAMICOBJECTARRAY_H
#define DYNAMICOBJECTARRAY_H

#include "../base/HFObject.h"

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
    
    inline int32_t get_num_elements() const
    {
        // TODO
        return 0;
    }
    
    inline CHFObject* get_element(int32_t index) const
    {
        // TODO
        return NULL;
    }
    
    inline bool append_element(CHFObject *e)
    {
        // TODO
        return false;
    }
    
    inline bool delete_element(int32_t index)
    {
        // TODO
        return false;
    }
    
private:
    virtual void init()
    {
        // TODO add parameters
    }
    
    inline void unref_all()
    {
        // TODO
        
    }
    
private:
    // TODO DynArray<>
    
    int32_t dim1_size_;
    int32_t dim2_size_;
    int32_t dim3_size_;
    
    const char* name_;
};

}

#endif	/* DYNAMICOBJECTARRAY_H */

