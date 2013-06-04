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
    
    /* vector related getters and setters */
    virtual void get_vector(bool *&vector, int32_t &len);
    virtual void get_vector(char *&vector, int32_t &len) = 0;
    virtual void get_vector(int8_t *&vector, int32_t &len) = 0;
    virtual void get_vector(int16_t *&vector, int32_t &len) = 0;
    virtual void get_vector(int32_t *&vector, int32_t &len) = 0;
    virtual void get_vector(int64_t *&vector, int32_t &len) = 0;
    virtual void get_vector(uint8_t *&vector, int32_t &len) = 0;
    virtual void get_vector(uint16_t *&vector, int32_t &len) = 0;
    virtual void get_vector(uint32_t *&vector, int32_t &len) = 0;
    virtual void get_vector(uint64_t *&vector, int32_t &len) = 0;
    virtual void get_vector(float32_t *&vector, int32_t &len) = 0;
    virtual void get_vector(float64_t *&vector, int32_t &len) = 0;
    virtual void get_vector(floatmax_t *&vector, int32_t &len) = 0;
    
    virtual void set_vector(const bool *vector, int32_t len);
    virtual void set_vector(const char *vector, int32_t len) = 0;
    virtual void set_vector(const int8_t *vector, int32_t len) = 0;
    virtual void set_vector(const int16_t *vector, int32_t len) = 0;
    virtual void set_vector(const int32_t *vector, int32_t len) = 0;
    virtual void set_vector(const int64_t *vector, int32_t len) = 0;
    virtual void set_vector(const uint8_t *vector, int32_t len) = 0;
    virtual void set_vector(const uint16_t *vector, int32_t len) = 0;
    virtual void set_vector(const uint32_t *vector, int32_t len) = 0;
    virtual void set_vector(const uint64_t *vector, int32_t len) = 0;
    virtual void set_vector(const float32_t *vector, int32_t len) = 0;
    virtual void set_vector(const float64_t *vector, int32_t len) = 0;
    virtual void set_vector(const floatmax_t *vector, int32_t len) = 0;
    
    /* matrix related getters and setters */
    virtual void get_matrix(bool *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(char *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(int8_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(int16_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(int32_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(int64_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(uint8_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(uint16_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(uint32_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(uint64_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(float32_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(float64_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    virtual void get_matrix(floatmax_t *&matrix, int32_t &num_feat, int32_t &num_vec) = 0;
    
    virtual void set_matrix(const bool *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const char *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const int8_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const int16_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const int32_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const int64_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const uint8_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const uint16_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const uint32_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const uint64_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const float32_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const float64_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    virtual void set_matrix(const floatmax_t *matrix, int32_t num_feat, int32_t num_vec) = 0;
    
protected:
    FILE *file_;
    char task_;
    char *filename_;
    char *variable_name_;

};

}

#endif	/* IO_FILE_H */

