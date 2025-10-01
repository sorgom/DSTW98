//  ============================================================
//  Interface Main
//  - the runtime
//  ============================================================
//  created by Manfred Sorgo

#ifndef I_MAIN_H
#define I_MAIN_H

#include <codebase/BaseTypes.h>

class I_Main
{
public:
    //  level
    //      0: do nothing
    //      1: read proj data
    //      2: read proj data and run tcp loop
    virtual INT32 main(INT32 level) const = 0;
};

#endif // _H
