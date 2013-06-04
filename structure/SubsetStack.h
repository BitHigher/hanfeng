/* 
 * File:   SubsetStack.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午12:28
 */

#ifndef STRUCTURE_SUBSETSTACK_H
#define STRUCTURE_SUBSETSTACK_H

#include "../base/HFObject.h"
#include "../io/HFIO.h"
#include "../structure/HFVector.h"

#include "Subset.h"

namespace hanfeng
{

class CSubsetStack : public CHFObject {
public:
    CSubsetStack();
    CSubsetStack(const CSubsetStack& orig);
    virtual ~CSubsetStack();
    
    
    virtual bool has_subsets()
    {
        // TODO
        return false;
    }
    
    inline int32_t get_size()
    {
        if(!has_subsets())
            HF_WARNING("CSubsetStack::get_size() No subset in stack");
        
        return has_subsets() ? active_subset_->get_size(): -1;
    }
    
    inline index_t subset_idx_conversion(index_t idx) const
    {
        return active_subset_ ? 
            active_subset_->subset_index_.vector[idx]:idx;
    }
    
    inline const char* get_name() const {return "SubsetStack";}
    
    virtual void add_subset(HFVector<index_t> subset);
    virtual void remove_subset();
    virtual void remove_all_subsets();
    
private:
    CSubset *active_subset_;
};

}
#endif	/* STRUCTURE_SUBSETSTACK_H */

