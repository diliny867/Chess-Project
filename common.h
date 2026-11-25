#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>


typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;


#define force_inline __attribute__((always_inline)) inline
#define unreachable  __builtin_unreachable()

#define minv(a, b) ((a) < (b) ? (a) : (b))
#define maxv(a, b) ((a) > (b) ? (a) : (b))

force_inline i32 clamp(i32 value, i32 min, i32 max){
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

force_inline i32 min(i32 a, i32 b){
    if(a < b) return a;
    return b;
}
