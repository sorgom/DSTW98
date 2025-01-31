//  ============================================================
//  mock for interface Elem derived classes
//  ============================================================
//  created by Manfred Sorgo

#ifndef M_ELEM_H
#define M_ELEM_H

#include <ifs/I_Elem.h>
#include "M_Base.h"

namespace test
{
    class M_Elem : public I_Elem, private M_Base
    {
    public:
        INSTANCE_DEC(M_Elem)

        inline void fromFld(const ComData& data)
        {
            call("fromFld").TPARAM(ComData, data);
        }
        inline void expectFromFld(const ComData& data) const
        {
            expect("fromFld").TPARAM(ComData, data);
        }

        inline void fromGui(const ComData& data)
        {
            call("fromGui").TPARAM(ComData, data);
        }
        inline void expectFromGui(const ComData& data) const
        {
            expect("fromGui").TPARAM(ComData, data);
        }

        inline void toGui() const
        {
            call("toGui");
        }
        inline void expectToGui() const
        {
            expect("toGui");
        }
        inline void expectToGui(UINT16 num) const
        {
            expect(num, "toGui");
        }

        NOCOPY(M_Elem)
    private:
        inline M_Elem() : M_Base("Elem") {}
    };
} // namespace
#endif // _H
