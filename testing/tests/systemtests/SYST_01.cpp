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
            ComData cdCmd;
            //  state request forwarded to field
            ComData cdFld;
            //  state returned to GUI
            ComData cdRet;

            bool ok = true;
            bool same = true;
            switch (data.type(n))
            {
                case TYPE_TSW:
                    cdCmd = ComData(TSW_CMD_LEFT);
                    cdFld = ComData(TSW_STATE_LEFT);
                    cdRet = ComData(TSW_STATE_WAIT_LEFT);
                    same = false;
                    break;
                case TYPE_LCR:
                    cdCmd = ComData(LCR_STATE_OPEN);
                    cdRet = ComData(LCR_STATE_WAIT_OPEN);
                    break;
                case TYPE_LCR_UBK:
                    cdCmd = ComData(LCR_STATE_OPEN);
                    cdRet = ComData(LCR_STATE_WAIT_OPEN, LCR_UBK_STATE_UNDEF);
                    break;
                case TYPE_SIG_H:
                    cdCmd = ComData(SIG_STATE_H0);
                    cdRet = ComData(SIG_STATE_WAIT_H0);
                    break;
                case TYPE_SIG_H_N:
                    cdCmd = ComData(SIG_STATE_H0_N0);
                    cdRet = ComData(SIG_STATE_WAIT_H0_N0, 0);
                    break;
                case TYPE_SIG_N:
                    cdCmd = ComData(SIG_STATE_N0);
                    cdRet = ComData(SIG_STATE_WAIT_N0, 0);
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                const ComTele teleCmd = { data.addr(n), cdCmd };
                const ComTele teleFld = { data.addr(n), same ? cdCmd : cdFld };
                const ComTele teleRet = { data.addr(n), cdRet };
                clientFld.expectRecv(teleFld);
                clientGui.expectRecv(teleRet);
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
            ComData cdFld;
            bool ok = true;
            switch (data.type(n))
            {
                case TYPE_TSW:
                    cdFld = ComData(TSW_STATE_LEFT);
                    break;
                case TYPE_LCR:
                    cdFld = ComData(LCR_STATE_OPEN);
                    break;
                case TYPE_LCR_UBK:
                    cdFld = ComData(LCR_STATE_OPEN, LCR_UBK_STATE_FREE);
                    break;
                case TYPE_SIG_H:
                    cdFld = ComData(SIG_STATE_H0);
                    break;
                case TYPE_SIG_H_N:
                    cdFld = ComData(SIG_STATE_H0_N0);
                    break;
                case TYPE_SIG_N:
                    cdFld = ComData(SIG_STATE_N0);
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                const ComTele teleState = { data.addr(n), cdFld };
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
