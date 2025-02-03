//  ============================================================
//  checks replacement for static assert
//  ============================================================
//  created by Manfred Sorgo

#ifndef CHECKS_H
#define CHECKS_H

//  creates inline size check function for type
//  coverage proofs if executed
#define SIZE_CHECK(TYPE, SIZE) \
    inline bool sizeCheck ## TYPE() { return sizeof(TYPE) == (SIZE); }

#define ENUM_CHECK(VAL) \
    inline bool enumCheck ## VAL() { return VAL <= 255; }

//  prevent from unused variable warning
template <class T>
void use(const T&) {}

#endif // _H
