//  ============================================================
//  system wide specified values
//  ============================================================
//  created by Manfred Sorgo

#ifndef VALUES_H
#define VALUES_H

#include <codebase/checks.h>

//  component identifiers
enum E_Comp
{
    COMP_COM = 81,
    COMP_TSW,
    COMP_SIG,
    COMP_LCR,
    COMP_SEG,
    COMP_SYS
};

//  return types
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
    RET_ERR_PROJ,
};

//  reserved parameter values
enum E_Param
{
    //  value not defined
    PARAM_UNDEF = 255
};

//  Element types
enum E_ElemType
{
    TYPE_LCR = 101,
    TYPE_LCR_UBK,
    TYPE_SEG,
    TYPE_SIG_H,
    TYPE_SIG_H_N,
    TYPE_SIG_N,
    TYPE_SIG_S,
    TYPE_TSW
};

//  SIG states
enum E_SigState
{
    SIG_STATE_H0,
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

//  TSW commands and states
enum E_TswState
{
    TSW_STATE_LEFT,
    TSW_STATE_RIGHT,
    TSW_STATE_DEFECT,
    TSW_STATE_WAIT_LEFT,
    TSW_STATE_WAIT_RIGHT,
    TSW_STATE_UNDEF = PARAM_UNDEF
};

enum E_TswCmd
{
    TSW_CMD_WU = 21,
    TSW_CMD_LEFT,
    TSW_CMD_RIGHT
};

//  LCR states
enum E_LcrState
{
    LCR_STATE_OPEN,
    LCR_STATE_CLOSED,
    LCR_STATE_WAIT_OPEN,
    LCR_STATE_WAIT_CLOSED,
    LCR_STATE_DEFECT,
    LCR_STATE_UNDEF = PARAM_UNDEF
};

enum E_LcrUbkState
{
    LCR_UBK_STATE_OCCUPIED,
    LCR_UBK_STATE_FREE,
    LCR_UBK_STATE_DEFECT,
    LCR_UBK_STATE_UNDEF = PARAM_UNDEF
};

//  COM control
enum E_ComCtrl
{
    COM_CTRL_STOP = 131,
    COM_CTRL_PING,
    COM_CTRL_RE_GUI
};
#endif // _H
