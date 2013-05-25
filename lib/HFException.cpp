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
    init(str);
}

HFException::HFException(const HFException &orig) {
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
        // TODO 
        exit(1);
    }
}

