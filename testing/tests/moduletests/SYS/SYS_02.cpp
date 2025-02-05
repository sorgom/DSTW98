//  ============================================================
//  test of Provider / Mapper
//  ============================================================
//  created by Manfred Sorgo
#include <testlib/TestGroupBase.h>
#include <SYS/Provider.h>

namespace test
{
    TEST_GROUP_BASE(SYS_02, TestGroupBase) {};

    TEST(SYS_02, T01)
    {
        SETUP()
        I_Provider& prov = Provider::instance();
        GenProjData<> data;
        prov.clear();
        L_CHECK_EQUAL(0, prov.size())

        STEP(1)
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            m_Mapper().expectAdd(n, data.addr(n));
            prov.add(data.at(n));
            CHECK_N_CLEAR()
        }
        L_CHECK_EQUAL(CAPACITY, prov.size())

        STEP(2)
        m_Ctrl().expectLog(COMP_SYS, RET_ERR_RANGE);
        prov.add(data.at(0));
        CHECK_N_CLEAR()

        STEP(3)
        ProjItem item = {};
        item.type = UINT8_MAX;
        m_Ctrl().expectLog(COMP_SYS, RET_ERR_PROJ);
        prov.clear();
        prov.add(item);
        CHECK_N_CLEAR()
    }

} // namespace
