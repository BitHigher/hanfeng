/* 
 * File:   LeastSquaresRegression.cpp
 * Author: zhf
 * 
 * Created on 2013年6月5日, 上午11:42
 */

#include "../lib/config.h"

#ifdef HAVE_LAPACK

#include "LeastSquaresRegression.h"

using namespace hanfeng;

CLeastSquaresRegression::CLeastSquaresRegression()
: CLinearRidgeRegression()
{
    tau_ = 0;
}

CLeastSquaresRegression::CLeastSquaresRegression(
                                CDenseFeatures<float64_t>* data, CLabels* lab)
: CLinearRidgeRegression(0, data, lab)
{
}

CLeastSquaresRegression::~CLeastSquaresRegression()
{
}

#endif  /* HAVE_LAPACK */