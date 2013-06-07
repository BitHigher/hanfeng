/* 
 * File:   Parameter.h
 * Author: zhf
 *
 * Created on 2013年6月6日, 下午9:17
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include "../base/common.h"
#include "../structure/DynArray.h"
#include "../base/HFObject.h"
#include "../structure/HFVector.h"
#include "../structure/HFMatrix.h"
#include "../base/DataType.h"

namespace hanfeng
{

struct TParameter
{
    explicit TParameter(const THFDataType *datatype, void *parameter,
                        const char *name, const char *description);
    
    ~TParameter();
    
    void print(const char *prefix);
    
    bool is_valid();
    
    
    THFDataType datatype;
    void *parameter;
    char *name;
    char *description;
    bool delete_data;
    bool was_allocated_from_scratch;
    
private:
    char* new_prefix(const char *s1, const char *s2);
    void delete_cont();
    void new_cont(HFVector<index_t> dims);
};
    
class Parameter
{
public:
    explicit Parameter();
    virtual ~Parameter();

    virtual void print(const char *prefix="");

    virtual int32_t get_num_parameters()
    {
        return params_.get_num_elements();
    }
    
    void set_from_parameters(Parameter *params);
    void add_parameters(Parameter *params);
    bool contains_paramter(const char *name);
    
    virtual int32_t get_num_elements()
    {
        return params_.get_num_elements();
    }
    
    inline TParameter* get_parameter(int32_t idx)
    {
        return params_.get_element(idx);
    }
    
    inline TParameter* get_parameter(const char *name)
    {
        TParameter *result = NULL;
        
        for(index_t i = 0; i < params_.get_num_elements(); ++i)
        {
            result = params_.get_element(i);
            if(!strcmp(name, result->name))
                break;
            else
                result = NULL;
        }
        
        return result;
    }
    
    void add(bool *param, char *name, const char *description="");
    void add(char *param, char *name, const char *description="");
    void add(int8_t *param, char *name, const char *description="");
    void add(int16_t *param, char *name, const char *description="");
    void add(int32_t *param, char *name, const char *description="");
    void add(int64_t *param, char *name, const char *description="");
    void add(uint8_t *param, char *name, const char *description="");
    void add(uint16_t *param, char *name, const char *description="");
    void add(uint32_t *param, char *name, const char *description="");
    void add(uint64_t *param, char *name, const char *description="");
    void add(float32_t *param, char *name, const char *description="");
    void add(float64_t *param, char *name, const char *description="");
    void add(floatmax_t *param, char *name, const char *description="");
    
    void add(HFVector<int32_t> *param, char *name, const char *description="");
    
    void add(CHFObject **param, char *name, const char *description="");
    
protected:
    virtual void add_type(const THFDataType *type, void *param, 
                          const char *name, const char *description);
    
protected:
    DynArray<TParameter*> params_;

};


}

#endif	/* PARAMETER_H */

