//  ============================================================
//  test of GenProjData
//  ============================================================
//  created by Manfred Sorgo

#include <comparators/ostreams.h>
#include <testlib/GenProjData.h>
#include <testlib/NetTest.h>
#include <testlib/TestGroupBase.h>

#include <sstream>

namespace test
{
    TEST_GROUP_BASE(DT_03, TestGroupBase) {};

    //  test type: equivalence class test
    TEST(DT_03, T01)
    {
        SETUP()
        GenProjData<10> data;

        STEP(1)
        const ComSetup& s = data.setup;
        L_CHECK_EQUAL(tcpPortFld,  NetTest::toH(s.portFld))
        L_CHECK_EQUAL(tcpPortGui,  NetTest::toH(s.portGui))
        L_CHECK_EQUAL(tcpPortCtrl, NetTest::toH(s.portCtrl))
        L_CHECK_EQUAL(tcpTimeout,  NetTest::toH(s.timeout))

        STEP(2)
        std::ostringstream os;
        os << fixT(data.at(9).addr.chars);
        STRCMP_EQUAL("ELEM 0001   ", os.str().c_str());

        os.str("");
        os << fixT(data.at(0).addr.chars);
        STRCMP_EQUAL("ELEM 0010   ", os.str().c_str());

        STEP(3)
        L_CHECK_EQUAL(TYPE_LCR,     data.type(0))
        L_CHECK_EQUAL(TYPE_LCR_UBK, data.type(1))
        L_CHECK_EQUAL(TYPE_SIG_H,   data.type(2))
        L_CHECK_EQUAL(TYPE_SIG_H_N, data.type(3))
        L_CHECK_EQUAL(TYPE_SIG_N,   data.type(4))
        L_CHECK_EQUAL(TYPE_TSW,     data.type(5))
        L_CHECK_EQUAL(TYPE_LCR,     data.type(6))
        L_CHECK_EQUAL(TYPE_LCR_UBK, data.type(7))
        L_CHECK_EQUAL(TYPE_SIG_H,   data.type(8))
        L_CHECK_EQUAL(TYPE_SIG_H_N, data.type(9))
    }

} // namespace
