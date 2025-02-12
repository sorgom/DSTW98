#include <SYS/Main.h>
#include <SYS/IL.h>

INSTANCE_DEF(Main)

INT32 Main::main(const INT32 argc, const CONST_C_STRING* const) const
{
    I_Ctrl& ctrl = IL::getCtrl();
    ctrl.clear();

    IL::getReader().read();

    if (ctrl.ok())
    {
        I_Com& com = IL::getCom();
        com.start();

        if (argc > 1)
        {
            while (ctrl.ok())
            {
                com.check();
            }
        }
        com.stop();
    }
    return ctrl.maxerr();
}
