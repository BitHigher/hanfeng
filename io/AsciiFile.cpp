/* 
 * File:   AsciiFile.cpp
 * Author: zhf
 * 
 * Created on 2013年6月9日, 上午11:26
 */

#include "AsciiFile.h"
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>

using namespace hanfeng;

CAsciiFile::CAsciiFile()
{
}

CAsciiFile::CAsciiFile(FILE* f, const char* name)
: CFile(f, name)
{
}

CAsciiFile::CAsciiFile(const char* fname, const char rw, const char *name)
: CFile(fname, rw, name)
{
}

CAsciiFile::~CAsciiFile()
{
}

template<class T>
void CAsciiFile::append_item(DynArray<T>* items, char* ptr_data, char* ptr_item)
{
    size_t len = (ptr_data - ptr_item)/sizeof(char);
    char *item = HF_MALLOC(char, len+1);
    memset(item, 0, sizeof(char)*(len+1));
    item = strncpy(item, ptr_item, len);
    
    HF_DEBUG("current %c, len %d, item %s\n", *ptr_data, len, ptr_item);
    items->append_element(item);
}

#define GET_MATRIX(funcname, conv, hf_type)                                    \
void CAsciiFile::funcname(hf_type *& matrix,                                   \
                int32_t& num_feat, int32_t& num_vec)                           \
{                                                                              \
    struct stat stats;                                                         \
    if(stat(filename_, &stats))                                                \
        HF_ERROR("Could not get file statistics.\n");                          \
                                                                               \
    char *data = HF_MALLOC(char, stats.st_size+1);                             \
    memset(data, 0, sizeof(char)*(stats.st_size+1));                           \
                                                                               \
    size_t nread = fread(data, sizeof(char), stats.st_size, file_);            \
    if(nread < 0)                                                              \
        HF_ERROR("Could not read data from %s.\n", filename_);                 \
                                                                               \
    int32_t nf = 0;                                                            \
    num_feat = 0;                                                              \
    num_vec = 0;                                                               \
                                                                               \
    char *ptr_item = NULL;                                                     \
    char *ptr_data = data;                                                     \
                                                                               \
    DynArray<char*> *items = new DynArray<char*>();                            \
                                                                               \
    while(*ptr_data)                                                           \
    {                                                                          \
        if(*ptr_data == '\n')                                                  \
        {                                                                      \
            if(ptr_item)                                                       \
                nf++;                                                          \
                                                                               \
            if(num_feat != 0 && nf != num_feat)                                \
                HF_ERROR("Number of features mismatch(%d != %d) "              \
                        "in vector %d in file %s.\n", num_feat,                \
                        nf, num_vec, filename_);                               \
                                                                               \
            append_item(items, ptr_data, ptr_item);                            \
                                                                               \
            num_feat = nf;                                                     \
            num_vec++;                                                         \
            nf = 0;                                                            \
            ptr_item = NULL;                                                   \
        }                                                                      \
        else if(!isblank(*ptr_data) && !ptr_item)                              \
        {                                                                      \
            ptr_item = ptr_data;                                               \
        }                                                                      \
        else if(isblank(*ptr_data) && ptr_item)                                \
        {                                                                      \
            append_item(items, ptr_data, ptr_item);                            \
            ptr_item = NULL;                                                   \
            nf++;                                                              \
        }                                                                      \
                                                                               \
        ptr_data++;                                                            \
    }                                                                          \
                                                                               \
    HF_DEBUG("num_feat: %d, num_vec: %d\n", num_feat, num_vec);                \
                                                                               \
    /* copy data into matrix */                                                \
    matrix = HF_MALLOC(hf_type, num_feat*num_vec);                             \
    for(index_t i = 0; i < num_vec; ++i)                                       \
    {                                                                          \
        for(index_t j = 0; j < num_feat; ++j)                                  \
        {                                                                      \
            char *item = items->get_element(i*num_feat+j);                     \
            matrix[i*num_feat+j] = conv(item);                                 \
            HF_FREE(item);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    delete items;                                                              \
}

GET_MATRIX(get_matrix, atoi, char)
GET_MATRIX(get_matrix, atoi, int8_t)
GET_MATRIX(get_matrix, atoi, uint8_t)
GET_MATRIX(get_matrix, atoi, int16_t)
GET_MATRIX(get_matrix, atoi, uint16_t)
GET_MATRIX(get_matrix, atoi, int32_t)
GET_MATRIX(get_matrix, atoi, uint32_t)
GET_MATRIX(get_matrix, atoll, int64_t)
GET_MATRIX(get_matrix, atoll, uint64_t)
GET_MATRIX(get_matrix, atof, float32_t)
GET_MATRIX(get_matrix, atof, float64_t)
GET_MATRIX(get_matrix, atof, floatmax_t)
#undef GET_MATRIX
        
        
#define SET_MATRIX(funcname, hf_type, fprt_type, type_str)                     \
void CAsciiFile::funcname(const hf_type *matrix,                               \
                        int32_t num_feat, int32_t num_vec)                     \
{                                                                              \
                                                                               \
}
        
SET_MATRIX(set_matrix, char, char, "%c")
SET_MATRIX(set_matrix, int8_t, int8_t, "%d")
SET_MATRIX(set_matrix, uint8_t, uint8_t, "%u")
SET_MATRIX(set_matrix, int16_t, int16_t, "%i")
SET_MATRIX(set_matrix, uint16_t, uint16_t, "%u")
SET_MATRIX(set_matrix, int32_t, int32_t, "%i")
SET_MATRIX(set_matrix, uint32_t, uint32_t, "%u")
SET_MATRIX(set_matrix, int64_t, int64_t, "%lli")
SET_MATRIX(set_matrix, uint64_t, uint64_t, "%llu")
SET_MATRIX(set_matrix, float32_t, float32_t, "%.16g")
SET_MATRIX(set_matrix, float64_t, float64_t, "%.16lg")
SET_MATRIX(set_matrix, floatmax_t, floatmax_t, "%.16Lg")
        
#undef SET_MATRIX
        
#define GET_VECTOR(funcname, mfname, hf_type)                                  \
void CAsciiFile::funcname(hf_type *&vec, int32_t &len)                         \
{                                                                              \
    vec = NULL;                                                                \
    len = 0;                                                                   \
                                                                               \
    int32_t num_feat = 0;                                                      \
    int32_t num_vec = 0;                                                       \
    mfname(vec, num_feat, num_vec);                                            \
                                                                               \
    if(num_feat == 1 || num_vec == 1)                                          \
    {                                                                          \
        if(num_feat == 1)                                                      \
            len = num_vec;                                                     \
        else                                                                   \
            len = num_feat;                                                    \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        HF_FREE(vec);                                                          \
        vec = NULL;                                                            \
        len = 0;                                                               \
        HF_ERROR("Could not read vector from %s "                              \
                "shape(%dx%d) found.", filename_, num_vec, num_feat);          \
    }                                                                          \
}                                                                              \

GET_VECTOR(get_vector, get_matrix, char)
GET_VECTOR(get_vector, get_matrix, int8_t)
GET_VECTOR(get_vector, get_matrix, uint8_t)
GET_VECTOR(get_vector, get_matrix, int16_t)
GET_VECTOR(get_vector, get_matrix, uint16_t)
GET_VECTOR(get_vector, get_matrix, int32_t)
GET_VECTOR(get_vector, get_matrix, uint32_t)
GET_VECTOR(get_vector, get_matrix, int64_t)
GET_VECTOR(get_vector, get_matrix, uint64_t)
GET_VECTOR(get_vector, get_matrix, float32_t)
GET_VECTOR(get_vector, get_matrix, float64_t)
GET_VECTOR(get_vector, get_matrix, floatmax_t)
        
#undef GET_VECTOR
        
#define SET_VECTOR(funcname, mfname, hf_type)                                  \
void CAsciiFile::funcname(const hf_type *vec, int32_t len)                     \
{                                                                              \
    mfname(vec, len, 1);                                                       \
}
        
SET_VECTOR(set_vector, set_matrix, char)
SET_VECTOR(set_vector, set_matrix, int8_t)
SET_VECTOR(set_vector, set_matrix, uint8_t)
SET_VECTOR(set_vector, set_matrix, int16_t)
SET_VECTOR(set_vector, set_matrix, uint16_t)
SET_VECTOR(set_vector, set_matrix, int32_t)
SET_VECTOR(set_vector, set_matrix, uint32_t)
SET_VECTOR(set_vector, set_matrix, int64_t)
SET_VECTOR(set_vector, set_matrix, uint64_t)
SET_VECTOR(set_vector, set_matrix, float32_t)
SET_VECTOR(set_vector, set_matrix, float64_t)
SET_VECTOR(set_vector, set_matrix, floatmax_t)

#undef SET_VECTOR