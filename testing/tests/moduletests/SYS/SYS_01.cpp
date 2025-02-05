//  ============================================================
//  test of module Reader, Ctrl
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <SYS/Reader.h>
#include <SYS/Ctrl.h>

namespace test
{
    class TestGroupRDR : public TestGroupBase
    {
    protected:
        static const CONST_C_STRING fname;
        void expectClear()
        {
            m_Mapper().expectClear();
            m_Provider().expectClear();
        }
        void expectFail()
        {
            expectClear();
            m_Ctrl().expectLog(COMP_SYS, RET_ERR_STARTUP);
        }
    };

    const CONST_C_STRING TestGroupRDR::fname = "tmp.dat";


    TEST_GROUP_BASE(SYS_01, TestGroupRDR) {};

    //  test type: equivalence class test
    //  successfully load data
    TEST(SYS_01, T01)
    {
        SETUP()
        I_Reader& rdr = Reader::instance();

        STEP(1)
        expectClear();
        GenProjData<> data(fname);
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            m_Provider().expectAdd(data.at(n));
            m_Ctrl().expectOk();
        }
        m_Mapper().expectIndex();
        data.dump();
        rdr.read(fname);
        CHECK_N_CLEAR()

        STEP(2)
        const ComSetup& cs = rdr.getComSetup();
        L_CHECK_EQUAL(tcpPortFld,  cs.portFld)
        L_CHECK_EQUAL(tcpPortGui,  cs.portGui)
        L_CHECK_EQUAL(tcpPortCtrl, cs.portCtrl)
        L_CHECK_EQUAL(tcpTimeout,  cs.timeout)
    }

    //  test type: equivalence class test
    //  failure: file does not exist
    TEST(SYS_01, T02)
    {
        SETUP()
        I_Reader& rdr = Reader::instance();

        STEP(1)
        expectClear();
        expectFail();
        rdr.read("does_not_exist.dat");
        CHECK_N_CLEAR()
    }

    // //  test type: equivalence class test
    // //  failure: file size mismatch
    // TEST(SYS_01, T03)
    // {
    //     STEP(1)
    //     //  too small
    //     wrongSize(-1);
    //     CHECK_N_CLEAR()

    //     STEP(2)
    //     //  too large
    //     wrongSize(+1);
    //     CHECK_N_CLEAR()

    //     STEP(3)
    //     //  no data
    //     wrongSize(0, 0);
    //     CHECK_N_CLEAR()
    // }

    // //  test type: equivalence class test
    // //  failure: file smaller than header
    // TEST(SYS_01, T04)
    // {
    //     SETUP()
    //     I_Reader& rdr = Reader::instance();

    //     std::ofstream os(fname, std::ios::binary);
    //     for (size_t n = 0; n < 4 * sizeof(UINT32) - 1; ++n)
    //     {
    //         os << ' ';
    //     }
    //     os.close();

    //     STEP(1)
    //     expectFail();
    //     rdr.read(fname);
    //     CHECK_N_CLEAR()
    // }

    // //  test type: equivalence class test
    // //  log instance, log, maxerr
    // TEST(SYS_01, T05)
    // {
    //     STEP(1)
    //     I_Ctrl& logm = Ctrl::instance();
    //     logm.log(COMP_SYS, RET_ERR_MATCH);
    //     logm.log(COMP_SYS, RET_ERR_STARTUP);

    //     STEP(2)
    //     const I_Ctrl& logc = Ctrl::instance();
    //     const E_Ret ret = logc.maxerr();
    //     L_CHECK_EQUAL(RET_ERR_STARTUP, ret)
    // }
}
