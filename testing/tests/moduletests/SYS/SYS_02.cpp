//  ============================================================
//  test of Provider / Mapper
//  ============================================================
//  created by Manfred Sorgo
#include <testlib/TestGroupBase.h>
#include <SYS/Provider.h>
#include <SYS/Mapper.h>

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
        SETUP()
        I_Mapper& mapper = Mapper::instance();
        const I_Mapper& cmapper = mapper;
        GenProjData<> data;
        mapper.clear();

        STEP(1)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            mapper.add(n, data.addr(n));
            CHECK_N_CLEAR()
        }
        ENDSTEPS()

        STEP(2)
        mapper.index();
        CHECK_N_CLEAR()

        STEP(3)
        const ComData cd(1, 2, 3, 4, 5, 6, 7, 8);
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            const ComTele tele = { data.addr(n), cd };
            m_Elems().at(n).expectFromFld(cd);
            cmapper.fromFld(tele);
            CHECK_N_CLEAR()
        }
        ENDSTEPS()

        STEP(4)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            const ComTele tele = { data.addr(n), cd };
            m_Elems().at(n).expectFromGui(cd);
            cmapper.fromGui(tele);
            CHECK_N_CLEAR()
        }
        ENDSTEPS()

        STEP(5)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            const ComTele tele = { data.addr(n), cd };
            m_Com().expectToFld(tele);
            cmapper.toFld(n, cd);
            CHECK_N_CLEAR()
        }
        ENDSTEPS()

        STEP(6)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            const ComTele tele = { data.addr(n), cd };
            m_Com().expectToGui(tele);
            cmapper.toGui(n, cd);
            CHECK_N_CLEAR()
        }
        ENDSTEPS()

        STEP(7)
        m_Provider().expectSize(CAPACITY);
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            m_Elems().at(n).expectToGui();
        }
        cmapper.reGui();
        CHECK_N_CLEAR()

        // TODO from coverage:
        //  - invalid address fromFld, fromGui
        //  - invalid id toFld, toGui
        //  - invalid position add
        //  - add with no space left
        //  - duplicate address add
    }
} // namespace
