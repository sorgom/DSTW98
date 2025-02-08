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
    inline INT32 main(INT32 argc, const CONST_C_STRING* argv) const
    {
        return smain(argc, argv);
    }

    INSTANCE_DEC(Main)
    NOCOPY(Main)
private:
    inline Main() {}
    static INT32 smain(INT32 argc, const CONST_C_STRING* argv);
};

#endif // _H
