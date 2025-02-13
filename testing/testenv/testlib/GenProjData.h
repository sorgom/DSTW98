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

#ifndef GEN_PROJDATA_H
#define GEN_PROJDATA_H

#include <BAS/StackArray.h>
#include <ifs/DataTypes.h>
#include <CFG/Setup.h>
#include <testlib/NetTest.h>
#include <testlib/TestLib.h>
#include <testlib/testValues.h>

#include <fstream>

//  current number of element types
#define NUM_ALL_TYPES 6

namespace test
{
    template <size_t SIZE = CAPACITY>
    class GenProjData
    {
    public:
        const ComSetup setup;

        GenProjData() :
            setup(
                NetTest::toN(tcpPortFld),
                NetTest::toN(tcpPortGui),
                NetTest::toN(tcpPortCtrl),
                NetTest::toN(tcpTimeout)
            )
        {
            preset();
        }

        inline static size_t size()
        {
            return SIZE;
        }

        void preset()
        {
            items.clear();
            for (size_t n = 0; n < SIZE; ++n)
            {
                const ProjItem item = {};
                items.add(item);
            }
            //  alternating types
            //  COM addresses in reversed order from SIZE down to 1
            for (size_t n = 0; n < SIZE; ++n)
            {
                ProjItem& item = items.at(n);
                genComAddr(item.addr, SIZE - n);
                item.type = getType(n);
            }
        }

        void dump(UINT32 num = SIZE, size_t size = SIZE)
        {
            if (openOs())
            {
                writeNum(num);
                writeSetup();
                for (size_t n = 0; (n < size) and  n < SIZE; ++n)
                {
                    writeItem(n);
                }
                os.close();
            }
        }

        //  file size less than header
        void dumpTooSmall()
        {
            if (openOs())
            {
                writeSetup();
                os.close();
            }
        }

        inline const ProjItem& at(size_t pos)
        {
            return items.at(pos);
        }

        inline UINT8 type(size_t pos)
        {
            return items.at(pos).type;
        }
        inline const ComAddr& addr(size_t pos)
        {
            return items.at(pos).addr;
        }

    private:
        static UINT8 getType(const size_t n)
        {
            static const UINT8 types[NUM_ALL_TYPES] = {
                TYPE_LCR,
                TYPE_LCR_UBK,
                TYPE_SIG_H,
                TYPE_SIG_H_N,
                TYPE_SIG_N,
                TYPE_TSW
            };
            return types[n % sizeof(types)];
        }

        void writeNum(UINT32 num = SIZE)
        {
            const UINT32 numN = NetTest::toN(num);
            os.write(reinterpret_cast<const char*>(&numN), sizeof(UINT32));
        }
        void writeSetup(INT32 err = 0)
        {
            os.write(reinterpret_cast<const char*>(&setup), sizeof(setup) + err);
        }
        void writeItem(size_t pos)
        {
            os.write(reinterpret_cast<const char*>(&items.at(pos)), sizeof(ProjItem));
        }

        bool openOs()
        {
            os.open(PROJ_FILE, std::ios::binary);
            const bool ok = os.good();
            if (not ok) os.close();
            return ok;
        }

        StackArray<ProjItem, SIZE> items;
        std::ofstream os;
        NOCOPY(GenProjData)
    };

    //  minimal proj data to get all element types tested
    typedef GenProjData<NUM_ALL_TYPES> MinProjData;
} // namespace
#endif // _H
