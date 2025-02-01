#include <SYS/Provider.h>
#include <SYS/IL.h>
#include <ifs/values.h>

INSTANCE_DEF(Provider)

void Provider::add(const ProjItem& item)
{
    if (mElems.hasSpace())
    {
        const size_t pos = mElems.size();
        switch (item.type)
        {
            case TYPE_LCR:
                add<LCR>(pos);
                break;
            case TYPE_LCR_UBK:
                add<LCR_UBK>(pos);
                break;
            case TYPE_SIG_H:
                add<SIG_H>(pos);
                break;
            case TYPE_SIG_N:
                add<SIG_N>(pos);
                break;
            case TYPE_SIG_H_N:
                add<SIG_H_N>(pos);
                break;
            case TYPE_TSW:
                add<TSW>(pos);
                break;
            default:
                IL::getCtrl().log(COMP_SYS, RET_ERR_PROJ);
                break;
        }
    }
    else
    {
        IL::getCtrl().log(COMP_SYS, RET_ERR_RANGE);
    }
}
