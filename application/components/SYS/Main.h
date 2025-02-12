//  ============================================================
//  class Main implements I_Main
//  - the runtime
//  ============================================================
//  created by Manfred Sorgo

#ifndef MAIN_H
#define MAIN_H

#include <ifs/I_Main.h>
#include <BAS/coding.h>

class Main : public I_Main
{
public:
    INT32 main(INT32 argc, const CONST_C_STRING* argv) const;

    INSTANCE_DEC(Main)
    NOCOPY(Main)
private:
    inline Main() {}
};

#endif // _H
