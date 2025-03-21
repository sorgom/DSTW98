#include <SYS/Ctrl.h>
#include <BAS/Math.h>

#include <algorithm>
#include <iostream>

INSTANCE_DEF(Ctrl)

void Ctrl::log(E_Comp, E_Err ret)
{
    mErr = maxv(mErr, ret);
}
