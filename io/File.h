/* 
 * File:   File.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午12:58
 */

#ifndef IO_FILE_H
#define IO_FILE_H

#include "../base/HFObject.h"
#include "../base/common.h"

namespace hanfeng
{

class CFile : public CHFObject
{
public:
    CFile();
    CFile(FILE *f, const char *name = NULL);
    CFile(const char *fname, char rw='r', const char *name = NULL);
    virtual ~CFile();
    
    void close()
    {
        HF_FREE(variable_name_);
        HF_FREE(filename_);
        if(file_)
            fclose(file_);
        
        variable_name_ = NULL;
        filename_ = NULL;
        file_ = NULL;
    }
    
    inline FILE* get_file_descriptor() { return file_;}
    
    void set_variable_name(const char *name);
    char* get_variable_name();

    virtual const char* get_name() const{return "File";}
    
    static char* read_whole_file(char *fname, size_t &len);
protected:
    FILE *file_;
    char task_;
    char *filename_;
    char *variable_name_;

};

}

#endif	/* IO_FILE_H */

