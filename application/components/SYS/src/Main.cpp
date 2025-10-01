#include <SYS/Main.h>
#include <SYS/IL.h>

INSTANCE_DEF(Main)

INT32 Main::main(const INT32 level) const
{
    I_Ctrl& ctrl = IL::getCtrl();
    ctrl.clear();

    if (level > 0)
    {
        IL::getReader().read();

        if ((level > 1) and ctrl.ok())
        {
            I_Com& com = IL::getCom();
            com.start();
            while (ctrl.ok())
            {
                com.check();
            }
            com.stop();
        }
    }
    return ctrl.maxerr();
}
