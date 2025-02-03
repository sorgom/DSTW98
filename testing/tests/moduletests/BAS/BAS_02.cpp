//  ============================================================
//  test of AddrMap
//  - should also cover all methods of container class Index
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <BAS/AddrMap.h>

namespace test
{

    #define CAP 10

    TEST_GROUP_BASE(BAS_02, TestGroupBase) {};

    //  test type: equivalence class test
    //  add and find data
    TEST(BAS_02, T01)
    {
        AddrMap<CAP> indx;

        const UINT8 tSize = CAP;
        const UINT8 tOffs = tSize - 1;
        bool ok = false;

        STEP(1)
        SUBSTEPS()
        // addresses from 9 .. 0
        for (UINT8 n = 0; n < tSize; ++n)
        {
            STEP(n)
            L_CHECK_TRUE(indx.hasSpace())
            indx.add(genComAddr(tOffs - n));
        }
        ENDSTEPS()
        L_CHECK_EQUAL(CAP, indx.size())
        L_CHECK_FALSE(indx.hasSpace())

        STEP(2)
        ok = indx.index();
        L_CHECK_TRUE(ok)

        STEP(3)
        SUBSTEPS()
        //  search for addresses from 0 .. 9
        //  index returns valid data positions 9 .. 0
        for (UINT8 n = 0; n < tSize; ++n)
        {
            STEP(n)
            const ComAddr& cn = genComAddr(n);
            const PosRes fnd = indx.find(cn);
            L_CHECK_TRUE(fnd.valid)
            L_CHECK_EQUAL(static_cast<size_t>(tOffs - n), fnd.pos)
            const bool eq = (cn == indx.at(fnd));
            L_CHECK_TRUE(eq)
        }
        ENDSTEPS()

        STEP(4)
        indx.clear();
        L_CHECK_EQUAL(0, indx.size())
    }
} // namespace
