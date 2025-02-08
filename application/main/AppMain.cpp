#include <SYS/Main.h>

INT32 main(const INT32 argc, const CONST_C_STRING* argv)
{
    return Main::instance().main(argc, argv);
}
