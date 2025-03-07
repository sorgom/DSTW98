//  ============================================================
//  test of application IL
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/TestGroupBase.h>
#include <SYS/IL.h>

namespace test
{

    TEST_GROUP_BASE(IL_01, TestGroupBase) {};

    TEST(IL_01, T01)
    {
        STEP(1);
        L_CHECK_EQUAL(&Com::instance(), &IL::getCom());
        L_CHECK_EQUAL(&Ctrl::instance(), &IL::getCtrl());
        L_CHECK_EQUAL(&Mapper::instance(), &IL::getMapper());
        L_CHECK_EQUAL(&Provider::instance(), &IL::getProvider());
        L_CHECK_EQUAL(&Reader::instance(), &IL::getReader());
        L_CHECK_EQUAL(&TCP_Con_Ctrl::instance(), &IL::getTCP_Con_Ctrl());
        L_CHECK_EQUAL(&TCP_Con_Fld::instance(), &IL::getTCP_Con_Fld());
        L_CHECK_EQUAL(&TCP_Con_Gui::instance(), &IL::getTCP_Con_Gui());
        L_CHECK_EQUAL(&TCP_Listener_Ctrl::instance(), &IL::getTCP_Listener_Ctrl());
        L_CHECK_EQUAL(&TCP_Listener_Fld::instance(), &IL::getTCP_Listener_Fld());
        L_CHECK_EQUAL(&TCP_Listener_Gui::instance(), &IL::getTCP_Listener_Gui());
        L_CHECK_EQUAL(&TCP::instance(), &IL::getTCP());
    }
} // namespace
