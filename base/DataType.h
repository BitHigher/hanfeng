/* 
 * File:   DataType.h
 * Author: zhf
 *
 * Created on 2013年6月7日, 下午3:09
 */

#ifndef DATATYPE_H
#define DATATYPE_H

#include "../base/common.h"

namespace hanfeng
{

#define PT_NOT_GENERIC PT_HFOBJECT
    
enum EContainerType
{
    CT_SCALAR = 0,
    CT_VECTOR = 1,
    CT_MATRIX = 2,
    CT_NDARRAY = 3,
    
    CT_HFVECTOR = 4,
    CT_HFMATRIX = 5
};

enum EStructType
{
    ST_NONE = 0,
    ST_STRING = 1,
    ST_SPARSE = 2
};

enum EPrimitiveType
{
    PT_BOOL = 0,
    PT_CHAR = 1,
    PT_INT8 = 2,
    PT_UINT8 = 3,
    PT_INT16 = 4,
    PT_UINT16 = 5,
    PT_INT32 = 6,
    PT_UINT32 = 7,
    PT_INT64 = 8,
    PT_UINT64 = 9,
    PT_FLOAT32 = 10,
    PT_FLOAT64 = 11,
    PT_FLOATMAX = 12,
    PT_HFOBJECT = 13
};
    
struct THFDataType {
    EContainerType ctype;
    EStructType stype;
    EPrimitiveType ptype;
    
    index_t *length_x;
    index_t *length_y;
    
    explicit THFDataType(EContainerType ctype, 
                         EStructType stype,
                         EPrimitiveType ptype);
    
    explicit THFDataType(EContainerType ctype,
                         EStructType stype,
                         EPrimitiveType ptype,
                         index_t *length);
    
    explicit THFDataType(EContainerType ctype,
                         EStructType stype,
                         EPrimitiveType ptype,
                         index_t *length_y,
                         index_t *length_x);
    
    virtual ~THFDataType();
    
    void to_string(char *dest, size_t n) const;
    
    
    static void stype_to_string(char *dest, EStructType stype,
                                EPrimitiveType ptype, size_t n);
    
    static void ptype_to_string(char *dest, EPrimitiveType ptype, size_t n);
    
    size_t get_size();
    int64_t get_num_elements();

};

}

#endif	/* DATATYPE_H */

