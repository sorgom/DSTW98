//  ============================================================
//  test values
//  ============================================================
//  created by Manfred Sorgo

#ifndef TEST_VALUES_H
#define TEST_VALUES_H

#include <codebase/BaseTypes.h>
#include <ifs/values.h>

namespace test
{
    enum E_TcpVals: UINT16
    {
        tcpPortFld  = 8091,
        tcpPortGui  = 8092,
        tcpPortCtrl = 8093,
        tcpTimeout  = 20
    };

    enum E_TestVals: UINT8
    {
        NO_PARAM = PARAM_UNDEF - 1,
        PARAM_UNKNOWN = PARAM_UNDEF - 2,
    };

} // namespace
#endif // _H
