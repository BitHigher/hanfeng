/* 
 * File:   File.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午12:58
 */

#include "File.h"
#include "HFIO.h"

using namespace hanfeng;

CFile::CFile()
: CHFObject(), file_(NULL), filename_(NULL), variable_name_(NULL)
{
}

CFile::CFile(FILE* f, const char *name)
: CHFObject(), file_(f), filename_(NULL)
{    
    variable_name_ = NULL;
    if(name)
        set_variable_name(name);
}

CFile::CFile(const char *fname, char rw, const char *name)
: CHFObject()
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