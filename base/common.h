/* 
 * File:   common.h
 * Author: zhf
 *
 * Created on 2013年5月24日, 下午9:49
 */

#ifndef BASE_COMMON_H
#define BASE_COMMON_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef float float32_t;
typedef double float64_t;
typedef long double floatmax_t;

typedef int32_t index_t;

#define STRING_LEN 256
#define STRING_LEN_STR "256"
typedef char string_t[STRING_LEN];

#include "memory.h"

#include "../lib/config.h"

#endif	/* BASE_COMMON_H */

