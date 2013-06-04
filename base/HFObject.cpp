/* 
 * File:   HFObject.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午1:45
 */

#include "HFObject.h"

namespace hanfeng
{
    extern HFIO *hf_io;
    extern Parallel *hf_parallel;
    extern Version *hf_version;
}

using namespace hanfeng;

CHFObject::CHFObject()
{
    init();
    set_global_objects();
    
    // TODO HF_GCDEBUG()
}

CHFObject::CHFObject(const CHFObject &orig)
: io(orig.io), parallel(orig.parallel)
{
    init(); // TODO here may exist bug !!!  
    set_global_objects();
}

CHFObject::~CHFObject()
{
    // TODO HF_GCDEBUG()
    
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK_DESTROY(&ref_lock_);
#endif
    
    unset_global_objects();
    
    // TODO delete objects
}

void CHFObject::init()
{
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK_INIT(&ref_lock_);
#endif
    
    refcount_ = 0;
    io = NULL;
    parallel = NULL;
    version = NULL;
    
    // TODO
}

void CHFObject::set_global_objects()
{
    if(!hf_io || !hf_parallel || !hf_version)
    {
        fprintf(stderr, "call init_hanfeng() before using this libaray, dying.");
        exit(1);
    }
    
    HF_REF(hf_io);
    HF_REF(hf_parallel);
    HF_REF(hf_version);
    
    io = hf_io;
    parallel = hf_parallel;
    version = hf_version;
}

void CHFObject::unset_global_objects()
{
    HF_UNREF(version);
    HF_UNREF(parallel);
    HF_UNREF(io);
}

void CHFObject::set_global_io(HFIO *io)
{
    HF_UNREF(hf_io);
    hf_io = io;
    HF_REF(hf_io);
}

void CHFObject::set_global_parallel(Parallel *parallel)
{
    HF_UNREF(hf_parallel);
    hf_parallel = parallel;
    HF_REF(hf_parallel);
}

void CHFObject::set_global_version(Version *version)
{
    HF_UNREF(hf_version);
    hf_version = version;
    HF_REF(hf_version);
}

HFIO* CHFObject::get_global_io()
{
    HF_REF(hf_io);
    return hf_io;
}

Parallel* CHFObject::get_global_parallel()
{
    HF_REF(hf_parallel);
    return hf_parallel;
}

Version* CHFObject::get_global_version()
{
    HF_REF(hf_version);
    return hf_version;
}

#ifdef USE_REFERENCE_COUNTING
int32_t CHFObject::ref_count()
{
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK(&ref_lock_);
#endif
    int32_t count = refcount_;
    
#ifdef HAVE_PTHREAD
    PTHREAD_UNLOCK(&ref_lock_);
#endif
    
    // TODO HF_GCDEBUG
    return count;
}

int32_t CHFObject::ref()
{
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK(&ref_lock_);
#endif
    ++refcount_;
    int32_t count = refcount_;
    
#ifdef HAVE_PTHREAD
    PTHREAD_UNLOCK(&ref_lock_);
#endif
    
    // TODO HF_GCDEBUG
    return count;
}

int32_t CHFObject::unref()
{
    #ifdef HAVE_PTHREAD
    PTHREAD_LOCK(&ref_lock_);
#endif
    if(refcount_ == 0 || --refcount_ == 0)
    {
#ifdef HAVE_PTHREAD
        PTHREAD_UNLOCK(&ref_lock_);
#endif
        delete this;
        return 0;
    }
    else
    {
        int32_t count = refcount_;
#ifdef HAVE_PTHREAD
        PTHREAD_UNLOCK(&ref_lock_);
#endif
        return count;
    }
}
#endif /* USE_REFERENCE_COUNTING */