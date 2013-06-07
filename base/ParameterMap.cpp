/* 
 * File:   ParameterMap.cpp
 * Author: zhf
 * 
 * Created on 2013年6月7日, 下午1:49
 */

#include "ParameterMap.h"
#include <string.h>

using namespace hanfeng;

HFParamInfo::HFParamInfo()
{
    name = NULL;
    ctype = (EContainerType) - 1;
    stype = (EStructType) - 1;
    ptype = (EPrimitiveType) - 1;
    
    param_version = -1;
}

HFParamInfo::HFParamInfo(const HFParamInfo &orig)
{
    name = orig.name ? strdup(orig.name) : NULL;
    
    ctype = orig.ctype;
    stype = orig.stype;
    ptype = orig.ptype;
    
    param_version = orig.param_version;
}

HFParamInfo::HFParamInfo(const char* name, EContainerType ctype, 
                        EStructType stype, EPrimitiveType ptype, 
                        int32_t param_version)
{
    name = name? strdup(name) : NULL;
    
    this->ctype = ctype;
    this->stype = stype;
    this->ptype = ptype;
    
    this->param_version = param_version;
}

HFParamInfo::HFParamInfo(const TParameter* param, int32_t param_version)
{
    // TODO
}

HFParamInfo::~HFParamInfo()
{
    HF_FREE(name);
}


ParameterMap::ParameterMap()
{
    
}

ParameterMap::~ParameterMap()
{
}

void ParameterMap::put(const HFParamInfo *key, const HFParamInfo *value)
{
    // TODO
}

void ParameterMap::finalize_map()
{
    // TODO
}