//  ============================================================
//  system tests vol. 1
//  requiring a running application (in background)
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <testlib/GenProjData.h>
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
            TS_SHOW(2)
        }

        inline static void think()
        {
            #ifdef _WIN32
            wait(100);
            #endif
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

    TEST(SYST_01, T01)
    {
        SETUP()
        MinProjData data;

        CSTEP(1, "send ping telegram")
        {
            const ComTele ts = { genComAddr(22, "PING"), ComData(COM_CTRL_PING, COM_CTRL_PING) };
            clientCtrl.expectRecv(ts);
            clientCtrl.send(ts);
            think();
            clientCtrl.recv();
            CHECK_N_CLEAR()
        }

        CSTEP(2, "process GUI commands")
        SUBSTEPS()
        for (size_t n = 0; n < data.size(); ++n)
        {
            LSTEP(n)
            //  GUI cmd
            UINT8 pCmd = PARAM_UNDEF;
            //  state request forwarded to field
            UINT8 pFld = PARAM_UNDEF;
            //  state returned to GUI
            UINT8 pGui1 = PARAM_UNDEF;
            UINT8 pGui2 = PARAM_UNDEF;

            bool ok = true;
            bool same = true;
            switch (data.type(n))
            {
                case TYPE_TSW:
                    pCmd = TSW_CMD_LEFT;
                    pFld = TSW_STATE_LEFT;
                    pGui1 = TSW_STATE_WAIT_LEFT;
                    same = false;
                    break;
                case TYPE_LCR:
                    pCmd = LCR_STATE_OPEN;
                    pGui1 = LCR_STATE_WAIT_OPEN;
                    break;
                case TYPE_LCR_UBK:
                    pCmd = LCR_STATE_OPEN;
                    pGui1 = LCR_STATE_WAIT_OPEN;
                    pGui2 = LCR_UBK_STATE_UNDEF;
                    break;
                case TYPE_SIG_H:
                    pCmd = SIG_STATE_H0;
                    pGui1 = SIG_STATE_WAIT_H0;
                    break;
                case TYPE_SIG_H_N:
                    pCmd = SIG_STATE_H0_N0;
                    pGui1 = SIG_STATE_WAIT_H0_N0;
                    pGui2 = 0;
                    break;
                case TYPE_SIG_N:
                    pCmd = SIG_STATE_N0;
                    pGui1 = SIG_STATE_WAIT_N0;
                    pGui2 = 0;
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                if (same) pFld = pCmd;
                const ComTele teleCmd = { data.addr(n), ComData(pCmd) };
                const ComTele teleFld = { data.addr(n), ComData(pFld) };
                const ComTele teleGui = { data.addr(n), ComData(pGui1, pGui2) };
                clientFld.expectRecv(teleFld);
                clientGui.expectRecv(teleGui);
                clientGui.send(teleCmd);
                think();
                clientFld.recv();
                clientGui.recv();
                CHECK_N_CLEAR()
            }
        }
        ENDSTEPS()

        CSTEP(3, "process field telegrams")
        SUBSTEPS()
        for (size_t n = 0; n < data.size(); ++n)
        {
            LSTEP(n)
            bool ok = true;
            UINT8 p1 = PARAM_UNDEF;
            UINT8 p2 = PARAM_UNDEF;
            switch (data.type(n))
            {
                case TYPE_TSW:
                    p1 = TSW_STATE_LEFT;
                    break;
                case TYPE_LCR:
                    p1 = LCR_STATE_OPEN;
                    break;
                case TYPE_LCR_UBK:
                    p1 = LCR_STATE_OPEN;
                    p2 = LCR_UBK_STATE_FREE;
                    break;
                case TYPE_SIG_H:
                    p1 = SIG_STATE_H0;
                    break;
                case TYPE_SIG_H_N:
                    p1 = SIG_STATE_H0_N0;
                    break;
                case TYPE_SIG_N:
                    p1 = SIG_STATE_N0;
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                const ComTele teleState = { data.addr(n), ComData(p1, p2) };
                clientGui.expectRecv(teleState);
                clientFld.send(teleState);
                think();
                clientGui.recv();
                CHECK_N_CLEAR()
            }
        }
        ENDSTEPS()

        CSTEP(4, "process reGui command via Ctrl")
        {
            const ComTele ts = { genComAddr(22, "REGUI"), ComData(COM_CTRL_RE_GUI, COM_CTRL_RE_GUI) };
            clientGui.expectRecv(MinProjData::size());
            clientCtrl.send(ts);
            wait(500);
            think();
            clientGui.recv();
            CHECK_N_CLEAR()
        }
    }
}
