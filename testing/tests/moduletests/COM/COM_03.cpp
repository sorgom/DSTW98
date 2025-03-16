//  ============================================================
//  test of COM TCP connections
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <COM/TCP_Com.h>

#include <cstring>

namespace test
{

    TEST_GROUP_BASE(COM_03, TestGroupBase)
    {
        static const INT32 validSocket = 0;
        static const INT32 invalidSocket = -1;
        static const size_t RcvBuffSize = I_TCP_Con::NumTelRcv * sizeof(ComTele);
        ComTele tele;
        bool ok;

        inline static void expectComerr(const E_Err err=ERR_COM)
        {
            m_Ctrl().expectLog(COMP_COM, err);
        }

        void setTele(const UINT8 p1, const UINT8 p2 = PARAM_UNDEF)
        {
            //  would be easier with placement new
            //  new (&tele.data) ComData(p1, p2);
            //  but vscode does not like it
            //  therefore:
            const ComData cd(p1, p2);
            std::memcpy((void*) &tele.data, &cd, sizeof(ComData));
        }
    };

    //  test type: equivalence class test
    //  TCP client field representing base client
    TEST(COM_03, T01)
    {
        SETUP()
        I_TCP_Con& client = TCP_Con_Fld::instance();

        //  accept returns invalid socket
        STEP(1)
        expectComerr(ERR_COM_ACCEPT);
        m_TCP().expectClose();
        m_TCP().expectAccept(validSocket, invalidSocket);
        ok = client.accept(validSocket);
        CHECK_N_CLEAR()
        L_CHECK_FALSE(ok)

        //  select should return true without action
        STEP(2)
        ok = client.select();
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)

        //  send telegram to invalid socket
        //  should not send
        STEP(3)
        {
            setTele(101, 202);
            client.send(tele);
            CHECK_N_CLEAR()
        }

        //  accept returns valid socket
        STEP(4)
        m_TCP().expectClose();
        m_TCP().expectAccept(validSocket, validSocket);
        ok = client.accept(validSocket);
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)

        //  select returns 0 no activity
        STEP(5)
        m_TCP().expectSelect(validSocket, SELECT_NONE);
        ok = client.select();
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)

        //  select returns 1 activity
        //  recv returns valid data
        //  Mapper gets data from field
        STEP(6)
        {
            setTele(101, 202);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            m_Mapper().expectFromFld(tele);
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  select returns -1 error
        STEP(7)
        expectComerr(ERR_COM_SELECT);
        m_TCP().expectSelect(validSocket, SELECT_ERR);
        m_TCP().expectClose();
        ok = client.select();
        CHECK_N_CLEAR()
        L_CHECK_FALSE(ok)
    }

    //  test type: equivalence class test
    //  TCP client GUI representing base client
    TEST(COM_03, T02)
    {
        SETUP()
        I_TCP_Con& client = TCP_Con_Gui::instance();

        //  accept returns valid socket
        STEP(1)
        m_TCP().expectClose();
        m_TCP().expectAccept(validSocket, validSocket);
        ok = client.accept(validSocket);
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)

        //  select returns 1 activity
        //  recv returns valid data
        //  Dispatcher gets data from GUI
        STEP(2)
        {
            setTele(121, 212);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            m_Mapper().expectFromGui(tele);
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  send telegram to valid socket
        STEP(3)
        {
            setTele(131, 232);
            m_TCP().expectSend(validSocket, sizeof(ComTele));
            client.send(tele);
            CHECK_N_CLEAR()
        }

        //  select returns 1 activity
        //  recv returns close event
        STEP(4)
        m_TCP().expectSelect(validSocket, SELECT_READY);
        m_TCP().expectRecv(validSocket, RcvBuffSize, 0);
        m_TCP().expectClose();
        ok = client.select();
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)
    }
    //  test type: equivalence class test
    //  TCP client CTRL representing base client
    TEST(COM_03, T03)
    {
        SETUP()
        I_TCP_Con& client = TCP_Con_Ctrl::instance();

        //  accept returns valid socket
        STEP(1)
        m_TCP().expectClose();
        m_TCP().expectAccept(validSocket, validSocket);
        ok = client.accept(validSocket);
        CHECK_N_CLEAR()
        L_CHECK_TRUE(ok)

        //  select returns 1 activity
        //  recv returns valid data
        //  data contains different values
        STEP(2)
        {
            setTele(COM_CTRL_STOP - 1, COM_CTRL_STOP);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  data contains both COM_CTRL_STOP
        //  Com::stop called
        STEP(3)
        {
            setTele(COM_CTRL_STOP, COM_CTRL_STOP);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            m_Ctrl().expectStop();
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  data contains both COM_CTRL_PING
        //  send echo
        STEP(4)
        {
            setTele(COM_CTRL_PING, COM_CTRL_PING);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            m_TCP().expectSend(validSocket, sizeof(ComTele));
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  data contains both COM_CTRL_RE_GUI
        //  Dispatcher::reGui called
        STEP(5)
        {
            setTele(COM_CTRL_RE_GUI, COM_CTRL_RE_GUI);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            m_Mapper().expectReGui();
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  data contains both unknown values
        //  no reaction
        STEP(5)
        {
            setTele(PARAM_UNKNOWN, PARAM_UNKNOWN);
            m_TCP().expectSelect(validSocket, SELECT_READY);
            m_TCP().expectRecv(validSocket, tele);
            ok = client.select();
            CHECK_N_CLEAR()
            L_CHECK_TRUE(ok)
        }

        //  recv returns invalid size
        STEP(7)
        expectComerr(ERR_COM_RECV);
        m_TCP().expectSelect(validSocket, SELECT_READY);
        m_TCP().expectRecv(validSocket, RcvBuffSize, RcvBuffSize - 1);
        m_TCP().expectClose();
        ok = client.select();
        CHECK_N_CLEAR()
        L_CHECK_FALSE(ok)
    }
} // namespace
