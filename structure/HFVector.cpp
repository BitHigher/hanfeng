/* 
 * File:   HFVector.cpp
 * Author: zhf
 * 
 * Created on 2013年5月16日, 下午5:38
 */

#include "HFVector.h"
#include "../math/Math.h"
#include "../io/HFIO.h"
#include "../base/common.h"
#include "../math/lapack.h"

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
HFVector<T>::HFVector(int32_t len, bool ref_counting)
: HFReferenceData(ref_counting), vlen(len)
{
    vector = HF_MALLOC(T, len);
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
void HFVector<T>::display_vector(const char *name, const char *prefix) const
{
    /*
    std::cout << '[';
    for(int32_t i = 0; i < vlen-1; ++i)
        std::cout << vector[i] << ',';
    
    if(vlen > 0)
        std::cout << vector[vlen-1];
    
    std::cout << ']' << '\n';
     */
    
    display_vector(vector, vlen, name, prefix);
}

namespace hanfeng
{
template<>
void HFVector<bool>::display_vector(const bool* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i]?1:0, i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<char>::display_vector(const char* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%c%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<uint8_t>::display_vector(const uint8_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<uint16_t>::display_vector(const uint16_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<uint32_t>::display_vector(const uint32_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<uint64_t>::display_vector(const uint64_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<int8_t>::display_vector(const int8_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<int16_t>::display_vector(const int16_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<int32_t>::display_vector(const int32_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<int64_t>::display_vector(const int64_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%d%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<float32_t>::display_vector(const float32_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%g%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<float64_t>::display_vector(const float64_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%.18g%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFVector<floatmax_t>::display_vector(const floatmax_t* vector, int32_t n, 
                                const char *name, const char *prefix)
{
    ASSERT(n > 0);
    HF_SPRINT("%s%s=[", prefix, name);
    for(index_t i = 0; i < n; ++i)
        HF_SPRINT("%s%.36Lg%s", prefix, vector[i], i==n-1?"":",");
    HF_SPRINT("%s]\n", prefix);
}

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
    ASSERT(vector && x.vector);
    ASSERT(vlen == x.vlen);
    
    for(int32_t i = 0; i < vlen; ++i)
        vector[i] += x.vector[i];
}

template<class T>
HFVector<T> HFVector<T>::operator +(HFVector<T>& that)
{
    ASSERT(vector && that.vector);
    ASSERT(vlen == that.vlen);
    
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

template<class T>
float64_t HFVector<T>::dot(const float64_t* v1, const float64_t* v2, int32_t n)
{
    float64_t r = 0;
#ifdef HAVE_EIGEN3
    // TODO EIGEN3
#elif HAVE_LAPACK
    int32_t skip = 1;
    r = cblas_ddot(n, v1, skip, v2, skip);
#else
    for(index_t i = 0; i < n; ++i)
        r += v1[i] * v2[i];
#endif
    
    return r;
}

template<class T>
void HFVector<T>::range_fill(T start)
{
    range_fill_vector(vector, vlen, start);
}

template<class T>
void HFVector<T>::range_fill_vector(T* vec, int32_t len, T start)
{
    for(index_t i = 0; i < len; ++i)
        vec[i] = i+start;
}


template<class T>
void HFVector<T>::load(CFile* loader)
{
    ASSERT(loader);
    
    unref();
    
    HF_SET_LOCALE_C;
    loader->get_vector(vector, vlen);
    HF_RESET_LOCALE;
}

template<class T>
void HFVector<T>::save(CFile* saver)
{
    ASSERT(saver);
    
    HF_SET_LOCALE_C;
    saver->set_vector(vector, vlen);
    HF_RESET_LOCALE;
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