/* 
 * File:   HFObject.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午1:45
 */

#ifndef BASE_HFOBJECT_H
#define BASE_HFOBJECT_H

#include "../io/HFIO.h"
#include "../base/Parallel.h"
#include "../base/Version.h"

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

namespace hanfeng
{
    
class Parameter;
class ParameterMap;

#ifdef USE_REFERENCE_COUNTING
#define HF_REF(x) {if(x) (x)->ref();}
#define HF_UNREF(x) {if(x){if((x)->unref() == 0) (x) = NULL;}}
#define HF_UNREF_NO_NULL(x) {if(x) (x)->unref();}
#else
#define HF_REF(x)
#define HF_UNREF(x)
#define HF_UNREF_NO_NULL(x)
#endif

/* add parameters */
#define HF_ADD(param, name, description, ms_available) { \
        parameters->add(param, name, description); \
           if(ms_available) \
               model_selection_parameters->add(param, name, description); \
        }
    
/* model selection availability */    
enum
{
    MS_NOT_AVAILABLE = 0,
    MS_AVAILABLE
};
    
    
class CHFObject {
public:
    CHFObject();
    CHFObject(const CHFObject &orig);
    virtual ~CHFObject();
    
#ifdef USE_REFERENCE_COUNTING
    int32_t ref();
    int32_t ref_count();
    int32_t unref();
#endif
    
    virtual CHFObject* shallow_copy() const
    {
        HF_NOTIMPLEMENTED
        return NULL;
    }
    
    virtual CHFObject* deep_copy() const
    {
        HF_NOTIMPLEMENTED
        return NULL;
    }
    
    virtual const char* get_name() const = 0;
    
    
    void set_global_io(HFIO *io);
    HFIO* get_global_io();
    void set_global_parallel(Parallel *parallel);
    Parallel* get_global_parallel();
    void set_global_version(Version *version);
    Version* get_global_version();
    
    virtual void print_serializable(const char *prefix="");
    
private:
    void set_global_objects();
    void unset_global_objects();
    void init();
    
public:
    HFIO *io;
    Parallel *parallel;
    Version *version;
    Parameter *parameters;
    Parameter *model_selection_parameters;
    
    ParameterMap *parameter_map;

private:
    int32_t refcount_;
    
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK_T ref_lock_;
#endif
};

}

#endif	/* BASE_HFOBJECT_H */

