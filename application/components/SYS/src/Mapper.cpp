#include <SYS/Mapper.h>
#include <codebase/Mem.h>
#include <BAS/coding.h>
#include <SYS/IL.h>

INSTANCE_DEF(Mapper)

void Mapper::add(const ProjItem& data)
{
    if (mMap.hasSpace())
    {
        mMap.add(data.addr);
    }
    else
    {
        IL::getCtrl().log(COMP_SYS, RET_ERR_RANGE);
    }
}

void Mapper::index()
{
    if (not mMap.index())
    {
        IL::getCtrl().log(COMP_SYS, RET_ERR_STARTUP);
    }
}

void Mapper::fromFld(const ComTele& tele) const
{
    const PosRes res = mMap.find(tele.addr);

    if (res.valid)
    {
        IL::getProvider().at(res.pos).fromFld(tele.data);
    }
    else
    {
        IL::getCtrl().log(COMP_SYS, RET_ERR_MATCH);
    }
}

void Mapper::fromGui(const ComTele& tele) const
{
    const PosRes res = mMap.find(tele.addr);

    if (res.valid)
    {
        IL::getProvider().at(res.pos).fromGui(tele.data);
    }
    else
    {
        IL::getCtrl().log(COMP_SYS, RET_ERR_MATCH);
    }
}

void Mapper::toFld(const size_t id, const ComData& data) const
{
    if (mMap.size() > id)
    {
        const ComTele tele = { mMap.at(id), data };
        IL::getCom().toFld(tele);
    }
}

void Mapper::toGui(const size_t id, const ComData& data) const
{
    if (mMap.size() > id)
    {
        const ComTele tele = { mMap.at(id), data };
        IL::getCom().toGui(tele);
    }
}

void Mapper::reGui() const
{
    const I_Provider& prov = IL::getProvider();
    for (size_t i = 0; i < prov.size(); ++i)
    {
        prov.at(i).toGui();
    }
}
