//  ============================================================
//  system wide specified values
//  ============================================================
//  created by Manfred Sorgo

#ifndef VALUES_H
#define VALUES_H

#include <codebase/BaseTypes.h>

//  component identifiers (size does not matter)
enum E_Comp
{
    COMP_COM = 81,
    COMP_TSW,
    COMP_SIG,
    COMP_LCR,
    COMP_SEG,
    COMP_SYS
};

//  return types (size does not matter)
enum E_Ret
{
    // no error
    RET_NO_ERR,
    //  element name not found
    //  or received state not valid
    RET_ERR_MATCH,
    //  element position out of range
    RET_ERR_RANGE,
    //  startup error in component
    RET_ERR_STARTUP,
    //  communication error
    RET_ERR_COM,
    //  project data error
    RET_ERR_PROJ
};

//  reserved parameter values
//  was: enum enum E_Param
static const UINT8 PARAM_UNDEF = 255;

//  Element types 21 .. 40
//  was: enum enum E_ElemType
static const UINT8 TYPE_LCR = 21;
static const UINT8 TYPE_LCR_UBK = 22;
static const UINT8 TYPE_SEG = 23;
static const UINT8 TYPE_SIG_H = 24;
static const UINT8 TYPE_SIG_H_N = 25;
static const UINT8 TYPE_SIG_N = 26;
static const UINT8 TYPE_SIG_S = 27;
static const UINT8 TYPE_TSW = 28;

//  SIG states 41 .. 60
//  was: enum enum E_SigState
static const UINT8 SIG_STATE_H0 = 41;
static const UINT8 SIG_STATE_H1 = 42;
static const UINT8 SIG_STATE_N0 = 43;
static const UINT8 SIG_STATE_N1 = 44;
static const UINT8 SIG_STATE_H0_N0 = 45;
static const UINT8 SIG_STATE_H0_N1 = 46;
static const UINT8 SIG_STATE_H1_N0 = 47;
static const UINT8 SIG_STATE_H1_N1 = 48;
static const UINT8 SIG_STATE_WAIT_H0 = 49;
static const UINT8 SIG_STATE_WAIT_H1 = 50;
static const UINT8 SIG_STATE_WAIT_N0 = 51;
static const UINT8 SIG_STATE_WAIT_N1 = 52;
static const UINT8 SIG_STATE_WAIT_H0_N0 = 53;
static const UINT8 SIG_STATE_WAIT_H0_N1 = 54;
static const UINT8 SIG_STATE_WAIT_H1_N0 = 55;
static const UINT8 SIG_STATE_WAIT_H1_N1 = 56;
static const UINT8 SIG_STATE_DEFECT = 57;
static const UINT8 SIG_STATE_UNDEF = PARAM_UNDEF;

//  TSW states 61 .. 70
//  was: enum enum E_TswState
static const UINT8 TSW_STATE_LEFT = 61;
static const UINT8 TSW_STATE_RIGHT = 62;
static const UINT8 TSW_STATE_DEFECT = 63;
static const UINT8 TSW_STATE_WAIT_LEFT = 64;
static const UINT8 TSW_STATE_WAIT_RIGHT = 65;
static const UINT8 TSW_STATE_UNDEF = PARAM_UNDEF;

//  TSW commands 71 .. 80
//  was: enum enum E_TswCmd
static const UINT8 TSW_CMD_WU = 71;
static const UINT8 TSW_CMD_LEFT = 72;
static const UINT8 TSW_CMD_RIGHT = 73;

//  LCR states 81 .. 90
//  was: enum enum E_LcrState
static const UINT8 LCR_STATE_OPEN = 81;
static const UINT8 LCR_STATE_CLOSED = 82;
static const UINT8 LCR_STATE_WAIT_OPEN = 83;
static const UINT8 LCR_STATE_WAIT_CLOSED = 84;
static const UINT8 LCR_STATE_DEFECT = 85;
static const UINT8 LCR_STATE_UNDEF = PARAM_UNDEF;

//  LCR UBK states 90 .. 100
//  was: enum enum E_LcrUbkState
static const UINT8 LCR_UBK_STATE_OCCUPIED = 91;
static const UINT8 LCR_UBK_STATE_FREE = 92;
static const UINT8 LCR_UBK_STATE_DEFECT = 93;
static const UINT8 LCR_UBK_STATE_UNDEF = PARAM_UNDEF;

//  COM control 101 .. 110
//  was: enum enum E_ComCtrl
static const UINT8 COM_CTRL_STOP = 101;
static const UINT8 COM_CTRL_PING = 102;
static const UINT8 COM_CTRL_RE_GUI = 103;

#endif // _H
