//  ============================================================
//  number of elements in test data
//  - track switches
//  - signals
//  - level crossings
//  - segments
//
//  pre-defined here
//  definable at compile time
//  e.g.: -DTEST_NUM_SIG=500
//  ============================================================
//  created by Manfred Sorgo

#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <codebase/BaseTypes.h>
#include <ifs/values.h>

namespace test
{
    //  was: enum enum E_TcpVals
    static const UINT16 tcpPortFld = 8080;
    static const UINT16 tcpPortGui = 8081;
    static const UINT16 tcpPortCtrl = 8082;
    static const UINT16 tcpTimeout = 10;

    //  was: enum enum E_TestVals
    static const UINT8 NO_PARAM = PARAM_UNDEF - 1;
    static const UINT8 PARAM_UNKNOWN = PARAM_UNDEF - 2;

} // namespace
#endif // _H
