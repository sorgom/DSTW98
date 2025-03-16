#include <COM/TCP_Com.h>
#include <SYS/IL.h>
#include <BAS/coverage.h>

#include <cstdio>

void TCP_Com_Base::comerr(const E_Err err)
{
    if (err != NO_ERR) IL::getCtrl().log(COMP_COM, err);
}

//  ============================================================
//  TCP listeners
//  ============================================================
bool Tcp_Listener_Base::listen(const UINT16 port)
{
    const I_TCP& tcp = IL::getTCP();
    bool ok = true;
    mSocket = tcp.socket();
    if (mSocket < 0)
    {
        ok = false;
        comerr(ERR_COM_SOCKET);
    }
    else if (not tcp.bind(mSocket, port))
    {
        ok = false;
        comerr(ERR_COM_BIND);
    }
    else if (not tcp.listen(mSocket))
    {
        ok = false;
        comerr(ERR_COM_LISTEN);
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
    E_Err err = NO_ERR;
    const E_Select res = tcp.select(mSocket);
    if (res == SELECT_ERR)
    {
        err = ERR_COM_SELECT;
    }
    else if (res == SELECT_READY)
    {
        if (not getCon().accept(mSocket))
        {
            err = ERR_COM_ACCEPT;
        }
    }

    bool ok = (err == NO_ERR);
    if (not ok)
    {
        comerr(err);
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
CHAR TCP_Con_Base::mBuffer[RecBuffSize];

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
        comerr(ERR_COM_ACCEPT);
    }
    return ok;
}

bool TCP_Con_Base::select()
{
    const I_TCP& tcp = IL::getTCP();
    E_Err err = NO_ERR;
    // not operating
    if (mSocket >= 0)
    {
        const E_Select res = tcp.select(mSocket);
        //  activity on socket
        if (res == SELECT_READY)
        {
            const INT32 len = tcp.recv(mSocket, mBuffer, RecBuffSize);
            //  close event
            if (len <= 0)
            {
                close();
            }
            //  odd data size
            else if ((len % sizeof(ComTele)) != 0)
            {
                err = ERR_COM_RECV;
                close();
            }
            //  valid telegram(s) received
            else
            {
                const size_t num = len / sizeof(ComTele);
                for (size_t n = 0; n < num; ++n)
                {
                    forward(reinterpret_cast<const ComTele*>(mBuffer)[n]);
                }
            }
        }
        //  select error
        else if (res == SELECT_ERR)
        {
            err = ERR_COM_SELECT;
            close();
        }
    }
    comerr(err);
    return err == NO_ERR;
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
    //  TODO: Mapper must recall all states
}

void TCP_Con_Fld::forward(const ComTele& tele) const
{
    IL::getMapper().fromFld(tele);
}

//  GUI connection
INSTANCE_DEF(TCP_Con_Gui)

void TCP_Con_Gui::onAccept() const
{
    //  TODO: Mapper resend all states
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
