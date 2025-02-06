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
        inline M_Elem(size_t num = 0) : M_Base("Elem"), mNum(num) {}

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
    protected:
        inline std::ostringstream& begin() const
        {
            mStream.str("");
            mStream << mName << '_' << mNum << "::";
            return mStream;
        }

        NOCOPY(M_Elem)
    private:
        const size_t mNum;
    };
} // namespace
#endif // _H
