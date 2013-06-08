/* 
 * File:   DataType.cpp
 * Author: zhf
 * 
 * Created on 2013年6月7日, 下午3:09
 */

#include "DataType.h"
#include "../io/HFIO.h"
#include <string.h>

using namespace hanfeng;

THFDataType::THFDataType(EContainerType ctype, EStructType stype, 
                        EPrimitiveType ptype)
{
    this->ctype = ctype;
    this->stype = stype;
    this->ptype = ptype;
    
    length_x = length_y = NULL;
}

THFDataType::THFDataType(EContainerType ctype, EStructType stype, 
                                EPrimitiveType ptype, index_t* length)
{
    this->ctype = ctype;
    this->stype = stype;
    this->ptype = ptype;
    
    length_y = length;
    length_x = NULL;
}

THFDataType::THFDataType(EContainerType ctype, EStructType stype, 
                EPrimitiveType ptype, index_t* length_y, index_t* length_x)
{
    this->ctype = ctype;
    this->stype = stype;
    this->ptype = ptype;
    
    this->length_y = length_y;
    this->length_x = length_x;
}

THFDataType::~THFDataType()
{
}

void THFDataType::to_string(char* dest, size_t n) const
{
    char *p = dest;
    
    switch(ctype)
    {
        case CT_SCALAR:
            strncpy(p, "", n);
            break;
        case CT_VECTOR:
            strncpy(p, "Vector<", n);
            break;
        case CT_MATRIX:
            strncpy(p, "Matrix<", n);
            break;
        case CT_HFVECTOR:
            strncpy(p, "HFVector<", n);
            break;
        case CT_HFMATRIX:
            strncpy(p, "HFMatrix<", n);
            break;
        case CT_NDARRAY:
            strncpy(p, "N-Dimensional Array<", n);
            break;
    }
    
    size_t np = strlen(p);
    stype_to_string(p+np, stype, ptype, n-np-2);
    
    switch(ctype)
    {
        case CT_SCALAR:
            break;
        case CT_VECTOR:
        case CT_MATRIX:
        case CT_HFVECTOR:
        case CT_HFMATRIX:
        case CT_NDARRAY:
            strcat(p, ">");
            break;
    }
}

void THFDataType::stype_to_string(char* dest, EStructType stype, 
                                        EPrimitiveType ptype, size_t n)
{
    char *p = dest;
    
    switch(stype)
    {
        case ST_NONE:
            strncpy(p, "", n);
            break;
        case ST_STRING:
            strncpy(p, "String<", n);
            break;
        case ST_SPARSE:
            strncpy(p, "Sparse<", n);
            break;
    }
    
    size_t np = strlen(p);
    ptype_to_string(p+np, ptype, n-np-2);
    
    switch(stype)
    {
        case ST_NONE:
            break;
        case ST_STRING:
        case ST_SPARSE:
            strcat(p, ">");
            break;
    }
}

void THFDataType::ptype_to_string(char* dest, EPrimitiveType ptype, size_t n)
{
    char *p = dest;
    
    switch(ptype)
    {
        case PT_BOOL: strncpy(p, "bool", n); break;
        case PT_CHAR: strncpy(p, "char", n); break;
        case PT_INT8: strncpy(p, "int8", n); break;
        case PT_UINT8: strncpy(p, "uint8", n); break;
        case PT_INT16: strncpy(p, "int16", n); break;
        case PT_UINT16: strncpy(p, "uint16", n); break;
        case PT_INT32: strncpy(p, "int32", n); break;
        case PT_UINT32: strncpy(p, "uint32", n); break;
        case PT_INT64: strncpy(p, "int64", n); break;
        case PT_UINT64: strncpy(p, "uint64", n); break;
        case PT_FLOAT32: strncpy(p, "float32", n); break;
        case PT_FLOAT64: strncpy(p, "float64", n); break;
        case PT_FLOATMAX: strncpy(p, "floatmax", n); break;
        case PT_HFOBJECT: strncpy(p, "HFSeriaizable*", n); break;
    }
}

int64_t THFDataType::get_num_elements()
{
    switch(ctype)
    {
        case CT_SCALAR:
            return 1;
        case CT_VECTOR:
        case CT_HFVECTOR:
            return *length_y;
        case CT_MATRIX:
        case CT_HFMATRIX:
            return (*length_y)*(*length_x);
        case CT_NDARRAY:
            HF_SNOTIMPLEMENTED
        default:
            HF_SERROR("THFDataType::get_num_elements():"
                    "unknown container type: %d\n", ctype);
    }
    
    return 0;
}

