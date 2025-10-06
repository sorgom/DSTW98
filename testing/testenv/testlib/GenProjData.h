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

#ifndef GEN_PROJ_DATA_H
#define GEN_PROJ_DATA_H

#include <CFG/Setup.h>
#include <ifs/DataTypes.h>
#include <testlib/NetTest.h>
#include <testlib/TestArray.h>
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
        GenProjData()
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
                const ProjItem item = { genComAddr(SIZE - n), getType(n) };
                items.add(item);
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
            return types[n % NUM_ALL_TYPES];
        }

        void writeNum(UINT32 num = SIZE)
        {
            const UINT32 numN = NetTest::toN(num);
            os.write(reinterpret_cast<const char*>(&numN), sizeof(UINT32));
        }
        void writeNum(UINT16 num)
        {
            const UINT16 numN = NetTest::toN(num);
            os.write(reinterpret_cast<const char*>(&numN), sizeof(UINT16));
        }
        void writeSetup()
        {
            writeNum(tcpPortFld);
            writeNum(tcpPortGui);
            writeNum(tcpPortCtrl);
            writeNum(tcpTimeout);
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

        TestArray<ProjItem, SIZE> items;
        std::ofstream os;
        NOCOPY(GenProjData)
    };

    //  minimal proj data to get all element types tested
    using MinProjData = GenProjData<NUM_ALL_TYPES>;
} // namespace
#endif // _H
