/* 
 * File:   DenseFeatures.cpp
 * Author: zhf
 * 
 * Created on 2013年6月3日, 上午12:26
 */

#include "DenseFeatures.h"
#include "../base/common.h"

using namespace hanfeng;

template<class T>
CDenseFeatures<T>::CDenseFeatures()
{
}

template<class T>
CDenseFeatures<T>::~CDenseFeatures() {
}


namespace hanfeng
{

#define GET_FEATURE_TYPE(f_type, hf_type) \
template<> EFeatureType CDenseFeatures<hf_type>::get_feature_type() const \
{ \
    return f_type; \
}

GET_FEATURE_TYPE(F_BOOL, bool)
GET_FEATURE_TYPE(F_DREAL, float64_t)

#undef GET_FEATURE_TYPE

}

template class CDenseFeatures<float64_t>;