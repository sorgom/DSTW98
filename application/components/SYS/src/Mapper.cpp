#include <SYS/Mapper.h>
#include <codebase/Mem.h>
#include <BAS/coding.h>
#include <SYS/IL.h>

INSTANCE_DEF(Mapper)

void Mapper::index()
{
    if (not mMap.index())
    {
        IL::getLog().log(COMP_SYS, RET_ERR_STARTUP);
    }
}

void Mapper::fromFld(const ComTele& tele) const
{
    const PosRes res = mMap.find(tele.addr);

    if (res.valid)
    {
    }
    else
    {
        IL::getLog().log(COMP_SYS, RET_ERR_MATCH);
    }
}

void Mapper::fromGui(const ComTele& tele) const
{
    const PosRes res = mMap.find(tele.addr);

    if (res.valid)
    {
    }
    else
    {
        IL::getLog().log(COMP_SYS, RET_ERR_MATCH);
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
}
