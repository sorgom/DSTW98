//  ============================================================
//  mock for interface Mapper
//  ============================================================
//  created by Manfred Sorgo
#ifndef M_MAPPER_H
#define M_MAPPER_H

#include <ifs/I_Mapper.h>
#include "M_Base.h"

namespace test
{
    class M_Mapper : public I_Mapper, private M_Base
    {
    public:
        INSTANCE_DEC(M_Mapper)

        inline void clear()
        {
            call("clear");
        }
        inline void expectClear() const
        {
            expect("clear");
        }

        inline void index()
        {
            call("index");
        }
        inline void expectIndex() const
        {
            expect("index");
        }

        inline bool add(const ProjItem& data)
        {
            return static_cast<bool>(call("add").TPARAM(ProjItem, data).RETURN_DEF_BOOL(true));
        }
        inline void expectAdd(const ProjItem& data, bool ret = true) const
        {
            expect("add").TPARAM(ProjItem, data).AND_RETURN_BOOL(ret);
        }
        inline void expectAdd(UINT16 num, bool ret = true) const
        {
            expect(num, "add").IGNORE().AND_RETURN_BOOL(ret);
        }

        inline void fromFld(const ComTele& tele) const
        {
            call("fromFld").TPARAM(ComTele, tele);
        }
        inline void expectFromFld(const ComTele& tele) const
        {
            expect("fromFld").TPARAM(ComTele, tele);
        }

        inline void fromGui(const ComTele& tele) const
        {
            call("fromGui").TPARAM(ComTele, tele);
        }
        inline void expectFromGui(const ComTele& tele) const
        {
            expect("fromGui").TPARAM(ComTele, tele);
        }

        inline void toFld(size_t id, const ComData& data) const
        {
            call("toFld").PARAM(id).TPARAM(ComData, data);
        }
        inline void expectToFld(size_t id, const ComData& data) const
        {
            expect("toFld").PARAM(id).TPARAM(ComData, data);
        }

        inline void toGui(size_t id, const ComData& data) const
        {
            call("toGui").PARAM(id).TPARAM(ComData, data);
        }
        inline void expectToGui(size_t id, const ComData& data) const
        {
            expect("toGui").PARAM(id).TPARAM(ComData, data);
        }

        inline void reGui() const
        {
            call("reGui");
        }
        inline void expectReGui() const
        {
            expect("reGui");
        }

        NOCOPY(M_Mapper)
    private:
        inline M_Mapper() : M_Base("Mapper") {}
    };
}
#endif // _H
