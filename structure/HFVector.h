/* 
 * File:   HFVector.h
 * Author: zhf
 *
 * Created on 2013年5月16日, 下午5:38
 */

#ifndef STRUCTURE_HFVECTOR_H
#define	STRUCTURE_HFVECTOR_H

#include "HFReferenceData.h"
#include <cstdlib>

namespace hanfeng
{

template<class T> class HFSparseVector;
class CFile;
    
template<class T> class HFVector : public HFReferenceData
{
public:
    HFVector();
    HFVector(const HFVector &orig);  
    HFVector(T *v, int32_t len, bool ref_counting=true);
  
    virtual ~HFVector();
    
    /** override virtual functions **/
    void init_data();
    void free_data();
    void copy_data(const HFReferenceData &orig);
    
    inline int32_t size() const {return vlen;}
    operator T*(){return vector;}
    void set_const(const T &const_elem);
    void zero();
    void random(T min_value, T max_value);
    
    
    /** static functions **/
    static void random_vector(T *vec, int32_t len, T min_value, T max_value);
    
public:
    T *vector;
    int32_t vlen;
};



}
#endif	/* STRUCTURE_HFVECTOR_H */

