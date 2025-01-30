//  ============================================================
//  test of basics
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>

namespace test
{
    TEST_GROUP_BASE(DT_00, TestGroupBase)
    {
        inline size_t getNext(size_t& size, bool valid)
        {
            return valid ? size++ : 0;
        }
    };

    // 5.16 Conditional operator [expr.cond]
    // 1 Conditional expressions group right-to-left. The first expression is contextually converted to bool (Clause 4).
    // It is evaluated and if it is true, the result of the conditional expression is the value of the second expression,
    // otherwise that of the third expression. Only one of the second and third expressions is evaluated. Every value
    // computation and side effect associated with the first expression is sequenced before every value computation
    // and side effect associated with the second or third expression.
    TEST(DT_00, T01)
    {
        STEP(1)
        size_t size = 0;
        size_t pos = 0;
        L_CHECK_EQUAL(0, size)

        STEP(2)
        pos = getNext(size, true);
        L_CHECK_EQUAL(0, pos)
        L_CHECK_EQUAL(1, size)

        STEP(3)
        pos = getNext(size, false);
        L_CHECK_EQUAL(0, pos)
        L_CHECK_EQUAL(1, size)

        STEP(4)
        pos = getNext(size, true);
        L_CHECK_EQUAL(1, pos);
        L_CHECK_EQUAL(2, size);
    }

} // namespace
