#include "base/memory.h"
#include "base/common.h"


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
