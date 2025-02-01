//  ============================================================
//  proj data generator
//      presets all proj data
//      with element names in reversed alphanumerical order
//      from size down to 1
//      e.g. TSW, size 100:
//          "TSW 100 *" .. "TSW 001 *"
//
//      dumps data to file
//
//      additional features
//      -   set SIG type for signal data
//      -   set LCR type for level crossing data
//  ============================================================
//  created by Manfred Sorgo

#ifndef GENPROJDATA_H
#define GENPROJDATA_H

#include <ifs/DataTypes.h>
#include <testlib/NetTest.h>
#include <testlib/testValues.h>
#include <testlib/TestLib.h>
#include <fstream>
#include <vector>
#include <setup/Capacity.h>
#include <BAS/StackArray.h>

namespace test
{
    template <size_t CAP = CAPACITY>
    class GenProjData
    {
    public:
        const ComSetup mComSetup;

        GenProjData() :
            mComSetup(
                NetTest::toN(tcpPortFld),
                NetTest::toN(tcpPortGui),
                NetTest::toN(tcpPortCtrl),
                NetTest::toN(tcpTimeout)
            )
        {
            preset();
        }

        void preset()
        {
            items.clear();
            for (size_t n = 0; n < CAP; ++n)
            {
                const ProjItem item = { genComAddr(CAP - n), { getType(n) } };
                items.add(item);
            }
        }

        static UINT8 getType(const size_t pos)
        {
            static const UINT8 types[] = {
                TYPE_LCR,
                TYPE_LCR_UBK,
                TYPE_SEG,
                TYPE_SIG_H,
                TYPE_SIG_H_N,
                TYPE_SIG_N,
                TYPE_SIG_S,
                TYPE_TSW
            };
            return types[pos % sizeof(types)];
        }

        void dump(CONST_C_STRING filename) const
        {
            std::ofstream os(filename, std::ios::binary);
            if (os.good())
            {
                os.write(reinterpret_cast<const char*>(&mComSetup), sizeof(mComSetup));
                os.write((items.data()), items.dsize());
            }
            os.close();
        }

        ProjItem& at(size_t pos)
        {
            return items.at(pos);
        }

        StackArray<ProjItem, CAP> items;

        NOCOPY(GenProjData)
    };
} // namespace
#endif // _H
