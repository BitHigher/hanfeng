/* 
 * File:   CustomKernel.cpp
 * Author: zhf
 * 
 * Created on 2013年6月11日, 下午8:02
 */

#include "CustomKernel.h"

using namespace hanfeng;

CCustomKernel::CCustomKernel()
: CKernel(10), kmatrix_(), upper_diagonal_(false)
{
    init();
}

CCustomKernel::~CCustomKernel()
{
    // TODO 
}

void CCustomKernel::init()
{
    // TODO init
}

bool CCustomKernel::init(CFeatures* l, CFeatures* r)
{
    // TODO init
}