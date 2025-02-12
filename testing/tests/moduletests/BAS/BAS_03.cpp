//  ============================================================
//  test of Net
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <testlib/NetTest.h>
#include <BAS/Net.h>

namespace test
{
    TEST_GROUP_BASE(BAS_03, TestGroupBase)
    {};

    //  test type: equivalence class test
    //  byte order conversion: unsigned
    TEST(BAS_03, T01)
    {
        STEP(1)
        {
            const UINT16 h = 0x010F;
            const UINT16 na = Net::toN(h);
            const UINT16 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const UINT16 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
        STEP(2)
        {
            const UINT32 h = 0x01020408;
            const UINT32 na = Net::toN(h);
            const UINT32 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const UINT32 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
    }

    //  test type: equivalence class test
    //  byte order conversion: signed
    TEST(BAS_03, T02)
    {
        STEP(1)
        {
            const INT16 h = INT16_MAX;
            const INT16 na = Net::toN(h);
            const INT16 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const INT16 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
        STEP(2)
        {
            const INT16 h = INT16_MIN;
            const INT16 na = Net::toN(h);
            const INT16 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const INT16 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
        STEP(3)
        {
            const INT32 h = INT32_MAX;
            const INT32 na = Net::toN(h);
            const INT32 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const INT32 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
        STEP(3)
        {
            const INT32 h = INT32_MIN;
            const INT32 na = Net::toN(h);
            const INT32 nt = NetTest::toN(h);
            L_CHECK_EQUAL(nt, na);

            const INT32 ha = Net::toH(na);
            L_CHECK_EQUAL(h, ha);
        }
    }

} // namespace
