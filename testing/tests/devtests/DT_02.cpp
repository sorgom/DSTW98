//  ============================================================
//  test of test features
//  - output of fixed size strings
//  - placement new substitution
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <comparators/ostreams.h>

#include <sstream>
#include <new>

namespace test
{

    TEST_GROUP_BASE(DT_02, TestGroupBase) {};

    TEST(DT_02, T01)
    {
        STEP(1)
        CHAR chars[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

        std::ostringstream os;
        os << fixT(chars);
        STRCMP_EQUAL("0123456789", os.str().c_str());

        STEP(2)
        chars[4]  = 0;
        chars[7] = 127;
        os.str("");
        os << fixT(chars);
        STRCMP_EQUAL("0123*56*89", os.str().c_str());
    }
    TEST(DT_02, T02)
    {
        STEP(1)
        ComTele tele = { ComAddr(), ComData(1, 2, 3, 4, 5, 6, 7, 8) };
        const ComData cd(11, 12, 13);
        std::memcpy((void*) &tele.data, &cd, sizeof(ComData));
        L_CHECK_EQUAL(11, tele.data.param1);
        L_CHECK_EQUAL(12, tele.data.param2);
        L_CHECK_EQUAL(13, tele.data.param3);
        L_CHECK_EQUAL(PARAM_UNDEF, tele.data.param4);
        L_CHECK_EQUAL(PARAM_UNDEF, tele.data.param5);
        L_CHECK_EQUAL(PARAM_UNDEF, tele.data.param6);
        L_CHECK_EQUAL(PARAM_UNDEF, tele.data.param7);
        L_CHECK_EQUAL(PARAM_UNDEF, tele.data.param8);
    }
}
