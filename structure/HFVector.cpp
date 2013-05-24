/* 
 * File:   HFVector.cpp
 * Author: zhf
 * 
 * Created on 2013年5月16日, 下午5:38
 */

#include "HFVector.h"
#include "../math/Math.h"
#include <iostream>

using namespace hanfeng;

template<class T>
HFVector<T>::HFVector(): HFReferenceData()
{
    init_data();
}

template<class T>
HFVector<T>::HFVector(const HFVector &orig): HFReferenceData(orig) 
{
    copy_data(orig);
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
    HF_FREE(vector);
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

template<class T>
void HFVector<T>::display_vector()
{
    std::cout << '[';
    for(int32_t i = 0; i < vlen-1; ++i)
        std::cout << vector[i] << ',';
    
    if(vlen > 0)
        std::cout << vector[vlen-1];
    
    std::cout << ']' << '\n';
}

template<class T>
T* HFVector<T>::clone_vector(const T* vec, int32_t len)
{
    T *result = HF_MALLOC(T, len);
    memcpy(result, vec, sizeof(T)*len);
    return result;
}

template<class T>
HFVector<T> HFVector<T>::clone() const
{
    return HFVector<T>(clone_vector(vector, vlen), vlen);
}

template<class T>
void HFVector<T>::qsort()
{
    CMath::qsort<T>(vector, vlen);
}

template<class T>
void HFVector<T>::add(const HFVector<T>& x)
{
    // TODO ASSERT(vecotr && x.vector)
    // TODO ASSERT(vlen == x.vlen)
    
    for(int32_t i = 0; i < vlen; ++i)
        vector[i] += x.vector[i];
}

template<class T>
HFVector<T> HFVector<T>::operator +(HFVector<T>& that)
{
    // TODO ASSERT(vecotr && x.vector)
    // TODO ASSERT(vlen == x.vlen)
    
    HFVector<T> result = clone();
    result.add(that);
    return result;
}

template<class T>
HFVector<T> HFVector<T>::operator +=(HFVector<T>& that)
{
    add(that);
    return *this;
}

/** supported types **/
template class HFVector<bool>;
template class HFVector<char>;

template class HFVector<int8_t>;
template class HFVector<uint8_t>;
template class HFVector<int16_t>;
template class HFVector<uint16_t>;
template class HFVector<int32_t>;
template class HFVector<uint32_t>;
template class HFVector<int64_t>;
template class HFVector<uint64_t>;

template class HFVector<float32_t>;
template class HFVector<float64_t>;
template class HFVector<floatmax_t>; 