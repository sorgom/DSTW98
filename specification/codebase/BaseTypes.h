//  ============================================================
//  basic integral types
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
    #define nullptr 0
#endif

#endif // _H
