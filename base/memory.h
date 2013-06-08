/* 
 * File:   memory.h
 * Author: zhf
 *
 * Created on 2013年5月24日, 下午10:05
 */

#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "common.h"

#define HF_MALLOC(type, len) hf_generic_malloc<type>(size_t(len))
#define HF_CALLOC(type, len) hf_generic_calloc<type>(size_t(len))
#define HF_REALLOC(type, ptr, old_len, len) hf_generic_realloc<type>(ptr, size_t(old_len), size_t(len))
#define HF_FREE(ptr) hf_generic_free(ptr)


namespace hanfeng
{

/** functions **/
void* hf_malloc(size_t size);

template<class T>
T* hf_generic_malloc(size_t len)
{
    return (T*)hf_malloc(sizeof(T)*len);
}


void* hf_calloc(size_t num, size_t size);

template<class T>
T* hf_generic_calloc(size_t len)
{
    return (T*)hf_calloc(len, sizeof(T));
}

void *hf_realloc(void *ptr, size_t len);

template<class T>
T* hf_generic_realloc(T *ptr, size_t old_len, size_t len)
{
    return (T*)hf_realloc(ptr, sizeof(T)*len);
}

void hf_free(void *ptr);

template<class T>
void hf_generic_free(T *ptr)
{
    hf_free((void*)ptr);
}

}

#endif	/* BASE_MEMORY_H */

