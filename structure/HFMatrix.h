/* 
 * File:   HFMatrix.h
 * Author: zhf
 *
 * Created on 2013年5月25日, 上午12:18
 */

#ifndef STRUCTURE_HFMATRIX_H
#define STRUCTURE_HFMATRIX_H

#include "HFReferenceData.h"

namespace hanfeng
{

template<class T> class HFMatrix : public HFReferenceData
{
public:
    HFMatrix();
    HFMatrix(bool ref_counting);
    HFMatrix(T *m, int32_t nrows, int32_t ncols, bool ref_counting=true);
    HFMatrix(int32_t nrows, int32_t ncols, bool ref_counting=true);
    HFMatrix(const HFMatrix &orig);
    virtual ~HFMatrix();
  
    void display_matrix();
    
    
    /** clone **/
    HFMatrix<T> clone();
    static T* clone_matrix(const T *matrix, int32_t nrows, int32_t ncols);
    
    static void transpose_matrix(T *&matrix, int32_t &nrows, int32_t &ncols);
    
#ifdef HAVE_LAPACK
    static void inverse(HFMatrix<float64_t> &matrix);
    
#endif

    static float64_t trace(float64_t *mat, int32_t nrows, int32_t ncols);
    
protected:
    virtual void init_data();
    virtual void copy_data(const HFReferenceData &that);
    virtual void free_data();
    
    
public:
    T *matrix;
    int32_t num_rows;
    int32_t num_cols;
};

}
#endif	/* STRUCTURE_HFMATRIX_H */

