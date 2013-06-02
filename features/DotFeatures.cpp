/* 
 * File:   DotFeatures.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午1:35
 */

#include "DotFeatures.h"
#include "../io/HFIO.h"

using namespace hanfeng;

CDotFeatures::CDotFeatures()
{
}

CDotFeatures::CDotFeatures(const CDotFeatures &orig)
{
}

CDotFeatures::~CDotFeatures()
{
}

void CDotFeatures::dense_dot_range(float64_t* output, int32_t start,
                                    int32_t stop, float64_t* alphas, 
                                    float64_t* vec, int32_t dim, float64_t b)
{
    ASSERT(output);
    output -= start;
    
    ASSERT(start >= 0);
    ASSERT(stop > start);
    ASSERT(stop <= get_num_vectors());
    
    int32_t num_vectors = stop-start;
    ASSERT(num_vectors > 0);
    
    // TODO
}
