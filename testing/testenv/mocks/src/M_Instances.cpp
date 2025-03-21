
#include <mocks/M_Instances.h>

// #include <mocks/M_Elem.h>
// #include <mocks/M_Ctrl.h>
// #include <mocks/M_Provider.h>
// #include <mocks/M_Reader.h>
// #include <mocks/M_TCP_Con.h>
// #include <mocks/M_TCP_Listener.h>
// #include <mocks/M_TCP.h>

#include <testlib/TestCoding.h>

namespace test
{
    TEST_INSTANCE_DEF(M_Com)
    TEST_INSTANCE_DEF(M_Ctrl)
    TEST_INSTANCE_DEF(M_Elems)
    TEST_INSTANCE_DEF(M_Mapper)
    TEST_INSTANCE_DEF(M_Provider)
    TEST_INSTANCE_DEF(M_Reader)
    TEST_INSTANCE_DEF(M_TCP_Con_Ctrl)
    TEST_INSTANCE_DEF(M_TCP_Con_Fld)
    TEST_INSTANCE_DEF(M_TCP_Con_Gui)
    TEST_INSTANCE_DEF(M_TCP_Listener_Ctrl)
    TEST_INSTANCE_DEF(M_TCP_Listener_Fld)
    TEST_INSTANCE_DEF(M_TCP_Listener_Gui)
    TEST_INSTANCE_DEF(M_TCP)

    std::ostringstream M_Base::mStream;
}
