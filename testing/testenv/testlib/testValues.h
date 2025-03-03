//  ============================================================
//  test values
//  ============================================================
//  created by Manfred Sorgo

#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <codebase/BaseTypes.h>
#include <ifs/values.h>

namespace test
{
    //  was: enum enum E_TcpVals
    static const UINT16 tcpPortFld  = 8081;
    static const UINT16 tcpPortGui  = 8082;
    static const UINT16 tcpPortCtrl = 8083;
    static const UINT16 tcpTimeout = 20;

    //  was: enum enum E_TestVals
    static const UINT8 NO_PARAM = PARAM_UNDEF - 1;
    static const UINT8 PARAM_UNKNOWN = PARAM_UNDEF - 2;

} // namespace
#endif // _H
