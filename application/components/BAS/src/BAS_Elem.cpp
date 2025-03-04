#include <BAS/BAS_Elem.h>
#include <SYS/IL.h>

void X_Elem::toFld(
    UINT8 p1,
    UINT8 p2,
    UINT8 p3,
    UINT8 p4,
    UINT8 p5,
    UINT8 p6,
    UINT8 p7,
    UINT8 p8) const
{
    IL::getMapper().toFld(mId, ComData(p1, p2, p3, p4, p5, p6, p7, p8));
}

void X_Elem::toGui(
    UINT8 p1,
    UINT8 p2,
    UINT8 p3,
    UINT8 p4,
    UINT8 p5,
    UINT8 p6,
    UINT8 p7,
    UINT8 p8) const
{
    IL::getMapper().toGui(mId, ComData(p1, p2, p3, p4, p5, p6, p7, p8));
}

void X_Elem::logMismatch(E_Comp comp)
{
    IL::getCtrl().log(comp, RET_ERR_MATCH);
}
