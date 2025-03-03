#include <COM/TCP_Com.h>
#include <SYS/IL.h>
#include <BAS/coverage.h>

#include <cstdio>

void TCP_Com_Base::comerr(const CONST_C_STRING msg)
{
    IL::getCtrl().log(COMP_COM, RET_ERR_COM);
    if (msg != nullptr)
    {
        printf("%s\n", msg);
    }
}

//  ============================================================
//  TCP listeners
//  ============================================================
bool Tcp_Listener_Base::listen(const UINT16 port)
{
    printf("listen: %u\n", port);
    const I_TCP& tcp = IL::getTCP();
    bool ok = true;
    mSocket = tcp.socket();
    if (mSocket < 0)
    {
        ok = false;
        comerr("socket");
    }
    else if (not tcp.bind(mSocket, port))
    {
        ok = false;
        comerr("bind");
    }
    else if (not tcp.listen(mSocket))
    {
        ok = false;
        comerr("listen");
    }

    if (not ok)
    {
        tcp.close(mSocket);
    }
    return ok;
}

bool Tcp_Listener_Base::select()
{
    const I_TCP& tcp = IL::getTCP();
    const INT32 res = tcp.select(mSocket);
    bool ok =
        (res == 0)
        or (res > 0 and getCon().accept(mSocket));

    if (not ok)
    {
        comerr("select");
        tcp.close(mSocket);
    }
    return ok;
}

void Tcp_Listener_Base::close()
{
    IL::getTCP().close(mSocket);
}

I_TCP_Con& TCP_Listener_Fld::getCon() const
{
    return IL::getTCP_Con_Fld();
}
INSTANCE_DEF(TCP_Listener_Fld)

I_TCP_Con& TCP_Listener_Gui::getCon() const
{
    return IL::getTCP_Con_Gui();
}
INSTANCE_DEF(TCP_Listener_Gui)

I_TCP_Con& TCP_Listener_Ctrl::getCon() const
{
    return IL::getTCP_Con_Ctrl();
}
INSTANCE_DEF(TCP_Listener_Ctrl)

//  ============================================================
//  TCP connections
//  ============================================================
bool TCP_Con_Base::accept(const INT32 socket)
{
    close();
    mSocket = IL::getTCP().accept(socket);
    const bool ok = mSocket >= 0;
    if (ok)
    {
        onAccept();
    }
    else
    {
        comerr("accept");
    }
    return ok;
}

bool TCP_Con_Base::select()
{
    const I_TCP& tcp = IL::getTCP();
    bool ok = true;
    // not operating
    if (mSocket >= 0)
    {
        const INT32 res = tcp.select(mSocket);
        //  activity on socket
        if (res > 0)
        {
            const INT32 len = tcp.recv(mSocket, &mTele, sizeof(ComTele));
            //  valid telegram received
            if (len == sizeof(ComTele))
            {
                forward(mTele);
            }
            //  close event
            else if (len <= 0)
            {
                close();
            }
            //  invalid data size
            else
            {
                ok = false;
                close();
            }
        }
        //  select error
        else if (res < 0)
        {
            ok = false;
            close();
        }
    }
    if (not ok)
    {
        comerr("select");
    }
    return ok;
}

void TCP_Con_Base::close()
{
    IL::getTCP().close(mSocket);
}

void TCP_Con_Base::send(const ComTele& tele) const
{
    if (mSocket >= 0)
    {
        IL::getTCP().send(mSocket, reinterpret_cast<const CHAR*>(&tele), sizeof(ComTele));
    }
}

//  field connection
INSTANCE_DEF(TCP_Con_Fld)

void TCP_Con_Fld::onAccept() const
{
    //  TODO: Dispatcher must recall all states
}

void TCP_Con_Fld::forward(const ComTele& tele) const
{
    IL::getMapper().fromFld(tele);
}

//  GUI connection
INSTANCE_DEF(TCP_Con_Gui)

void TCP_Con_Gui::onAccept() const
{
    //  TODO: Dispatcher resend all states
    //  call I_Elem::resend() or similar
}

void TCP_Con_Gui::forward(const ComTele& tele) const
{
    IL::getMapper().fromGui(tele);
}

//  control connection
INSTANCE_DEF(TCP_Con_Ctrl)

void TCP_Con_Ctrl::forward(const ComTele& tele) const
{
    //  evaluate telegram
    if (tele.data.param1 == tele.data.param2)
    {
        switch (tele.data.param1)
        {
        case COM_CTRL_STOP:
            IL::getCtrl().stop();
            break;
        case COM_CTRL_PING:
            send(tele);
            break;
        case COM_CTRL_RE_GUI:
            IL::getMapper().reGui();
            break;
        default:
            break;
        }
    }
}
