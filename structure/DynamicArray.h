/* 
 * File:   DynamicArray.h
 * Author: zhf
 *
 * Created on 2013年6月6日, 下午10:40
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "../base/common.h"
#include "../base/HFObject.h"
#include "../structure/DynArray.h"

namespace hanfeng
{

template<class T>
class CDynamicArray : public CHFObject
{
public:
    CDynamicArray()
    : array_(), name_("Array")
    {
        dim1_size_ = 1;
        dim2_size_ = 1;
        dim3_size_ = 1;
        
        init();
    }
            
    CDynamicArray(int32_t dim1_size, int32_t dim2_size=1, dim3_size=1)
    : array_(dim1_size*dim2_size*dim3_size), name_("Array")
    {
        dim1_size_ = dim1_size;
        dim2_size_ = dim2_size;
        dim3_size_ = dim3_size;
        
        init();
    }
    
    CDynamicArray(const CDynamicArray& orig);
    virtual ~CDynamicArray(){}
    
    virtual const char* get_name() const {return "DynamicArray"; }

    inline int32_t set_granularity(int32_t g)
    {
        // TODO
    }
    
    inline int32_t get_array_size()
    {
        // TODO
    }
    
    inline void get_array_size(int32_t &dim1, int32_t &dim2)
    {
        dim1 = dim1_size_;
        dim2 = dim2_size_;
    }
    
    inline void get_array_size(int32_t &dim1, int32_t &dim2, int32_t &dim3)
    {
        dim1 = dim1_size_;
        dim2 = dim2_size_;
        dim3 = dim3_size_;
    }
    
    inline int32_t get_dim1() {return dim1_size_; }
    inline int32_t get_dim2() {return dim2_size_; }
    inline int32_t get_dim3() {return dim3_size_; }
    
private:
    void init()
    {
        // TODO
    }
    
protected:
    DynArray<T> array_;
    
    int32_t dim1_size_;
    int32_t dim2_size_;
    int32_t dim3_size_;
    const char *name_;

};

}

#endif	/* DYNAMICARRAY_H */

