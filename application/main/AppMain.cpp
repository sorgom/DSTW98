#include <SYS/IL.h>
#include <cstdio>

int main(const INT32 argc, const CONST_C_STRING* const)
{
    I_Ctrl& ctrl = IL::getCtrl();
    I_Com& com = IL::getCom();

    IL::getReader().read("dstw.proj");

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
    printf("ERR: %5d\n", ctrl.maxerr());
    return ctrl.maxerr();
}
