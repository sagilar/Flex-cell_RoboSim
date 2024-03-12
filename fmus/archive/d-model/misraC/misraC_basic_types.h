/**
 * Basic type declarations
 */


typedef char char_t;
#ifndef _GCC_WRAP_STDINT_H
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
#endif
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

// typedef bool uint8_t;
typedef int bool;
typedef char* string;

#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
