/* 
 * File:   DataType.h
 * Author: zhf
 *
 * Created on 2013年6月7日, 下午3:09
 */

#ifndef DATATYPE_H
#define DATATYPE_H

namespace hanfeng
{

enum EContainerType
{
    CT_SCALAR = 0,
    CT_VECTOR = 1,
    CT_MATRIX = 2
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
    PT_INT8 = 2
};
    
class THFDataType {
public:
    THFDataType();
    THFDataType(const THFDataType &orig);
    virtual ~THFDataType();
private:

};

}

#endif	/* DATATYPE_H */

