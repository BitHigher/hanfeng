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
        refcount_ = HF_CALLOC(refcount_t, 1);
        
#ifdef HAVE_PTHREAD
        //PTHREAD_LOCK_INIT(&refcount_->lock);
#endif
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
    PTHREAD_LOCK(&refcount_->lock);
#endif
    
    int32_t c = refcount_->rc;
    
#ifdef HAVE_PTHREAD
    PTHREAD_UNLOCK(&refcount_->lock);
#endif
    
    return c;
}

int32_t HFReferenceData::ref()
{
    if(this->refcount_ == NULL)
        return -1;
    
#ifdef HAVE_PTHREAD
    PTHREAD_LOCK(&refcount_->lock);
#endif
    
    int32_t c = ++(this->refcount_->rc);
    
#ifdef HAVE_PTHREAD
    PTHREAD_UNLOCK(&refcount_->lock);
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
    PTHREAD_LOCK(&refcount_->lock);
#endif 
    
    if(this->refcount_->rc == 0 || --(this->refcount_->rc) == 0)
    {
#ifdef HAVE_PTHREAD
        PTHREAD_UNLOCK(&refcount_->lock);
        PTHREAD_LOCK_DESTROY(&refcount_->lock);
#endif
        free_data();
        HF_FREE(this->refcount_);
        this->refcount_ = NULL;
        return 0;
    }else
    {
#ifdef HAVE_PTHREAD
        PTHREAD_UNLOCK(&refcount_->lock);
#endif
        return this->refcount_->rc;
    }
 }

void HFReferenceData::copy_refcount(const HFReferenceData &orig)
{    
    this->refcount_ = orig.refcount_;
}