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
    //  Reader: successfully load data
    TEST(SYS_01, T01)
    {
        SETUP()
        I_Reader& rdr = Reader::instance();
        GenProjData<> data(fname);
        data.dump();

        STEP(1)
        expectClear();
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            m_Provider().expectAdd(data.at(n));
            m_Ctrl().expectOk();
        }
        m_Mapper().expectIndex();
        rdr.read(fname);
        CHECK_N_CLEAR()

        STEP(2)
        const ComSetup& cs = rdr.getComSetup();
        L_CHECK_EQUAL(tcpPortFld,  cs.portFld)
        L_CHECK_EQUAL(tcpPortGui,  cs.portGui)
        L_CHECK_EQUAL(tcpPortCtrl, cs.portCtrl)
        L_CHECK_EQUAL(tcpTimeout,  cs.timeout)

        STEP(3)
        //  Ctrl reports error
        expectClear();
        m_Provider().expectAdd(data.at(0));
        m_Ctrl().expectOk(false);
        expectFail();
        rdr.read(fname);
        CHECK_N_CLEAR()
    }

    //  test type: equivalence class test
    //  Reader: file does not exist
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

    //  test type: equivalence class test
    //  Reader: data size errors
    TEST(SYS_01, T03)
    {
        SETUP()
        I_Reader& rdr = Reader::instance();
        GenProjData<> data(fname);

        STEP(1)
        // file smaller than header
        data.dumpTooSmall();
        expectClear();
        expectFail();
        rdr.read(fname);
        CHECK_N_CLEAR()

        STEP(2)
        // too many items announced
        data.dump(CAPACITY + 1);
        expectClear();
        expectFail();
        rdr.read(fname);
        CHECK_N_CLEAR()

        STEP(3)
        // less items than announced
        data.dump(CAPACITY, CAPACITY - 1);
        expectClear();
        expectFail();
        rdr.read(fname);
        CHECK_N_CLEAR()
    }

    //  test type: equivalence class test
    //  Ctrl instance, log, maxerr
    TEST(SYS_01, T05)
    {
        SETUP()
        I_Ctrl& ctrl = Ctrl::instance();
        const I_Ctrl& ctrlc = Ctrl::instance();

        STEP(1)
        ctrl.clear();
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ctrlc.ok())

        STEP(2)
        ctrl.log(COMP_SYS, RET_ERR_STARTUP);
        ctrl.log(COMP_SYS, RET_ERR_MATCH);
        CHECK_N_CLEAR()
        L_CHECK_FALSE(ctrlc.ok())
        L_CHECK_EQUAL(RET_ERR_STARTUP, ctrlc.maxerr())

        STEP(1)
        ctrl.clear();
        L_CHECK_TRUE(ctrlc.ok())
        ctrl.stop();
        CHECK_N_CLEAR()
        L_CHECK_FALSE(ctrlc.ok())
    }
}
