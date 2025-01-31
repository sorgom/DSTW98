//  ============================================================
//  basic integral types and limits
//  ============================================================
//  created by Manfred Sorgo

#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <cstddef>

typedef unsigned char   UINT8;
typedef UINT8           BYTE;
typedef unsigned short  UINT16;
typedef unsigned int    UINT32;

typedef signed char     INT8;
typedef signed short    INT16;
typedef signed int      INT32;

typedef char            CHAR;

typedef void*           PTR;
typedef const void*     CPTR;

typedef CHAR*           C_STRING;
typedef const CHAR*     CONST_C_STRING;


#ifndef _MSC_VER
using std::size_t;
#endif

#if 0
#ifndef UINT8_MAX
#define UINT8_MAX 0xFF
#endif

#ifndef UINT16_MAX
#define UINT16_MAX 0xFFFF
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 0xFFFFFFFF
#endif

#ifndef INT8_MIN
#define INT8_MIN -0x7F
#endif

#ifndef INT8_MAX
#define INT8_MAX 0x7F
#endif

#ifndef INT16_MIN
#define INT16_MIN -0x7FFF
#endif

#ifndef INT16_MAX
#define INT16_MAX 0x7FFF
#endif

#ifndef INT32_MIN
#define INT32_MIN -0x7FFFFFFF
#endif

#ifndef INT32_MAX
#define INT32_MAX 0x7FFFFFFF
#endif
#endif

#endif // _H
