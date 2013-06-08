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

template<class T> class HFVector;
class CFile;
    
template<class T> class HFMatrix : public HFReferenceData
{
public:
    HFMatrix();
    HFMatrix(bool ref_counting);
    HFMatrix(T *m, int32_t nrows, int32_t ncols, bool ref_counting=true);
    HFMatrix(int32_t nrows, int32_t ncols, bool ref_counting=true);
    HFMatrix(const HFMatrix &orig);
    virtual ~HFMatrix();
    
    /** read only access **/
    inline const T& operator()(index_t i_row, index_t i_col) const
    {
        return matrix[i_col*num_rows+i_row];
    }
    
    inline const T& operator[](index_t index) const
    {
        return matrix[index];
    }
    
    /** r/w access **/
    inline T& operator()(index_t i_row, index_t i_col)
    {
        return matrix[i_col*num_rows+i_row];
    }
    
    inline T& operator[](index_t index)
    {
        return matrix[index];
    }
    
    inline HFMatrix<T> get()
    {
        return *this;
    }
    
    T* get_column_vector(index_t col) const
    {
        return &matrix[col*num_rows];
    }
    
    /** check for pointer identity **/
    bool operator== (HFMatrix<T> &that);
    
    /** check for element identity **/
    bool equals(HFMatrix<T> &that);
    
    void set_const(T const_elem);
    void zero();
    
    T max_single();
    
    
    /** clone **/
    HFMatrix<T> clone();
    static T* clone_matrix(const T *matrix, int32_t nrows, int32_t ncols);

    static void transpose_matrix(T *&matrix, int32_t &nrows, int32_t &ncols);
    
    static void create_diaonal_matrix(T *matrix, T *v, int32_t size);
    static HFMatrix<T> create_identity_matrix(int32_t size, T scale);
    static HFMatrix<float64_t> create_centering_matrix(int32_t size);
    
    static HFMatrix<float64_t> matrix_multiply(
            HFMatrix<float64_t> A, HFMatrix<float64_t> B,
            bool transpose_A = false, bool transpose_B = false,
            float64_t scale = 1.0);
    
    /* display */
    void display_matrix(const char *name = "Matrix") const;
    
    static void display_matrix(const T *matrix, int32_t rows, int32_t cols,
                            const char *name="Matrix", const char *prefix="");
    
    static void display_matrix(const HFMatrix<T> matrix, 
                            const char *name="Matrix", const char *prefix="");
    
#ifdef HAVE_LAPACK
    static void inverse(HFMatrix<float64_t> &matrix);
    static float64_t* pinv(float64_t *matrix, int32_t rows, int32_t cols,
                                float64_t *target = NULL);
    
#endif

    static float64_t trace(float64_t *mat, int32_t nrows, int32_t ncols);
    
    static T* get_row_sum(T *matrix, int32_t m, int32_t n);
    static T* get_col_sum(T *matrix, int32_t m, int32_t n);
    
    void center();
    static void center_matrix(T *matrix, int32_t m, int32_t n);
    
    void remove_column_mean();
    
    
    void load(CFile *loader);
    void save(CFile *saver);
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

