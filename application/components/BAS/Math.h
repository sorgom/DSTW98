//  ============================================================
//  calculations
//  ============================================================
//  created by Manfred Sorgo

#ifndef MATH_H
#define MATH_H

#define MAXV(A, B) ((B) > (A) ? (B) : (A))

template <class T>
T maxv(T a, T b)
{
    return b > a ? b : a;
}

#endif // _H
