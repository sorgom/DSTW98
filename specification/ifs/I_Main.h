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
    virtual INT32 main(INT32 argc, const CONST_C_STRING* argv) const = 0;
};

#endif // _H
