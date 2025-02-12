//  ============================================================
//  mock instances for IL and tests
//  for interface I_<NAME>
//  - function m_<NAME>() returns mock instance
//  ============================================================
//  created by Manfred Sorgo

#ifndef M_INSTANCES_H
#define M_INSTANCES_H

#include "M_Com.h"
#include "M_Ctrl.h"
#include "M_Elem.h"
#include "M_Elems.h"
#include "M_Mapper.h"
#include "M_Provider.h"
#include "M_Reader.h"
#include "M_TCP_Con.h"
#include "M_TCP_Listener.h"
#include "M_TCP.h"

namespace test
{
    inline M_Com& m_Com() { return M_Com::instance(); }
    inline M_Ctrl& m_Ctrl() { return M_Ctrl::instance(); }
    inline M_Elems& m_Elems() { return M_Elems::instance(); }
    inline M_Mapper& m_Mapper() { return M_Mapper::instance(); }
    inline M_Provider& m_Provider() { return M_Provider::instance(); }
    inline M_Reader& m_Reader() { return M_Reader::instance(); }
    inline M_TCP_Con_Ctrl& m_TCP_Con_Ctrl() { return M_TCP_Con_Ctrl::instance(); }
    inline M_TCP_Con_Fld& m_TCP_Con_Fld() { return M_TCP_Con_Fld::instance(); }
    inline M_TCP_Con_Gui& m_TCP_Con_Gui() { return M_TCP_Con_Gui::instance(); }
    inline M_TCP_Listener_Ctrl& m_TCP_Listener_Ctrl() { return M_TCP_Listener_Ctrl::instance(); }
    inline M_TCP_Listener_Fld& m_TCP_Listener_Fld() { return M_TCP_Listener_Fld::instance(); }
    inline M_TCP_Listener_Gui& m_TCP_Listener_Gui() { return M_TCP_Listener_Gui::instance(); }
    inline M_TCP& m_TCP() { return M_TCP::instance(); }

} // namespace
#endif // _H
