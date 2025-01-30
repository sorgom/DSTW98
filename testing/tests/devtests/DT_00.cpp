//  ============================================================
//  test of basics
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <BAS/StackArray.h>
#include <BAS/AddrMap.h>

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

    //  test type: equivalence class test
    //  ByteArray
    TEST(DT_00, T02)
    {
        STEP(1)
        PTR p = 0;
        ByteArray<10, 5> ba;
        L_CHECK_EQUAL(0, ba.size())

        STEP(2)
        SUBSTEPS()
        for (size_t n = 0; n < ba.capacity(); ++n)
        {
            STEP(n)
            p = ba.reserve();
            L_CHECK_FALSE(p == 0)
            L_CHECK_EQUAL(n + 1, ba.size())
        }
        ENDSTEPS()
        L_CHECK_EQUAL(ba.capacity(), ba.size())

        STEP(3)
        p = ba.reserve();
        L_CHECK_EQUAL(0, p)
        L_CHECK_EQUAL(ba.capacity(), ba.size())

        STEP(4)
        ba.clear();
        L_CHECK_EQUAL(0, ba.size())
    }

    struct TestData
    {
        size_t v1;
        size_t v2;
        inline TestData(size_t v1, size_t v2 = 0) : v1(v1), v2(v2) {}
    };

    template <size_t CAP>
    class TestArray : public StackArray<TestData, CAP, sizeof(TestData) + 10>
    {
    public:
        bool add(int v1, int v2 = 0)
        {
            PTR p = this->mBytes.reserve();
            const bool ok = p != 0;
            if (ok)
            {
                new (p) TestData(v1, v2);
            }
            return ok;
        }
    };

    template <size_t CAP>
    class TestIndex : public StackIndex<TestData, CAP, size_t>
    {
    public:
        inline TestIndex(const TestArray<CAP>& array) : StackIndex<TestData, CAP, size_t>(array) {}
    protected:
        size_t getKey(const TestData& td) const override
        {
            return td.v1;
        }
    };

    //  test type: equivalence class test
    //  StackArray
    TEST(DT_00, T03)
    {
        STEP(1)
        bool ok = false;
        TestArray<5> ta;
        TestIndex<5> ti(ta);

        L_CHECK_EQUAL(0, ta.size())

        STEP(2)
        SUBSTEPS()
        for (size_t n = 0; n < ta.capacity(); ++n)
        {
            STEP(n)
            ok = ta.add(2 * ta.capacity() - 2 * n, n);
            L_CHECK_TRUE(ok)
            L_CHECK_EQUAL(n + 1, ta.size())
        }
        ENDSTEPS()
        L_CHECK_EQUAL(ta.capacity(), ta.size())

        STEP(3)
        ok = ta.add(0);
        L_CHECK_FALSE(ok)

        STEP(4)
        SUBSTEPS()
        for (size_t n = 0; n < ta.capacity(); ++n)
        {
            STEP(n)
            const TestData& td = ta.at(n);
            L_CHECK_EQUAL(2 * ta.capacity() - 2 * n, td.v1)
            L_CHECK_EQUAL(n, td.v2)
        }
        ENDSTEPS()

        STEP(5)
        ok = ti.index();
        L_CHECK_TRUE(ok)

        STEP(6)
        SUBSTEPS()
        for (size_t n = 0; n < ta.capacity(); ++n)
        {
            STEP(n)
            const size_t key = 2 * ta.capacity() - 2 * n;
            const PosRes pr = ti.find(key);
            L_CHECK_TRUE(pr.valid)
            L_CHECK_EQUAL(n, pr.pos)
        }
        ENDSTEPS()
    }
} // namespace
