//  ============================================================
//  test of Main
//  ============================================================
//  created by Manfred Sorgo
#include <testlib/TestGroupBase.h>
#include <SYS/Main.h>

namespace test
{
    TEST_GROUP_BASE(SYS_03, TestGroupBase)
    {

    };

    TEST(SYS_03, T01)
    {
        SETUP()
        const I_Main& main = Main::instance();
        CONST_C_STRING fname = "test.proj";
        CONST_C_STRING argv[2] = { "call", fname };
        INT32 ret = 0;

        STEP(1)
        // call with no file
        m_Ctrl().expectClear();
        m_Ctrl().expectMaxerr(RET_NO_ERR);
        ret = main.main(1, argv);
        CHECK_N_CLEAR()
        L_CHECK_EQUAL(RET_NO_ERR, ret)

        STEP(2)
        // NOK after Reader::read
        m_Ctrl().expectClear();
        m_Reader().expectRead(fname);
        m_Ctrl().expectOk(false);
        m_Com().expectStop();

        m_Ctrl().expectMaxerr(RET_ERR_STARTUP);
        ret = main.main(2, argv);
        CHECK_N_CLEAR()
        L_CHECK_EQUAL(RET_ERR_STARTUP, ret)

        STEP(3)
        // NOK after Com::start
        m_Ctrl().expectClear();
        m_Reader().expectRead(fname);
        m_Ctrl().expectOk(true);
        m_Com().expectStart();
        m_Ctrl().expectOk(false);

        m_Com().expectStop();
        m_Ctrl().expectMaxerr();
        main.main(2, argv);
        CHECK_N_CLEAR()

        STEP(4)
        // NOK after 1st Com::check
        m_Ctrl().expectClear();
        m_Reader().expectRead(fname);
        m_Ctrl().expectOk(true);
        m_Com().expectStart();
        m_Ctrl().expectOk(true);
        m_Com().expectCheck();
        m_Ctrl().expectOk(false);

        m_Com().expectStop();
        m_Ctrl().expectMaxerr();
        main.main(2, argv);
        CHECK_N_CLEAR()

        STEP(5)
        // NOK after 2nd Com::check
        m_Ctrl().expectClear();
        m_Reader().expectRead(fname);
        m_Ctrl().expectOk(true);
        m_Com().expectStart();
        m_Ctrl().expectOk(true);
        m_Com().expectCheck();
        m_Ctrl().expectOk(true);
        m_Com().expectCheck();
        m_Ctrl().expectOk(false);

        m_Com().expectStop();
        m_Ctrl().expectMaxerr();
        main.main(2, argv);
        CHECK_N_CLEAR()
    }

} // namespace
