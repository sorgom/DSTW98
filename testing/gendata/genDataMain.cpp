//  ============================================================
//  sample proj data generator
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/GenProjData.h>

INT32 main(INT32 argc, const CONST_C_STRING* argv)
{
    test::GenProjData<> data(argc > 1 ? argv[1] : DEF_PROJ_FILE);
    data.dump();
    return 0;
}
