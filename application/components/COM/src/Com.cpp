#include <COM/Com.h>
#include <SYS/IL.h>

INSTANCE_DEF(Com)

void Com::start()
{
    I_TCP& tcp = IL::getTCP();
    const ComSetup& setup = IL::getReader().getComSetup();

    if (
        tcp.init()
        and IL::getTCP_Listener_Fld().listen(setup.portFld)
        and IL::getTCP_Listener_Gui().listen(setup.portGui)
        and IL::getTCP_Listener_Ctrl().listen(setup.portCtrl)
    )
    {
        tcp.setTimeout(setup.timeout);
    }
    else
    {
        IL::getCtrl().log(COMP_COM, RET_ERR_STARTUP);
    }
}

void Com::check()
{
    if (not(
        IL::getTCP_Listener_Fld().select()
        and IL::getTCP_Listener_Gui().select()
        and IL::getTCP_Listener_Ctrl().select()
        and IL::getTCP_Con_Fld().select()
        and IL::getTCP_Con_Gui().select()
        and IL::getTCP_Con_Ctrl().select()
    ))
    {
        IL::getCtrl().log(COMP_COM, RET_ERR_COM);
    }
}
void Com::stop()
{
    IL::getTCP_Listener_Fld().close();
    IL::getTCP_Listener_Gui().close();
    IL::getTCP_Listener_Ctrl().close();
    IL::getTCP_Con_Fld().close();
    IL::getTCP_Con_Gui().close();
    IL::getTCP_Con_Ctrl().close();
    IL::getTCP().cleanup();
}

void Com::toFld(const ComTele& tele) const
{
    IL::getTCP_Con_Fld().send(tele);
}

void Com::toGui(const ComTele& tele) const
{
    IL::getTCP_Con_Gui().send(tele);
}
