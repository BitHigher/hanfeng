/* 
 * File:   Parameter.cpp
 * Author: zhf
 * 
 * Created on 2013年6月6日, 下午9:17
 */

#include "Parameter.h"
#include "../io/HFIO.h"

using namespace hanfeng;

TParameter::TParameter(const THFDataType *datatype, void *parameter, 
                        const char *name, const char *description)
: datatype(*datatype)
{
    this->parameter = parameter;
    this->name = strdup(name);
    this->description = strdup(description);
    this->delete_data = false;
    this->was_allocated_from_scratch = false;
}

void TParameter::print(const char *prefix)
{
    string_t buf;
    datatype.to_string(buf, STRING_LEN);
    
    HF_SPRINT("\n%s\n%-35s %-24s :%s\n", prefix, 
            (!description || !description[0])?"(Parameter)" : description,
            name, buf);
    
    if(datatype.ptype == PT_HFOBJECT &&
        datatype.stype == ST_NONE &&
        datatype.ctype == CT_SCALAR &&
        *(CHFObject**)parameter != NULL)
    {
        char *p = new_prefix(prefix, name);
        (*(CHFObject**)parameter)->print_serializable(p);
        delete p;
    }
}

bool TParameter::is_valid()
{
    return datatype.get_num_elements() > 0;
}

char* TParameter::new_prefix(const char* s1, const char* s2)
{
    char *tmp = HF_MALLOC(char, strlen(s1) + strlen(s2) + 2);
    
    sprintf(tmp, "%s%s/", s1, s2);
    
    return tmp;
}

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}

void Parameter::print(const char *prefix)
{
    for(index_t i = 0; i < get_num_parameters(); ++i)
        params_.get_element(i)->print(prefix);
}

void Parameter::add_type(const THFDataType* type, void* param, 
                                const char* name, const char* description)
{
    ASSERT(name || name[0]);
    
    for(index_t i = 0; i < get_num_elements(); ++i)
    {
        if(!strcmp(params_.get_element(i)->name, name))
            HF_SERROR("FATAL: Parameter::add_type():"
                        "Double parameter '%s'\n", name);
    }
    
    params_.append_element(new TParameter(type, param, name, description));
}

void Parameter::add(bool* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_BOOL);
    add_type(&type, param, name, description);
}

void Parameter::add(char* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_CHAR);
    add_type(&type, param, name, description);
}

void Parameter::add(int8_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_INT8);
    add_type(&type, param, name, description);
}

void Parameter::add(int16_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_INT16);
    add_type(&type, param, name, description);
}

void Parameter::add(int32_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_INT32);
    add_type(&type, param, name, description);
}

void Parameter::add(int64_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_INT64);
    add_type(&type, param, name, description);
}

void Parameter::add(uint8_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_UINT8);
    add_type(&type, param, name, description);
}

void Parameter::add(uint16_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_UINT16);
    add_type(&type, param, name, description);
}

void Parameter::add(uint32_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_UINT32);
    add_type(&type, param, name, description);
}

void Parameter::add(uint64_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_UINT64);
    add_type(&type, param, name, description);
}

void Parameter::add(float32_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_FLOAT32);
    add_type(&type, param, name, description);
}

void Parameter::add(float64_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_FLOAT64);
    add_type(&type, param, name, description);
}

void Parameter::add(floatmax_t* param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_FLOATMAX);
    add_type(&type, param, name, description);
}

void Parameter::add(CHFObject** param, char* name, const char* description)
{
    THFDataType type(CT_SCALAR, ST_NONE, PT_HFOBJECT);
    add_type(&type, param, name, description);
}

void Parameter::add(HFVector<int32_t>* param, char* name, 
                        const char* description)
{
    THFDataType type(CT_HFVECTOR, ST_NONE, PT_INT32, &param->vlen);
    add_type(&type, param, name, description);
}