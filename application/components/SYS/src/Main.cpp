#include <SYS/Main.h>
#include <SYS/IL.h>

INSTANCE_DEF(Main)

INT32 Main::smain(const INT32 argc, const CONST_C_STRING* const argv)
{
    I_Ctrl& ctrl = IL::getCtrl();
    ctrl.clear();

    if (argc > 1)
    {
        I_Com& com = IL::getCom();

        IL::getReader().read(argv[1]);

        if (ctrl.ok())
        {
            com.start();
            while (ctrl.ok())
            {
                com.check();
            }
        }
        com.stop();
    }
    return ctrl.maxerr();
}
