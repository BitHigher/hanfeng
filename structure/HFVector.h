/* 
 * File:   HFVector.h
 * Author: zhf
 *
 * Created on 2013年5月16日, 下午5:38
 */

#ifndef STRUCTURE_HFVECTOR_H
#define STRUCTURE_HFVECTOR_H

#include "HFReferenceData.h"
#include "../base/common.h"
#include "../io/File.h"

namespace hanfeng
{

template<class T> class HFSparseVector;
    
template<class T> class HFVector : public HFReferenceData
{
public:
    HFVector();
    HFVector(const HFVector &orig);  
    HFVector(T *v, int32_t len, bool ref_counting=true);
    HFVector(int32_t len, bool ref_counting=true);
    
    virtual ~HFVector();
    
    /** override virtual functions **/
    void init_data();
    void free_data();
    void copy_data(const HFReferenceData &orig);
    
    /** base operations **/
    inline int32_t size() const {return vlen;}
    operator T*(){return vector;}
    HFVector<T> get(){return *this;}
    
    inline const T& operator[](index_t index) const
    {
        return vector[index];
    }
    
    inline T& operator[](index_t index)
    {
        return vector[index];
    }
    
    void set_const(const T &const_elem);
    void zero();
    void random(T min_value, T max_value);
    
    void display_vector(const char *name="vector", const char *prefix="") const;
    static void display_vector(const T *vector, int32_t n, 
                        const char *name="vector", const char *prefix="");
    
    static void display_vector(const HFVector<T>, const char *name="vector",
                                        const char *prefix="");
    
    /** calculations **/
    static inline T sum(T *vec, int32_t len)
    {
        T result = 0;
        for(int32_t i = 0; i < len; ++i)
            result += vec[i];
        
        return result;
    }
    
    static inline T sum(HFVector<T> &vec)
    {
        return sum(vec.vector, vec.vlen);
    }
    
    inline T sum()
    {
        return sum(this->vector, this->vlen);
    }
    
    /** static functions **/
    static void random_vector(T *vec, int32_t len, T min_value, T max_value);
    
    HFVector<T> clone() const;
    static T* clone_vector(const T *vec, int32_t len);
    
    void qsort();
    void add(const HFVector<T> &x);
    HFVector<T> operator+ (HFVector<T> &that);
    HFVector<T> operator+= (HFVector<T> &that);
    
    static inline T product(T *vec, int32_t len)
    {
        T result = 1;
        for(int32_t i = 0; i < len; ++i)
        {
            result *= vec[i];
        }
        return result;
    }
    
    inline T product()
    {
        return product(vector, vlen);
    }
    
    static float64_t dot(const float64_t *v1, const float64_t *v2, int32_t n);
    
    void load(CFile *loader);
    void save(CFile *saver);
public:
    T *vector;
    int32_t vlen;
};



}
#endif	/* STRUCTURE_HFVECTOR_H */

