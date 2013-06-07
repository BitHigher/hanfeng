#include "memory.h"
#include "common.h"
#include "../lib/HFException.h"

namespace hanfeng
{
    
void* hf_malloc(size_t size)
{
    void *p = malloc(size);
    
    if(!p)
    {
        const size_t buf_len = 128;
        char buf[buf_len];
        size_t written = snprintf(buf, buf_len,
                "Out of memory error, tried to allocate %lld bytes "
                "using malloc.\n", (long long int)size);
        
        if(written < buf_len)
            throw HFException(buf);
        else
            throw HFException("Out of memory error using malloc");
    }
    
    return p;
}


void* hf_calloc(size_t num, size_t size)
{
    void *p = calloc(num, size);
    
    if(!p)
    {
        const size_t buf_len = 128;
        char buf[buf_len];
        size_t written = snprintf(buf, buf_len,
                "Out of memory error, tried to allocate %lld bytes "
                "using calloc.\n", (long long int)size);
        
        if(written < buf_len)
            throw HFException(buf);
        else
            throw HFException("Out of memory error using calloc");
    }
    
    return p;
}

void hf_free(void *ptr)
{
    free(ptr);
}

}