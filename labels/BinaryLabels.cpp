/* 
 * File:   BinaryLabels.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午11:04
 */

#include "BinaryLabels.h"

using namespace hanfeng;

CBinaryLabels::CBinaryLabels()
{
}

CBinaryLabels::CBinaryLabels(int32_t num_labels)
: CDenseLabels(num_labels)
{
}

CBinaryLabels::CBinaryLabels(HFVector<float64_t> src, float64_t threshold)
{
    HFVector<float64_t> labels(src.vlen);
    for(index_t i = 0; i < src.vlen; ++i)
        labels[i] = src[i]+threshold >= 0?1.0 : -1.0; // FIXME why not src[i] >= threshold
    
    set_labels(labels);
    set_values(src);
}

CBinaryLabels::CBinaryLabels(CFile *loader)
: CDenseLabels(loader)
{
}

CBinaryLabels::~CBinaryLabels()
{
}

void CBinaryLabels::ensure_valid(const char *context)
{
    // TODO ensure_valid
}

void CBinaryLabels::scores_to_probabilities()
{
    // TODO scores_to_probabilities
}