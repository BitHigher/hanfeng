/* 
 * File:   HFMatrix.cpp
 * Author: zhf
 * 
 * Created on 2013年5月25日, 上午12:18
 */

#include <iostream>
#include "HFMatrix.h"
#include "../math/Math.h"
#include "../math/lapack.h"

#include "../io/HFIO.h"
#include "HFVector.h"

using namespace hanfeng;

template<class T>
HFMatrix<T>::HFMatrix():HFReferenceData()
{
    init_data();
}

template<class T>
HFMatrix<T>::HFMatrix(const HFMatrix &orig) 
:HFReferenceData(orig)
{
    copy_data(orig);
}

template<class T>
HFMatrix<T>::HFMatrix(T* m, int32_t nrows, int32_t ncols, bool ref_counting)
: HFReferenceData(ref_counting), matrix(m), num_rows(nrows), num_cols(ncols)
{
    
}

template<class T>
HFMatrix<T>::HFMatrix(int32_t nrows, int32_t ncols, bool ref_counting)
: HFReferenceData(ref_counting), num_rows(nrows), num_cols(ncols)
{
    matrix = HF_MALLOC(T, ((int64_t)nrows) * ncols);
}

template<class T>
HFMatrix<T>::~HFMatrix() 
{
    unref();
}

template<class T>
void HFMatrix<T>::init_data()
{
    matrix = NULL;
    num_rows = 0;
    num_cols = 0;
}

template<class T>
void HFMatrix<T>::copy_data(const HFReferenceData &that)
{
    matrix = ((HFMatrix<T>*)(&that))->matrix;
    num_rows = ((HFMatrix<T>*)(&that))->num_rows;
    num_cols = ((HFMatrix<T>*)(&that))->num_cols;
}

template<class T>
void HFMatrix<T>::free_data()
{
    HF_FREE(matrix);
    matrix = NULL;
    num_rows = 0;
    num_cols = 0;
}

template<class T>
T* HFMatrix<T>::clone_matrix(const T* matrix, int32_t nrows, int32_t ncols)
{
    T *result = HF_MALLOC(T, int64_t(nrows)*ncols);
    for(int64_t i = 0; i < int64_t(nrows)*ncols; ++i)
        result[i] = matrix[i];
    
    return result;
}

template<class T>
HFMatrix<T> HFMatrix<T>::clone()
{
    return HFMatrix<T>(clone_matrix(matrix, num_rows, num_cols), 
                        num_rows, num_cols);
}

template<class T>
void HFMatrix<T>::transpose_matrix(
        T*& matrix, int32_t& nrows, int32_t& ncols)
{
    T *transposed = HF_MALLOC(T, int64_t(nrows)*ncols);
    for(int32_t i = 0; i < ncols; ++i)
    {
        for(int32_t j = 0; j < nrows; ++j)
            transposed[i+j*nrows] = matrix[i*nrows+j];
    }
    
    HF_FREE(matrix);
    matrix = transposed;
    
    CMath::swap(nrows, ncols);
}

#ifdef HAVE_LAPACK
template<class T>
void HFMatrix<T>::inverse(HFMatrix<float64_t> &matrix)
{
    ASSERT(matrix.num_rows == matrix.num_cols);
    int32_t *ipiv = HF_MALLOC(int32_t, matrix.num_cols);
    
    clapack_dgetrf(CblasColMajor,matrix.num_cols,
                   matrix.num_cols,matrix.matrix,
                   matrix.num_cols,ipiv);
    
    clapack_dgetri(CblasColMajor,matrix.num_cols,
                   matrix.matrix,matrix.num_cols,ipiv);
    
    HF_FREE(ipiv);
}

template<class T>
float64_t* HFMatrix<T>::pinv(float64_t* matrix, int32_t rows, 
                                int32_t cols, float64_t *target)
{
    if(!target)
        target = HF_MALLOC(float64_t, rows*cols);
    
    char jobu = 'A';
    char jobvt = 'A';
    
    int32_t m = rows;
    int32_t n = cols;
    int32_t lda = m;
    int32_t ldu = m;
    int32_t ldvt = n;
    int32_t info = -1;
    
    int32_t lsize = CMath::min(m, n);
    float64_t *s = HF_MALLOC(float64_t, lsize);
    float64_t *u = HF_MALLOC(float64_t, m*m);
    float64_t *vt = HF_MALLOC(float64_t, n*n);
    
    wrap_dgesvd(jobu, jobvt, m, n, matrix, lda, s, u, ldu, vt, ldvt, &info);
    ASSERT(info == 0);
    
    for(index_t i = 0; i < n; ++i)
    {
        for(index_t j = 0; j < lsize; ++j)
            vt[i*n+j] = vt[i*n+j]/s[j];
    }
    
    cblas_dgemm(CblasColMajor, CblasTrans, CblasTrans, m, n,
                m, 1.0, vt, ldvt, u, ldu, 0, target, m);

    HF_FREE(s);
    HF_FREE(u);
    HF_FREE(vt);
    return target;
}

#endif

template<class T>
float64_t HFMatrix<T>::trace(float64_t* mat, int32_t nrows, int32_t ncols)
{
    ASSERT(nrows == ncols);
    float64_t trace = 0;
    for(int32_t i = 0; i < nrows; ++i)
        trace += mat[i*ncols + i];
    
    return trace;
}

template<class T>
bool HFMatrix<T>::operator ==(HFMatrix<T>& that)
{
    if(num_rows != that.num_rows || num_cols != that.num_cols)
        return false;
    
    if(matrix != that.matrix)
        return false;
    
    return true;
}


template<class T>
bool HFMatrix<T>::equals(HFMatrix<T>& that)
{
    if(num_rows != that.num_rows || num_cols != that.num_cols)
        return false;
    
    for(index_t i = 0; i < num_rows*num_cols; ++i)
    {
        if(matrix[i] != that.matrix[i])
            return false;
    }
    
    return true;
}

template<class T>
void HFMatrix<T>::set_const(T const_elem)
{
    for(index_t i = 0; i < num_rows*num_cols; ++i)
        matrix[i] = const_elem;
}

template<class T>
void HFMatrix<T>::zero()
{
    set_const(0);
}

template<class T>
T HFMatrix<T>::max_single()
{
    T max = matrix[0];
    for(index_t i = 0; i < num_rows*num_cols; ++i)
    {
        if(matrix[i] > max)
            max = matrix[i];
    }
    return max;
}

template<class T>
void HFMatrix<T>::create_diaonal_matrix(T* matrix, T* v, int32_t size)
{
    for(index_t i = 0; i < size; ++i)
    {
        for(index_t j = 0; j < size; ++j)
        {
            if(i == j)
                matrix[j*size+i] = v[i];
            else
                matrix[j*size+i] = 0;
        }
    }
}

template<class T>
HFMatrix<T> HFMatrix<T>::create_identity_matrix(int32_t size, T scale)
{
    HFMatrix<T> I(size, size);
    for(index_t i = 0; i < size; ++i)
    {
        for(index_t j = 0; j < size; ++j)
        {
            I(i,j) = (i==j)?scale:0;
        }
    }
    
    return I;
}

template<class T>
HFMatrix<float64_t> HFMatrix<T>::create_centering_matrix(int32_t size)
{
    HFMatrix<float64_t> H = HFMatrix<float64_t>::
            create_identity_matrix(size, 1.0);
    
    float64_t subtract = 1.0/size;
    for(index_t i = 0; i < size; ++i)
    {
        for(index_t j = 0; j < size; ++j)
            H(i,j) -= subtract;
    }
    
    return H;
}

template<class T>
HFMatrix<float64_t> HFMatrix<T>::matrix_multiply(
                            HFMatrix<float64_t> A, HFMatrix<float64_t> B, 
                            bool transpose_A, bool transpose_B, 
                            float64_t scale)
{
    index_t cols_A = transpose_A ? A.num_rows : A.num_cols;
    index_t rows_A = transpose_A ? A.num_cols : A.num_rows;
    index_t cols_B = transpose_B ? B.num_rows : B.num_cols;
    index_t rows_B = transpose_A ? B.num_cols : B.num_rows;

    /* check dimension */
    if(cols_A != rows_B)
    {
        HF_SERROR("HFMatirx::matrix_multiply(): dimension mismatch: "
                "A(%dx%d)*B(%dx%d)\n", rows_A, cols_A, rows_B, cols_B);
    }
    
    HFMatrix<float64_t> C(rows_A, cols_B);
    C.zero();
    
#ifdef HAVE_LAPACK
    cblas_dgemm(CblasColMajor,
             transpose_A ? CblasTrans : CblasNoTrans,
             transpose_B ? CblasTrans : CblasNoTrans,
             rows_A, cols_B, cols_A, scale, 
             A.matrix, A.num_rows, B.matrix, B.num_rows,
             0.0, C.matrix, C.num_rows); 
#else
    for(index_t i = 0; i < rows_A; ++i)
    {
        for(index_t j = 0; j < cols_B; ++j)
        {
            for(index_t k = 0; k < cols_A; ++k)
                C(i, j) += A(i, k) * B(k, j);
        }
    }    
#endif
    
    return C;
}

template<class T>
T* HFMatrix<T>::get_row_sum(T* matrix, int32_t m, int32_t n)
{
    T *rowsums = HF_CALLOC(T, n);
    
    for(index_t i = 0; i < n; ++i)
    {
        for(index_t j = 0; j < m; ++j)
            rowsums[i] += matrix[j + int64_t(i)*m];
    }
    
    return rowsums;
}

template<class T>
T* HFMatrix<T>::get_col_sum(T* matrix, int32_t m, int32_t n)
{
    T *colsums = HF_CALLOC(T, m);
    
    for(index_t i = 0; i < m; ++i)
    {
        for(index_t j = 0; j < n; ++j)
            colsums[i] += matrix[i + int64_t(j)*m];
    }
    
    return colsums;
}

template<class T>
void HFMatrix<T>::center_matrix(T* matrix, int32_t m, int32_t n)
{
    float64_t num_data = n;
    
    T *colsums = get_col_sum(matrix, m, n);
    T *rowsums = get_row_sum(matrix, m, n);
    
    for(index_t i = 0; i < m; ++i)
        colsums[i] /= num_data;
    for(index_t i = 0; i < n; ++i)
        rowsums[i] /= num_data;
    
    T s = HFVector<T>::sum(rowsums, n)/num_data;
    
    for(index_t i = 0; i < n; ++i)
    {
        for(index_t j = 0; j < m; ++j)
            matrix[int64_t(i)*m + j] += s - colsums[j] - rowsums[i];
    }
    
    HF_FREE(colsums);
    HF_FREE(rowsums);
}

template<class T>
void HFMatrix<T>::center()
{
    center_matrix(matrix, num_rows, num_cols);
}

template<class T>
void HFMatrix<T>::remove_column_mean()
{
    T *means = get_row_sum(matrix, num_rows, num_cols);
    
    for(index_t i = 0; i < num_cols; ++i)
    {
        means[i] /= num_rows;
        for(index_t j = 0; j < num_rows; ++j)
            matrix[int64_t(i)*num_rows+j] -= means[i];
    }
    
    HF_FREE(means);
}

template<class T>
void HFMatrix<T>::load(CFile *loader)
{
    ASSERT(loader);
    unref();
    
    HF_SET_LOCALE_C;
    loader->get_matrix(matrix, num_rows, num_cols);
    HF_RESET_LOCALE;
}

template<class T>
void HFMatrix<T>::save(CFile *saver)
{
    ASSERT(saver);
    
    HF_SET_LOCALE_C;
    saver->set_matrix(matrix, num_rows, num_cols);
    HF_RESET_LOCALE;
}

template<class T>
void HFMatrix<T>::display_matrix(const char *name, const char *prefix) const
{
    display_matrix(matrix, num_rows, num_cols, name, prefix);
}

template<class T>
void HFMatrix<T>::display_matrix(const HFMatrix<T> matrix, 
                                const char *name, const char *prefix)
{
    // FIXME there is a bug in shogun
    // matrix.display_matrix(); 
    display_matrix(matrix.matrix, matrix.num_rows, matrix.num_cols,
                        name, prefix);
}

namespace hanfeng
{

template<>
void HFMatrix<bool>::display_matrix(const bool *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i] != 0, 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}
    
template<>
void HFMatrix<char>::display_matrix(const char *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%c%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<int8_t>::display_matrix(const int8_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<int16_t>::display_matrix(const int16_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<int32_t>::display_matrix(const int32_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<int64_t>::display_matrix(const int64_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<uint8_t>::display_matrix(const uint8_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<uint16_t>::display_matrix(const uint16_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<uint32_t>::display_matrix(const uint32_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<uint64_t>::display_matrix(const uint64_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%d%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<float32_t>::display_matrix(const float32_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%g%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<float64_t>::display_matrix(const float64_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%.18g%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

template<>
void HFMatrix<floatmax_t>::display_matrix(const floatmax_t *matrix, int32_t rows, 
                            int32_t cols, const char *name, const char *prefix)
{
    ASSERT(rows >= 0 && cols >= 0);
    
    HF_SPRINT("%s%s=[\n", prefix, name);
    for(index_t i = 0; i < rows; ++i)
    {
        HF_SPRINT("%s[", prefix);
        for(index_t j = 0; j < cols; ++j)
            HF_SPRINT("%s\t%.36Lg%s", prefix, matrix[j*rows+i], 
                    j==cols-1?"":",");
        
        HF_SPRINT("%s]%s\n", prefix, i==rows-1?"":",");
    }
    HF_SPRINT("%s]\n", prefix);
}

}


/** supported types **/
template class HFMatrix<bool>;
template class HFMatrix<char>;

template class HFMatrix<int8_t>;
template class HFMatrix<uint8_t>;
template class HFMatrix<int16_t>;
template class HFMatrix<uint16_t>;
template class HFMatrix<int32_t>;
template class HFMatrix<uint32_t>;
template class HFMatrix<int64_t>;
template class HFMatrix<uint64_t>;

template class HFMatrix<float32_t>;
template class HFMatrix<float64_t>;
template class HFMatrix<floatmax_t>;