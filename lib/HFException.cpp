/* 
 * File:   HFException.cpp
 * Author: zhf
 * 
 * Created on 2013年5月25日, 下午3:28
 */

#include "HFException.h"
#include "string.h"

using namespace hanfeng;

HFException::HFException(const char *str) 
{
#ifndef WIN32
    // TODO
#endif
    
    init(str);
}

HFException::HFException(const HFException &orig)
{
    init(orig.val);
}

HFException::~HFException()
{
    free(val);
}

void HFException::init(const char* str)
{
    size_t n = strlen(str)+1;
    
    val = (char*)malloc(n);
    if(val)
        strncpy(val, str, n);
    else
    {
        // TODO fprintf
        exit(1);
    }
}

