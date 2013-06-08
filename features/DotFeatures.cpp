/* 
 * File:   DotFeatures.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午1:35
 */

#include "DotFeatures.h"
#include "../io/HFIO.h"
#include "../base/Parameter.h"

using namespace hanfeng;

CDotFeatures::CDotFeatures(int32_t size)
: CFeatures(size), combined_weight_(1.0)
{
    init();
}

CDotFeatures::CDotFeatures(const CDotFeatures &orig)
: CFeatures(orig), combined_weight_(orig.combined_weight_)
{
    init();
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
    
    // TODO CSignal
}


void CDotFeatures::init()
{
    set_property(FP_DOT);
    
    HF_ADD(&combined_weight_, "combined_weight",
            "Feature weighting in combined dot feature", MS_NOT_AVAILABLE);
}