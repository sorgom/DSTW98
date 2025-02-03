//  ============================================================
//  test of Containers
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <BAS/StackArray.h>

namespace test
{

    TEST_GROUP_BASE(BAS_01, TestGroupBase)
    {
    protected:
        INT32 genv(const INT32 n)
        {
            return (n % 3 == 0 ? n : -n);
        }
        INT32 gendup(const INT32 n)
        {
            return (n % 3 == 0 ? 123 : -n);
        }
    };

    struct I_Data
    {
        virtual INT32 v1() const = 0;
        virtual INT32 v2() const = 0;
        virtual ~I_Data() {}
    };

    struct BaseData : I_Data
    {
        inline INT32 v1() const { return m1; }
        virtual INT32 v2() const { return 0; }
        inline BaseData(INT32 v1) : m1(v1) {}
    private:
        const INT32 m1;
    };

    struct ExtendedData : BaseData
    {
        inline INT32 v2() const { return m2; }
        inline ExtendedData(INT32 v1, INT32 v2 = 0) : BaseData(v1), m2(v2) {}
    private:
        const INT32 m2;
    };

    template <INT32 CAP>
    class TestArray : public StackArray<I_Data, CAP, sizeof(ExtendedData)>
    {};

    template <INT32 CAP>
    class TestIndex : public StackIndex<I_Data, CAP, INT32>
    {
    public:
        inline TestIndex(const TestArray<CAP>& array) : StackIndex<I_Data, CAP, INT32>(array) {}
    protected:
        INT32 getKey(const I_Data& td) const
        {
            return td.v1();
        }
    };

    //  test type: equivalence class test
    //  StackArray, StackIndex
    TEST(BAS_01, T02)
    {
        STEP(1)
        bool ok = false;
        #define CAP 5
        TestArray<CAP> ta;
        TestIndex<CAP> ti(ta);

        L_CHECK_EQUAL(0, ta.size())
        L_CHECK_EQUAL(CAP, ta.capacity())

        STEP(2)
        SUBSTEPS()
        for (INT32 n = 0; n < CAP; ++n)
        {
            STEP(n)
            L_CHECK_TRUE(ta.hasSpace())
            ta.add(ExtendedData(genv(n), n));
        }
        ENDSTEPS()
        L_CHECK_EQUAL(CAP, ta.size())
        L_CHECK_FALSE(ta.hasSpace())

        STEP(3)
        SUBSTEPS()
        for (INT32 n = 0; n < CAP; ++n)
        {
            STEP(n)
            const I_Data& d = ta.at(n);
            L_CHECK_EQUAL(genv(n), d.v1())
            L_CHECK_EQUAL(n, d.v2())
        }
        ENDSTEPS()

        STEP(4)
        ok = ti.index();
        L_CHECK_TRUE(ok)

        STEP(5)
        SUBSTEPS()
        for (INT32 n = 0; n < CAP; ++n)
        {
            STEP(n)
            const INT32 key = genv(n);
            const PosRes pr = ti.find(key);
            L_CHECK_TRUE(pr.valid)
            L_CHECK_EQUAL(n, static_cast<INT32>(pr.pos))
        }
        ENDSTEPS()

        STEP(6)
        {
            const PosRes pr = ti.find(INT32_MAX);
            L_CHECK_FALSE(pr.valid)
        }
        {
            const PosRes pr = ti.find(INT32_MIN);
            L_CHECK_FALSE(pr.valid)
        }
        STEP(7)
        ta.clear();
        L_CHECK_EQUAL(0, ta.size())
        {
            const PosRes pr = ti.find(0);
            L_CHECK_FALSE(pr.valid)
        }
        for (INT32 n = 0; n < CAP; ++n)
        {
            ta.add(ExtendedData(n, n));
        }
        L_CHECK_EQUAL(CAP, ta.size())

        STEP(8)
        ok = ti.index();
        L_CHECK_TRUE(ok)

        STEP(9)
        ta.clear();
        L_CHECK_EQUAL(0, ta.size())
        for (INT32 n = 0; n < CAP; ++n)
        {
            ta.add(ExtendedData(gendup(n), n));
        }
        L_CHECK_EQUAL(CAP, ta.size())

        STEP(10)
        ok = ti.index();
        L_CHECK_FALSE(ok)
    }
} // namespace
