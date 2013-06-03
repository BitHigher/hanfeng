/* 
 * File:   Parallel.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午7:13
 */

#include "Parallel.h"
#include "../lib/config.h"

#if defined(LINUX) && defined(_SC_NPROCESSORS_ONLN)
#include <unistd.h>
#elif defined(DARWIN)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif


using namespace hanfeng;

Parallel::Parallel():refcount_(0), num_threads_(0)
{
}

Parallel::Parallel(const Parallel &orig): refcount_(0)
{
    num_threads_ = orig.get_num_threads();
}

Parallel::~Parallel()
{
}

int32_t Parallel::get_num_cpus() const
{
#if defined(LINUX) && defined(_SC_NPROCESSORS_ONLN)
    return sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(DARWIN)
    int32_t num;
    size_t size = sizeof(num);
    if(!sysctlbyname("hw.ncpu", &num, &size, NULL, 0))
        return num;
#endif
    return 1;
}

int32_t Parallel::get_num_threads() const
{
    return num_threads_;
}

void Parallel::set_num_threads(int32_t n)
{
#ifndef HAVE_PTHREAD
    ASSERT(n == 1);
#endif
    
    num_threads_ = n;
}

int32_t Parallel::ref()
{
    ++refcount_;
    return refcount_;
}

int32_t Parallel::unref()
{
    if(refcount_ == 0 || --refcount_ == 0)
    {
        delete this;
        return 0;
    }
    
    else
        return refcount_;
}