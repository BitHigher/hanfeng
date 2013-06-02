/* 
 * File:   Subset.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午4:27
 */

#ifndef STRUCTURE_SUBSET_H
#define STRUCTURE_SUBSET_H

#include "../base/HFObject.h"
#include "HFVector.h"

namespace hanfeng
{

class CSubset : public CHFObject {
    
    friend class CSubsetStack;
    
public:
    CSubset();
    CSubset(HFVector<index_t> subset_idx);
    virtual ~CSubset();
    
    inline const char* get_name() const {return "Subset"; }
    
    inline index_t get_size() const {return subset_index_.vlen;} 
    inline HFVector<index_t> get_subset_index() const {return subset_index_;}


private:
    void init();
    
private:
    HFVector<index_t> subset_index_;
};

}
#endif	/* STRUCTURE_SUBSET_H */

