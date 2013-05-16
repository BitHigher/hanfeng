/* 
 * File:   HFReferenceData.cpp
 * Author: zhf
 * 
 * Created on 2013年5月16日, 上午11:51
 */

#include "HFReferenceData.h"

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

using namespace hanfeng;

HFReferenceData::HFReferenceData(bool ref_counting):refcount_(NULL) 
{
    if(ref_counting)
    {
        refcount_ = new refcount_t;
        refcount_->rc = 0;
    }
    
    ref();
}

HFReferenceData::HFReferenceData(const HFReferenceData &orig)
:refcount_(orig.refcount_) 
{
    ref();
}

HFReferenceData::~HFReferenceData()
{
}

HFReferenceData& HFReferenceData::operator =(const HFReferenceData &orig)
{
    if(this == &orig)
        return *this;

    unref();
    copy_data(orig);
    copy_refcount(orig);
    ref();
    return *this;
}

int32_t HFReferenceData::ref_count()
{
    if(this->refcount_ == NULL)
        return -1;
    
#ifdef HAVE_PTHREAD
    // TODO get lock
#endif
    
    int32_t c = refcount_->rc;
    
#ifdef HAVE_PTHREAD
    // TODO release lock
#endif
    
    return c;
}

int32_t HFReferenceData::ref()
{
    if(this->refcount_ == NULL)
        return -1;
    
#ifdef HAVE_PTHREAD
    // TODO get lock
#endif
    
    int32_t c = ++(this->refcount_->rc);
    
#ifdef HAVE_PTHREAD
    // TODO release lock
#endif
    
    return c;
}

int32_t HFReferenceData::unref()
{
    if(this->refcount_ == NULL)
    {
        init_data();
        this->refcount_ = NULL;
        return -1;
    }
    
#ifdef HAVE_PTHREAD
    // TODO get lock
#endif 
    
    int32_t c = --(this->refcount_->rc);
    
#ifdef HAVE_PTHREAD
    // TODO release lock
#endif
    
    if(c < 0)
    {
        free_data();
        
#ifdef HAVE_PTHREAD
        // TODO desctroy lock
#endif
        // free refcount_
        
        this->refcount_ = NULL;
        return 0;
    }
}

void HFReferenceData::copy_refcount(const HFReferenceData &orig)
{    
    this->refcount_ = orig.refcount_;
}