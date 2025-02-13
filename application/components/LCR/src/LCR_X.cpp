#include <LCR/LCR_X.h>
#include <SYS/IL.h>

void LCR_X::open()
{
    switch (mState)
    {
        case LCR_STATE_UNDEF:
        case LCR_STATE_CLOSED:
        case LCR_STATE_WAIT_CLOSED:
            mState = LCR_STATE_WAIT_OPEN;
            reGui();
            toFld(LCR_STATE_OPEN);
            break;
        default:
            break;
    }
}

void LCR_X::close()
{
    switch (mState)
    {
        case LCR_STATE_UNDEF:
        case LCR_STATE_OPEN:
        case LCR_STATE_WAIT_OPEN:
            mState = LCR_STATE_WAIT_CLOSED;
            reGui();
            toFld(LCR_STATE_CLOSED);
            break;
        default:
            break;
    }
}

void LCR_X::fromGui(const ComData& data)
{
    switch (data.param1)
    {
        case LCR_STATE_CLOSED:
            close();
            break;
        case LCR_STATE_OPEN:
            open();
            break;
        default:
            logMismatch();
            break;
    }
}

bool LCR_X::validState(const UINT8 state)
{
    bool ok = false;
    switch (state)
    {
    case LCR_STATE_UNDEF:
    case LCR_STATE_DEFECT:
    case LCR_STATE_OPEN:
    case LCR_STATE_CLOSED:
        ok = true;
        break;
    default:
        logMismatch();
        break;
    };
    return ok;
}

void LCR::fromFld(const ComData& data)
{
    const UINT8 state = data.param1;
    if (validState(state) and state != mState)
    {
        mState = state;
        reGui();
    }
}

bool LCR_UBK::validUbk(const UINT8 state)
{
    bool ok = false;
    switch (state)
    {
    case LCR_UBK_STATE_UNDEF:
    case LCR_UBK_STATE_DEFECT:
    case LCR_UBK_STATE_OCCUPIED:
    case LCR_UBK_STATE_FREE:
        ok = true;
        break;
    default:
        logMismatch();
        break;
    };
    return ok;
}

void LCR_UBK::fromFld(const ComData& data)
{
    const UINT8 state = data.param1;
    const UINT8 ubk   = data.param2;
    if (
        (
            (state != mState) or
            (ubk   != mStateUbk)
        ) and
        validState(state) and
        validUbk(ubk)
    )
    {
        mState = state;
        mStateUbk = ubk;
        reGui();
    }
}
