#include <SYS/Main.h>
#include <cstdio>
INT32 main(const INT32 argc, const CONST_C_STRING*)
{
    const INT32 ret = Main::instance().main(argc - 1);
    printf("ERR: %d\n", ret);
    return ret;
}
