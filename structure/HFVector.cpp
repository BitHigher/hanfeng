/* 
 * File:   HFVector.cpp
 * Author: zhf
 * 
 * Created on 2013年5月16日, 下午5:38
 */

#include "HFVector.h"
#include "../math/Math.h"

using namespace hanfeng;

template<class T>
HFVector<T>::HFVector() 
{
    init_data();
}

template<class T>
HFVector<T>::HFVector(const HFVector &orig) 
{
}

template<class T>
HFVector<T>::HFVector(T* v, int32_t len, bool ref_counting)
: HFReferenceData(ref_counting), vector(v), vlen(len)
{ 
}

template<class T>
HFVector<T>::~HFVector()
{
    unref();
}

template<class T>
void HFVector<T>::init_data()
{
    vector = NULL;
    vlen = 0;
}

template<class T>
void HFVector<T>::free_data()
{
    // TODO free
    vector = NULL;
    vlen = 0;
}

template<class T>
void HFVector<T>::copy_data(const HFReferenceData &orig)
{
    vector = ((HFVector *)(&orig))->vector;
    vlen = ((HFVector *)(&orig))->vlen;
}

template<class T>
void HFVector<T>::set_const(const T &const_elem)
{
    for(int32_t i = 0; i < this->vlen; ++i)
        vector[i] = const_elem;
}

template<class T>
void HFVector<T>::zero()
{
    if(vector && vlen)
        set_const(0);
}

template<class T>
void HFVector<T>::random(T min_value, T max_value)
{
    random_vector(vector, vlen, min_value, max_value);
}

template<class T>
void HFVector<T>::random_vector(T* vec, int32_t len, T min_value, T max_value)
{
    for(int32_t i = 0; i < len; ++i)
        vec[i] = CMath::random(min_value, max_value);
}

template class HFVector<int32_t>;
template class HFVector<bool>;