//  ============================================================
//  block any copying
//  ============================================================
//  created by Manfred Sorgo
#ifndef NOCOPY_H
#define NOCOPY_H

//  disable copy constructor and copy operator
#define NOCOPY(CLASS) \
private: CLASS(const CLASS&); CLASS& operator = (const CLASS&);

//  disable default constructor
#define NODEF(CLASS) private: CLASS();

#endif // _H
