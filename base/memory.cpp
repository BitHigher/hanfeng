#include "memory.h"
#include "common.h"

void* hf_malloc(size_t size)
{
    void *p = malloc(size);
    if(!p)
    {
        // TODO
    }
    
    return p;
}


void* hf_calloc(size_t num, size_t size)
{
    void *p = calloc(num, size);
    
    if(!p)
    {
        // TODO
    }
    
    return p;
}

void hf_free(void *ptr)
{
    free(ptr);
}
