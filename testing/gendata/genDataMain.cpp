//  ============================================================
//  sample proj data generator
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/GenProjData.h>

INT32 main(INT32 argc, const CONST_C_STRING* argv)
{
    test::GenProjData<> data;
    data.dump();
    return 0;
}
