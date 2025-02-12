//  ============================================================
//  test of basics & mocks
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <testlib/wait.h>
#include <ctime>

namespace test
{
    TEST_GROUP_BASE(DT_01, TestGroupBase) {};

#ifdef _WIN32
//  no loss of data coverting time_t to UINT32
#pragma warning(disable:4244)
#endif

    TEST(DT_01, T01)
    {
        STEP(1)
        const time_t t1 = time(nullptr);
        while (time(nullptr) == t1)
        {
            wait(10);
        }
        const time_t t2 = time(nullptr);
        const UINT32 d1 = static_cast<UINT32>(t2 - t1);
        L_CHECK_EQUAL(1, d1)

        STEP(2)
        wait(1000);
        const time_t t3 = time(nullptr);
        const UINT32 d2 = static_cast<UINT32>(t3 - t2);
        L_CHECK_EQUAL(1, d2)
    }
#ifdef _WIN32
#pragma warning(default:4244)
#endif

    //  call mock explicitly
    TEST(DT_01, T02)
    {
        STEP(1)
        ComData d(11);
        L_CHECK_EQUAL(PARAM_UNDEF, d.param2)


        STEP(2)
        ComData d1(11, 111);
        m_Mapper().expectToFld(1, d1);
        m_Mapper().toFld(1, ComData(11, 111));
        CHECK_N_CLEAR()
    }
}
