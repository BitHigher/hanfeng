/* 
 * File:   File.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午12:58
 */

#include "File.h"
#include "HFIO.h"

#include <string.h>

using namespace hanfeng;

CFile::CFile()
: file_(NULL), filename_(NULL), variable_name_(NULL)
{
}

CFile::CFile(FILE* f, const char *name)
: file_(f), filename_(NULL)
{    
    variable_name_ = NULL;
    if(name)
        set_variable_name(name);
}

CFile::CFile(const char *fname, char rw, const char *name)
{
    variable_name_ = NULL;
    task_ = rw;
    filename_ = strdup(fname);
    
    char mode[2];
    mode[0] = rw;
    mode[1] = '\0';
    
    if(rw == 'r' || rw == 'w')
    {
        if(filename_)
        {
            if(!(file_ = fopen((const char*)filename_, (const char*)mode)))
                HF_ERROR("Error opening file '%s'", filename_);
        }else
            HF_ERROR("Filename is NULL");
    }else
        HF_ERROR("unknown mode '%c'", mode[0]);
    
    if(name)
        set_variable_name(name);
}

CFile::~CFile()
{
    close();
}

void CFile::set_variable_name(const char* name)
{
    HF_FREE(variable_name_);
    variable_name_ = strdup(name);
}

char* CFile::get_variable_name()
{
    return strdup(variable_name_);
}

char* CFile::read_whole_file(char* fname, size_t& len)
{
    FILE *tmpf = fopen(fname, "r");
    ASSERT(tmpf);
    
    fseek(tmpf, 0, SEEK_END);
    len = ftell(tmpf);
    ASSERT(len > 0);
    
    rewind(tmpf);
    
    char *result = HF_MALLOC(char, len);
    size_t total = fread(result, 1, len, tmpf);
    ASSERT(total == len);
    fclose(tmpf);
    
    return result;
}

void CFile::get_vector(bool*& vector, int32_t& len)
{
    int32_t *int_vector;
    get_vector(int_vector, len);
    
    ASSERT(len > 0);
    vector = HF_MALLOC(bool, len);
    
    for(index_t i = 0; i < len; ++i)
        vector[i] = (int_vector[i] != 0);
    
    HF_FREE(int_vector);
}

void CFile::set_vector(const bool* vector, int32_t len)
{
    int32_t *int_vector = HF_MALLOC(int32_t, len);
    for(index_t i = 0; i < len; ++i)
    {
        if(vector[i])
            int_vector[i] = 1;
        else
            int_vector[i] = 0;
    }
    
    set_vector(int_vector, len);
    
    HF_FREE(int_vector);
}

void CFile::get_matrix(bool*& matrix, int32_t& num_feat, int32_t& num_vec)
{
    int32_t *int_matrix;
    get_matrix(int_matrix, num_feat, num_vec);
    
    ASSERT(num_feat > 0 && num_vec > 0);
    
    matrix = HF_MALLOC(bool, num_feat * num_vec);
    for(index_t i = 0; i < num_feat * num_vec; ++i)
        matrix[i] = (int_matrix[i] != 0);
    
    HF_FREE(int_matrix);
}

void CFile::set_matrix(const bool *matrix, int32_t num_feat, int32_t num_vec)
{
    int32_t *int_matrix = HF_MALLOC(int32_t, num_feat*num_vec);
    for(index_t i = 0; i < num_feat*num_vec; ++i)
        int_matrix[i] = matrix[i];
    
    set_matrix(int_matrix, num_feat, num_vec);
    
    HF_FREE(int_matrix);
}