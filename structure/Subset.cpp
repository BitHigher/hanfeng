/* 
 * File:   Subset.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午4:27
 */

#include "Subset.h"
#include "../base/Parameter.h"

using namespace hanfeng;

CSubset::CSubset()
{
    init();
}

CSubset::CSubset(HFVector<index_t> subset_idx)
{
    init();
    
    subset_index_ = subset_idx;
}

CSubset::~CSubset()
{
}

void CSubset::init()
{
    HF_ADD(&subset_index_, "subset", "Vector of subset indeices",
            MS_NOT_AVAILABLE);
}
