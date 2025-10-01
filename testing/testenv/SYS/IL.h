//  ============================================================
//  Interface Locator IL
//  - test version: all mocked
//  ============================================================
//  created by Manfred Sorgo

#ifndef IL_H
#define IL_H

#include <mocks/M_Instances.h>

namespace IL
{
    inline I_Com& getCom() { return test::m_Com(); }
    inline I_Ctrl& getCtrl() { return test::m_Ctrl(); }
    inline I_Mapper& getMapper() { return test::m_Mapper(); }
    inline I_Provider& getProvider() { return test::m_Provider(); }
    inline I_Reader& getReader() { return test::m_Reader(); }
    inline I_TCP_Con& getTCP_Con_Ctrl() { return test::m_TCP_Con_Ctrl(); }
    inline I_TCP_Con& getTCP_Con_Fld() { return test::m_TCP_Con_Fld(); }
    inline I_TCP_Con& getTCP_Con_Gui() { return test::m_TCP_Con_Gui(); }
    inline I_TCP_Listener& getTCP_Listener_Ctrl() { return test::m_TCP_Listener_Ctrl(); }
    inline I_TCP_Listener& getTCP_Listener_Fld() { return test::m_TCP_Listener_Fld(); }
    inline I_TCP_Listener& getTCP_Listener_Gui() { return test::m_TCP_Listener_Gui(); }
    inline I_TCP& getTCP() { return test::m_TCP(); }

} // namespace
#endif // _H
