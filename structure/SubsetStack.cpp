/* 
 * File:   SubsetStack.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午12:28
 */

#include "SubsetStack.h"
#include "../base/Parameter.h"

using namespace hanfeng;

CSubsetStack::CSubsetStack()        
{
    init();
}

CSubsetStack::CSubsetStack(const CSubsetStack &orig)
{
    init();
    
    for(index_t i = 0; i < orig.active_subsets_stack_->get_num_elements(); ++i)
    {
        active_subset_ = (CSubset*)orig.active_subsets_stack_->get_element(i);
        active_subsets_stack_->append_element(active_subset_);
    }
}

CSubsetStack::~CSubsetStack()
{
    HF_UNREF(active_subsets_stack_);
    HF_UNREF(active_subset_);
}

void CSubsetStack::remove_all_subsets()
{
    for(index_t i = 0; i < active_subsets_stack_->get_num_elements()-1; ++i)
        active_subsets_stack_->delete_element(i);
    
    HF_UNREF(active_subset_);
}

void CSubsetStack::init()
{
    HF_ADD((CHFObject**)&active_subset_, "active_subset",
            "Currently active subset", MS_NOT_AVAILABLE);
    
    HF_ADD((CHFObject**)&active_subsets_stack_, "active_subsets_stack",
            "Stack of active subsets", MS_NOT_AVAILABLE);
    
    active_subset_ = NULL;
    active_subsets_stack_ = new CDynamicObjectArray();
    HF_REF(active_subsets_stack_);
}

void CSubsetStack::add_subset(HFVector<index_t> subset)
{
    if(active_subsets_stack_->get_num_elements())
    {
        // TODO
    }
    
    // TODO
    HF_NOTIMPLEMENTED;
}

void CSubsetStack::remove_subset()
{
    // TODO
    HF_NOTIMPLEMENTED;
}