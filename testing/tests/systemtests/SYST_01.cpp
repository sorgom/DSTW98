//  ============================================================
//  system tests vol. 1
//  requiring a running application (in background)
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <testlib/wait.h>
#include <mocks/M_TCP_Client.h>
#include <COM/TCP.h>

namespace test
{
    class TestGroupSys : public TestGroupBase
    {
    protected:
        TestGroupSys() :
            clientFld("FLD"),
            clientGui("GUI"),
            clientCtrl("CTRL")
        {}
        M_TCP_Client clientFld;
        M_TCP_Client clientGui;
        M_TCP_Client clientCtrl;

        void setup()
        {
            SUBSTEPS()
            STEP(1)
            const bool ok = TCP_Client::init();
            L_CHECK_TRUE(ok)
            STEP(2)
            clientFld.connect(tcpPortFld);
            clientGui.connect(tcpPortGui);
            clientCtrl.connect(tcpPortCtrl);
            ENDSTEPS()
        }

        //  check all clients for received telegrams
        void recvAll()
        {
            #ifdef _WIN32
            wait(50);
            #endif
            clientFld.recv();
            clientGui.recv();
            clientCtrl.recv();
        }

        void teardown()
        {
            clientFld.close();
            clientGui.close();
            clientCtrl.close();
            TCP_Client::cleanup();
        }

    };

    TEST_GROUP_BASE(SYST_01, TestGroupSys) {};

    //  ping pong test
    TEST(SYST_01, T01)
    {
        //  send ping telegram
        STEP(1)
        const ComTele ts = { genComAddr(22, "PING"), ComData(COM_CTRL_PING, COM_CTRL_PING) };
        clientCtrl.expectRecv(ts);
        clientCtrl.send(ts);
        recvAll();
        CHECK_N_CLEAR()
    }

    //  track switches 1, 11, 21, ...
    //  initial state: UNDEF
    //  STEP(1)
    //  send GUI command WU
    //  - no telegrams to field or GUI
    //  STEP(2)
    //  send switch state telegrams from field
    //  - receive identical switch state telegrams to GUI
    //  UNDEF to LEFT
    //  STEP(3)
    //  send GUI command WU
    //  - field should receive RIGHT
    //  - GUI should receive WAIT_RIGHT
    // TEST(SYST_01, T02)
    // {
    //     STEP(1)
    //     SUBSTEPS()
    //     for (UINT16 n = 1; n < TEST_NUM_TSW; n += 10)
    //     {
    //         STEP(n)
    //         const ComAddr cname {genComAddr(n, "TSW")};
    //         const ComTele txg{cname, { TSW_CMD_WU, PARAM_UNDEF }};
    //         clientGui.send(txg);
    //         recvAll();
    //         CHECK_N_CLEAR()
    //     }
    //     ENDSTEPS()

    //     STEP(2)
    //     SUBSTEPS()
    //     for (UINT16 n = 1; n < TEST_NUM_TSW; n += 10)
    //     {
    //         STEP(n)
    //         const ComAddr cname {genComAddr(n, "TSW")};
    //         const ComTele txf{cname, { TSW_STATE_LEFT, PARAM_UNDEF }};
    //         clientGui.expectRecv(txf);
    //         clientFld.send(txf);
    //         recvAll();
    //         CHECK_N_CLEAR()
    //     }
    //     ENDSTEPS()

    //     STEP(3)
    //     SUBSTEPS()
    //     for (UINT16 n = 1; n < TEST_NUM_TSW; n += 10)
    //     {
    //         STEP(n)
    //         const ComAddr cname {genComAddr(n, "TSW")};
    //         const ComTele txgs{cname, { TSW_CMD_WU, PARAM_UNDEF }};
    //         const ComTele txfr{cname, { TSW_STATE_RIGHT, PARAM_UNDEF }};
    //         const ComTele txgr{cname, { TSW_STATE_WAIT_RIGHT, PARAM_UNDEF }};
    //         clientFld.expectRecv(txfr);
    //         clientGui.expectRecv(txgr);
    //         clientGui.send(txgs);
    //         recvAll();
    //         CHECK_N_CLEAR()
    //     }
    //     ENDSTEPS()
    // }

    // //  call for reGui
    // TEST(SYST_01, T03)
    // {
    //     STEP(1)
    //     clientGui.expectRecv(CAPACITY);
    //     clientCtrl.send(ComTele{{}, { COM_CTRL_RE_GUI, COM_CTRL_RE_GUI }});
    //     recvAll();
    //     CHECK_N_CLEAR()
    // }
}
