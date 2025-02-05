//  ============================================================
//  test of Provider / Mapper
//  ============================================================
//  created by Manfred Sorgo
#include <testlib/TestGroupBase.h>
#include <SYS/Provider.h>

namespace test
{
    TEST_GROUP_BASE(SYS_02, TestGroupBase)
    {
        void checkType(UINT8 type, const I_Elem& elem)
        {
            switch (type)
            {
            case TYPE_LCR:
                L_CHECK_ELEM_TYPE(LCR, elem)
                break;
            case TYPE_LCR_UBK:
                L_CHECK_ELEM_TYPE(LCR_UBK, elem)
                break;
            case TYPE_SIG_H:
                L_CHECK_ELEM_TYPE(SIG_H, elem)
                break;
            case TYPE_SIG_N:
                L_CHECK_ELEM_TYPE(SIG_N, elem)
                break;
            case TYPE_SIG_H_N:
                L_CHECK_ELEM_TYPE(SIG_H_N, elem)
                break;
            case TYPE_TSW:
                L_CHECK_ELEM_TYPE(TSW, elem)
                break;
            default:
                break;
            }
        }
    };

    TEST(SYS_02, T01)
    {
        SETUP()
        I_Provider& prov = Provider::instance();
        const I_Provider& cprov = prov;
        GenProjData<> data;
        prov.clear();
        L_CHECK_EQUAL(0, prov.size())

        STEP(1)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            m_Mapper().expectAdd(n, data.addr(n));
            prov.add(data.at(n));
            CHECK_N_CLEAR()
            checkType(data.type(n), cprov.at(n));
            //  coverage: non const reference
            I_Elem& elem = prov.at(n);
            play(elem);
        }
        ENDSTEPS()
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
    TEST(SYS_02, T02)
    {

    }
} // namespace
