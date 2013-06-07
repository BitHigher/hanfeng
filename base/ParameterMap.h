/* 
 * File:   ParameterMap.h
 * Author: zhf
 *
 * Created on 2013年6月7日, 下午1:49
 */

#ifndef PARAMETERMAP_H
#define PARAMETERMAP_H

#include "../structure/DynArray.h"
#include "../base/DataType.h"

namespace hanfeng
{

struct TParameter;
 
class HFParamInfo
{
public:
    HFParamInfo();
    HFParamInfo(const HFParamInfo &orig);
    
    HFParamInfo(const char *name, EContainerType ctype, EStructType stype,
                EPrimitiveType ptype, int32_t param_version);
   
    HFParamInfo(const TParameter *param, int32_t param_version);
    
    virtual ~HFParamInfo();
    
public:
    char *name;
    EContainerType ctype;
    EStructType stype;
    EPrimitiveType ptype;
    int32_t param_version;
};


class ParameterMapElement
{
    
};

class ParameterMap {
public:
    ParameterMap();
    virtual ~ParameterMap();
    
    void put(const HFParamInfo *key, const HFParamInfo *value);
    
    void finalize_map();
    void print_map();
    
private:

protected:
    DynArray<ParameterMapElement*> map_elements_;
    DynArray<ParameterMapElement*> multi_map_elements_;
    
    bool finalized_;
};

}

#endif	/* PARAMETERMAP_H */

