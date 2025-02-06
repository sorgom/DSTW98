#include <SYS/IL.h>
#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;

int main(const INT32 argc, const CONST_C_STRING* const argv)
{
    I_Ctrl& ctrl = IL::getCtrl();
    I_Com& com = IL::getCom();

    IL::getReader().read("dstw.proj");

    if (ctrl.ok())
    {
        com.start();
    }

    cout
        << "NUM: " << setw(5) << IL::getProvider().size() << '\n'
        << "ERR: " << setw(5) << ctrl.maxerr() << '\n'
    ;

    if (argc > 1)
    {
        while (ctrl.ok())
        {
            com.check();
        }
    }
    com.stop();
    return ctrl.maxerr();
}
