/* 
 * File:   AsciiFile.h
 * Author: zhf
 *
 * Created on 2013年6月9日, 上午11:26
 */

#ifndef ASCIIFILE_H
#define ASCIIFILE_H

#include "../io/File.h"
#include "../structure/DynArray.h"

namespace hanfeng
{

class CAsciiFile : public CFile{
public:
    CAsciiFile();
    CAsciiFile(FILE *f, const char *name=NULL);
    CAsciiFile(const char *fname, const char rw='r', const char *name=NULL);
   
    virtual ~CAsciiFile();
    
    virtual const char* get_name() const {return "AsciiFile"; }
    
    virtual void get_vector(char *&vector, int32_t &len);
    virtual void get_vector(int8_t *&vector, int32_t &len);
    virtual void get_vector(uint8_t *&vector, int32_t &len);
    virtual void get_vector(int16_t *&vector, int32_t &len);
    virtual void get_vector(uint16_t *&vector, int32_t &len);
    virtual void get_vector(int32_t *&vector, int32_t &len);
    virtual void get_vector(uint32_t *&vector, int32_t &len);
    virtual void get_vector(int64_t *&vector, int32_t &len);
    virtual void get_vector(uint64_t *&vector, int32_t &len);
    virtual void get_vector(float32_t *&vector, int32_t &len);
    virtual void get_vector(float64_t *&vector, int32_t &len);
    virtual void get_vector(floatmax_t *&vector, int32_t &len);
    
    virtual void set_vector(const char *vector, int32_t len);
    virtual void set_vector(const int8_t *vector, int32_t len);
    virtual void set_vector(const int16_t *vector, int32_t len);
    virtual void set_vector(const int32_t *vector, int32_t len);
    virtual void set_vector(const int64_t *vector, int32_t len);
    virtual void set_vector(const uint8_t *vector, int32_t len);
    virtual void set_vector(const uint16_t *vector, int32_t len);
    virtual void set_vector(const uint32_t *vector, int32_t len);
    virtual void set_vector(const uint64_t *vector, int32_t len);
    virtual void set_vector(const float32_t *vector, int32_t len);
    virtual void set_vector(const float64_t *vector, int32_t len);
    virtual void set_vector(const floatmax_t *vector, int32_t len);
    
    virtual void get_matrix(char *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(int8_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(uint8_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(int16_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(uint16_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(int32_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(uint32_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(int64_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(uint64_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(float32_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(float64_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    virtual void get_matrix(floatmax_t *&matrix, int32_t &num_feat, int32_t &num_vec);
    
    virtual void set_matrix(const char *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const int8_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const int16_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const int32_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const int64_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const uint8_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const uint16_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const uint32_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const uint64_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const float32_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const float64_t *matrix, int32_t num_feat, int32_t num_vec);
    virtual void set_matrix(const floatmax_t *matrix, int32_t num_feat, int32_t num_vec);
    
private:
    template<class T>
    void append_item(DynArray<T> *items, char *ptr_data, char *ptr_item);
    
};

}

#endif	/* ASCIIFILE_H */

