//  ============================================================
//  checks replacement for static assert
//  ============================================================
//  created by Manfred Sorgo

#ifndef CHECKS_H
#define CHECKS_H

//  creates inline size check function for type
//  coverage proofs if executed
#define SIZE_CHECK(TYPE, SIZE) \
    typedef CHAR sizeCheck ## TYPE[(sizeof(TYPE) == (SIZE)) ? 1 : -1];


#endif // _H
