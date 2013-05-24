/* 
 * File:   memory.h
 * Author: zhf
 *
 * Created on 2013年5月24日, 下午10:05
 */

#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "common.h"


#define HF_CALLOC(type, len) hf_generic_calloc<type>(size_t(len))
#define HF_FREE(ptr) hf_generic_free(ptr)




/** functions **/
void* hf_calloc(size_t num, size_t size);
template<class T>
T* hf_generic_calloc(size_t len)
{
    return (T*)hf_calloc(len, sizeof(T));
}


void hf_free(void *ptr);
template<class T>
void hf_generic_free(T *ptr)
{
    hf_free((void*)ptr);
}


#endif	/* BASE_MEMORY_H */

