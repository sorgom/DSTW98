//  ============================================================
//  Mapper implements I_Mapper
//  ============================================================
//  created by Manfred Sorgo
#ifndef MAPPER_H
#define MAPPER_H

#include <BAS/AddrMap.h>
#include <BAS/coding.h>
#include <ifs/I_Mapper.h>
#include <ifs/I_Provider.h>
#include <setup/Capacity.h>

class Mapper : public I_Mapper
{
public:

    inline void clear() { mMap.clear(); }
    void index();

    void add(size_t pos, const ComAddr& addr);

    void fromFld(const ComTele& tele) const;
    void fromGui(const ComTele& tele) const;

    void toFld(size_t id, const ComData& data) const;
    void toGui(size_t id, const ComData& data) const;

    void reGui() const;

    INSTANCE_DEC(Mapper)
    NOCOPY(Mapper)

private:
    AddrMap<CAPACITY> mMap;
    inline Mapper() {}
};
#endif // _H
