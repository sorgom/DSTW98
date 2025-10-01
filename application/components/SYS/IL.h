//  ============================================================
//  Interface Locator IL
//  - production application version
//  ============================================================
//  created by Manfred Sorgo

#ifndef IL_H
#define IL_H

#include <COM/Com.h>
#include <COM/TCP_Com.h>
#include <COM/TCP.h>
#include <SYS/Ctrl.h>
#include <SYS/Mapper.h>
#include <SYS/Provider.h>
#include <SYS/Reader.h>

namespace IL
{
    inline I_Com& getCom() { return Com::instance(); }
    inline I_Ctrl& getCtrl() { return Ctrl::instance(); }
    inline I_Mapper& getMapper() { return Mapper::instance(); }
    inline I_Provider& getProvider() { return Provider::instance(); }
    inline I_Reader& getReader() { return Reader::instance(); }
    inline I_TCP_Con& getTCP_Con_Ctrl() { return TCP_Con_Ctrl::instance(); }
    inline I_TCP_Con& getTCP_Con_Fld() { return TCP_Con_Fld::instance(); }
    inline I_TCP_Con& getTCP_Con_Gui() { return TCP_Con_Gui::instance(); }
    inline I_TCP_Listener& getTCP_Listener_Ctrl() { return TCP_Listener_Ctrl::instance(); }
    inline I_TCP_Listener& getTCP_Listener_Fld() { return TCP_Listener_Fld::instance(); }
    inline I_TCP_Listener& getTCP_Listener_Gui() { return TCP_Listener_Gui::instance(); }
    inline I_TCP& getTCP() { return TCP::instance(); }
} // namespace
#endif // _H
