/* 
 * File:   ParameterMap.cpp
 * Author: zhf
 * 
 * Created on 2013年6月7日, 下午1:49
 */

#include "ParameterMap.h"
#include "Parameter.h"
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
    name = param->name ? strdup(param->name) : NULL;
    
    THFDataType type = param->datatype;
    ctype = type.ctype;
    stype = type.stype;
    ptype = type.ptype;
    
    this->param_version = param_version;
}

HFParamInfo::~HFParamInfo()
{
    HF_FREE(name);
}


bool HFParamInfo::operator ==(const HFParamInfo& that) const
{    
    if((!name && that.name) || (name && !that.name))
        return false;
    
    if(name && that.name && strcmp(name, that.name))
        return false;
    
    if(ctype != that.ctype)
        return false;
    
    if(stype != that.stype)
        return false;
    
    if(ptype != that.ptype)
        return false;
     
    if(param_version != that.param_version)
        return false;
    
    return true;
}

bool HFParamInfo::operator !=(const HFParamInfo& that) const
{
    return ! operator==(that);
}

bool HFParamInfo::operator <(const HFParamInfo& that) const
{
    // TODO operator <
}

bool HFParamInfo::operator >(const HFParamInfo& that) const
{
    // TODO operator >
}

bool HFParamInfo::is_empty() const
{
    return ctype < 0 && stype < 0 && ptype < 0 && !name;
}

char* HFParamInfo::to_string() const
{
    // TODO to_string
    return NULL;
}

ParameterMapElement::ParameterMapElement()
{
    key = NULL;
    values = NULL;
}

ParameterMapElement::ParameterMapElement(const HFParamInfo* key, 
                                DynArray<const HFParamInfo*>* values)
{
    this->key = key;
    this->values = values;
}

ParameterMapElement::~ParameterMapElement()
{
    // FIXME this is a bug in shogun
    if(key)
        delete key;
    
    if(values)
    {
        for(index_t i = 0; i < values->get_num_elements(); ++i)
            delete values->get_element(i);
        
        delete values;
    }
}

ParameterMap::ParameterMap()
{
    
}

ParameterMap::~ParameterMap()
{
}

void ParameterMap::put(const HFParamInfo *key, const HFParamInfo *value)
{
    if(key->param_version - value->param_version != 1)
    {
        if(!key->is_empty() && !value->is_empty())
        {
            char *k = key->to_string();
            char *v = value->to_string();
            
            HF_SERROR("Versions of parameter mappings from '%s' "
                     "to '%s' have to differ exactly one\n", k, v);
            
            HF_FREE(k);
            HF_FREE(v);
        }
    }
    
    DynArray<const HFParamInfo*> *values = new DynArray<const HFParamInfo*>();
    values->append_element(value);
    map_elements_.append_element(new ParameterMapElement(key, values));
    finalized_ = false;
}

void ParameterMap::finalize_map()
{
    // TODO finalize_map
}