#include <BAS/BAS_Elem.h>
#include <SYS/IL.h>

void X_Elem::sndFld(const ComData& data) const
{
    IL::getMapper().toFld(mId, data);
}

void X_Elem::sndGui(const ComData& data) const
{
    IL::getMapper().toGui(mId, data);
}

void X_Elem::logMismatch(E_Comp comp)
{
    IL::getCtrl().log(comp, ERR_MATCH);
}
