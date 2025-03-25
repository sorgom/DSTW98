//  ============================================================
//  enumeration source for static constants
//  ============================================================
//  created by Manfred Sorgo

#ifndef ENUMS_H
#define ENUMS_H

#include <codebase/BaseTypes.h>

//  reserved parameter values
enum E_Param : UINT8
{
    PARAM_UNDEF = 255
};

//  Element types 21 .. 40
enum E_ElemType : UINT8
{
    TYPE_LCR = 21,
    TYPE_LCR_UBK,
    TYPE_SEG,
    TYPE_SIG_H,
    TYPE_SIG_H_N,
    TYPE_SIG_N,
    TYPE_SIG_S,
    TYPE_TSW
};

//  SIG states 41 .. 60
enum E_SigState : UINT8
{
    SIG_STATE_H0 = 41,
    SIG_STATE_H1,
    SIG_STATE_N0,
    SIG_STATE_N1,
    SIG_STATE_H0_N0,
    SIG_STATE_H0_N1,
    SIG_STATE_H1_N0,
    SIG_STATE_H1_N1,

    SIG_STATE_WAIT_H0,
    SIG_STATE_WAIT_H1,
    SIG_STATE_WAIT_N0,
    SIG_STATE_WAIT_N1,
    SIG_STATE_WAIT_H0_N0,
    SIG_STATE_WAIT_H0_N1,
    SIG_STATE_WAIT_H1_N0,
    SIG_STATE_WAIT_H1_N1,
    SIG_STATE_DEFECT,
    SIG_STATE_UNDEF = PARAM_UNDEF
};

//  TSW states 61 .. 70
enum E_TswState : UINT8
{
    TSW_STATE_LEFT = 61,
    TSW_STATE_RIGHT,
    TSW_STATE_WAIT_LEFT,
    TSW_STATE_WAIT_RIGHT,
    TSW_STATE_DEFECT,
    TSW_STATE_UNDEF = PARAM_UNDEF
};

//  TSW commands 71 .. 80
enum E_TswCmd : UINT8
{
    TSW_CMD_WU = 71,
    TSW_CMD_LEFT,
    TSW_CMD_RIGHT
};

//  LCR states 81 .. 90
enum E_LcrState : UINT8
{
    LCR_STATE_OPEN = 81,
    LCR_STATE_CLOSED,
    LCR_STATE_WAIT_OPEN,
    LCR_STATE_WAIT_CLOSED,
    LCR_STATE_DEFECT,
    LCR_STATE_UNDEF = PARAM_UNDEF
};

//  LCR UBK states 90 .. 100
enum E_LcrUbkState : UINT8
{
    LCR_UBK_STATE_OCCUPIED = 91,
    LCR_UBK_STATE_FREE,
    LCR_UBK_STATE_DEFECT,
    LCR_UBK_STATE_UNDEF = PARAM_UNDEF
};

//  COM control 101 .. 110
enum E_ComCtrl : UINT8
{
    COM_CTRL_STOP = 101,
    COM_CTRL_PING,
    COM_CTRL_RE_GUI
};

#endif // _H
