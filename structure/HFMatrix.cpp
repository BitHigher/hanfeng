/* 
 * File:   HFMatrix.cpp
 * Author: zhf
 * 
 * Created on 2013年5月25日, 上午12:18
 */

#include <iostream>
#include "HFMatrix.h"

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
void HFMatrix<T>::display_matrix()
{
    for(uint32_t i = 0; i < num_rows; ++i)
    {
        for(uint32_t j = 0; j < num_cols; ++j)
        {
            std::cout << matrix[i*num_cols + j] << ' ';
        }
        std::cout << '\n';
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