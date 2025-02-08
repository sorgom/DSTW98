#include <SYS/Main.h>
#include <SYS/IL.h>
#include <cstdio>

INSTANCE_DEF(Main)

INT32 Main::smain(const INT32 argc, const CONST_C_STRING* const argv)
{
    I_Ctrl& ctrl = IL::getCtrl();

    if (argc > 1)
    {
        I_Com& com = IL::getCom();

        IL::getReader().read(argv[1]);

        if (ctrl.ok())
        {
            printf("NUM: %5lu\n", IL::getProvider().size());
            com.start();
        }

        if (argc > 1)
        {
            while (ctrl.ok())
            {
                com.check();
            }
        }
        com.stop();
    }

    printf("ERR: %5d\n", ctrl.maxerr());
    return ctrl.maxerr();
}
