#include <SYS/Main.h>
#include <cstdio>
INT32 main(const INT32 argc, const CONST_C_STRING* argv)
{
    const INT32 ret = Main::instance().main(argc, argv);
    printf("ERR: %d\n", ret);
    return ret;
}
