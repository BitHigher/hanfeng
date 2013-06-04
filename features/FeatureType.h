/* 
 * File:   FeatureType.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午5:34
 */

#ifndef FEATURETYPE_H
#define FEATURETYPE_H

namespace hanfeng
{
  enum EFeatureProperty
{
    FP_NONE = 0,
    FP_DOT = 1,
    FP_STREAMING_DOT = 2
};

enum EFeatureClass
{
    C_UNKNOWN = 0,
    C_DENSE = 10,
    C_SPARSE = 20,
    C_STRING = 30
};
    
enum EFeatureType
{
    F_UNKNOWN = 0,
    F_BOOL = 5,
    F_CHAR = 10,
    F_BYTE = 20,
    F_DREAL = 100
};

};

#endif	/* FEATURETYPE_H */

