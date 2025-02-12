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
        }

        //  check all clients for received telegrams
        void recvAll()
        {
            SUBSTEPS()
            #ifdef _WIN32
            wait(100);
            #endif
            STEP(1)
            clientFld.recv();
            STEP(2)
            clientGui.recv();
            STEP(3)
            clientCtrl.recv();
            ENDSTEPS()
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

    //  receive states from field
    TEST(SYST_01, T02)
    {
        SETUP()
        GenProjData<> gp;
        STEP(1)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            LSTEP(n)
            //  GUI cmd
            ComData dataCmd;
            //  state request forwarded to field
            ComData dataFld;
            //  state returned to GUI
            ComData dataRet;

            bool ok = true;
            bool same = true;
            switch (gp.type(n))
            {
                case TYPE_TSW:
                    dataCmd = ComData(TSW_CMD_LEFT);
                    dataFld = ComData(TSW_STATE_LEFT);
                    dataRet = ComData(TSW_STATE_WAIT_LEFT);
                    same = false;
                    break;
                case TYPE_LCR:
                    dataCmd = ComData(LCR_STATE_OPEN);
                    dataRet = ComData(LCR_STATE_WAIT_OPEN);
                    break;
                case TYPE_LCR_UBK:
                    dataCmd = ComData(LCR_STATE_OPEN);
                    dataRet = ComData(LCR_STATE_WAIT_OPEN, LCR_UBK_STATE_UNDEF);
                    break;
                case TYPE_SIG_H:
                    dataCmd = ComData(SIG_STATE_H0);
                    dataRet = ComData(SIG_STATE_WAIT_H0);
                    break;
                case TYPE_SIG_H_N:
                    dataCmd = ComData(SIG_STATE_H0_N0);
                    dataRet = ComData(SIG_STATE_WAIT_H0_N0, 0);
                    break;
                case TYPE_SIG_N:
                    dataCmd = ComData(SIG_STATE_N0);
                    dataRet = ComData(SIG_STATE_WAIT_N0, 0);
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                const ComTele teleCmd = { gp.addr(n), dataCmd };
                const ComTele teleFld = { gp.addr(n), same ? dataCmd : dataFld };
                const ComTele teleRet = { gp.addr(n), dataRet };
                clientFld.expectRecv(teleFld);
                clientGui.expectRecv(teleRet);
                clientGui.send(teleCmd);
                wait(50);
                recvAll();
                recvAll();
                CHECK_N_CLEAR()
            }
        }
        ENDSTEPS()

        STEP(2)
        SUBSTEPS()
        for (size_t n = 0; n < CAPACITY; ++n)
        {
            STEP(n)
            ComData data;
            bool ok = true;
            switch (gp.type(n))
            {
                case TYPE_TSW:
                    data = ComData(TSW_STATE_LEFT);
                    break;
                case TYPE_LCR:
                    data = ComData(LCR_STATE_OPEN);
                    break;
                case TYPE_LCR_UBK:
                    data = ComData(LCR_STATE_OPEN, LCR_UBK_STATE_FREE);
                    break;
                case TYPE_SIG_H:
                    data = ComData(SIG_STATE_H0);
                    break;
                case TYPE_SIG_H_N:
                    data = ComData(SIG_STATE_H0_N0);
                    break;
                case TYPE_SIG_N:
                    data = ComData(SIG_STATE_N0);
                    break;
                default:
                    ok = false;
                    break;
            }
            if (ok)
            {
                const ComTele teleState = { gp.addr(n), data };
                clientGui.expectRecv(teleState);
                clientFld.send(teleState);
                wait(10);
                recvAll();
                CHECK_N_CLEAR()
            }
        }
        ENDSTEPS()
    }

    //  call for reGui
    TEST(SYST_01, T03)
    {
        STEP(1)
        const ComTele ts = { genComAddr(22, "REGUI"), ComData(COM_CTRL_RE_GUI, COM_CTRL_RE_GUI) };
        clientGui.expectRecv(CAPACITY);
        clientCtrl.send(ts);
        wait(50);
        recvAll();
        CHECK_N_CLEAR()
    }
}
