//  ============================================================
//  test of AddrMap
//  - should also cover all methods of container class Index
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <BAS/AddrMap.h>

namespace test
{

    #define TEST_CAP 10

    TEST_GROUP_BASE(BAS_02, TestGroupBase) {};

    //  test type: equivalence class test
    //  add and find data
    TEST(BAS_02, T01)
    {
        AddrMap<TEST_CAP> indx;

        const UINT8 tSize = TEST_CAP;
        const UINT8 tOffs = tSize - 1;
        bool ok = false;

        STEP(1)
        SUBSTEPS()
        // addresses from 9 .. 0
        for (UINT8 n = 0; n < tSize; ++n)
        {
            STEP(n)
            ok = indx.add(genComAddr(tOffs - n));
            L_CHECK_TRUE(ok)
        }
        ENDSTEPS()

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
    }

    // //  test type: equivalence class test
    // //  search for non-existing data
    // //  after successful index
    // TEST(BAS_02, T02)
    // {
    //     AcpIndex indx;

    //     // no data added
    //     STEP(1)
    //     {
    //         const auto ok = indx.index();
    //         L_CHECK_TRUE(ok);
    //         const auto fnd = indx.find(genComAddr(1));
    //         L_CHECK_FALSE(fnd.valid)
    //     }

    //     // add data 0 .. 19
    //     // index & find 20
    //     STEP(2)
    //     for (UINT8 n = 0; n < 10; ++n)
    //     {
    //         indx.add(genComAddr(n), n, n);
    //         indx.add(genComAddr(n + 10), n, n);
    //     }
    //     {
    //         const auto ok = indx.index();
    //         L_CHECK_TRUE(ok);
    //         const auto fnd = indx.find(genComAddr(20));
    //         L_CHECK_FALSE(fnd.valid)
    //     }
    // }
    // //  test type: equivalence class test
    // //  failure of index due to duplicate data
    // TEST(BAS_02, T03)
    // {
    //     AcpIndex indx;

    //     // no data added
    //     STEP(1)
    //     indx.add(genComAddr(1), 1, 1);
    //     indx.add(genComAddr(1), 2, 3);
    //     const auto ok = indx.index();
    //     L_CHECK_FALSE(ok);
    // }
} // namespace
