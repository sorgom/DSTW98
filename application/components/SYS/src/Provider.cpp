#include <SYS/Provider.h>

INSTANCE_DEF(Provider)

bool Provider::add(const ProjItem& item)
{
    bool ok = mElems.hasSpace();
    if (ok)
    {
        const size_t pos = mElems.size();
        switch (item.type)
        {
            case TYPE_LCR:
                mElems.add(LCR(pos));
                break;
            case TYPE_LCR_UBK:
                mElems.add(LCR_UBK(pos));
                break;
            case TYPE_SIG_H:
                mElems.add(SIG_H(pos));
                break;
            case TYPE_SIG_N:
                mElems.add(SIG_N(pos));
                break;
            case TYPE_SIG_H_N:
                mElems.add(SIG_H_N(pos));
                break;
            case TYPE_TSW:
                mElems.add(TSW(pos));
                break;
            default:
                ok = false;
                break;
        }
    }
    return ok;
}
