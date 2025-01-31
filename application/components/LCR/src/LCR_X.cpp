#include <LCR/LCR_X.h>
#include <SYS/IL.h>

void LCR_X::open()
{
    switch (mStateToGui)
    {
        case LCR_STATE_UNDEF:
        case LCR_STATE_CLOSED:
        case LCR_STATE_WAIT_CLOSED:
            mStateToGui = LCR_STATE_WAIT_OPEN;
            toGui();
            toFld(LCR_STATE_OPEN);
            break;
        default:
            break;
    }
}

void LCR_X::close()
{
    switch (mStateToGui)
    {
        case LCR_STATE_UNDEF:
        case LCR_STATE_OPEN:
        case LCR_STATE_WAIT_OPEN:
            mStateToGui = LCR_STATE_WAIT_CLOSED;
            toGui();
            toFld(LCR_STATE_CLOSED);
            break;
        default:
            break;
    }
}

void LCR_X::toFld(const UINT8 state) const
{
    IL::getMapper().toFld(mId, ComData(state));
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
            IL::getCtrl().log(COMP_LCR, RET_ERR_MATCH);
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
        IL::getCtrl().log(COMP_LCR, RET_ERR_MATCH);
        break;
    };
    return ok;
}

void LCR::fromFld(const ComData& data)
{
    const UINT8 state = data.param1;
    if (validState(state) and state != mStateToGui)
    {
        mStateToGui = state;
        toGui();
    }
}

void LCR::toGui() const
{
    IL::getMapper().toGui(mId, ComData(mStateToGui));
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
        IL::getCtrl().log(COMP_LCR, RET_ERR_MATCH);
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
            (state != mStateToGui) or
            (ubk   != mUbkToGui)
        ) and
        validState(state) and
        validUbk(ubk)
    )
    {
        mStateToGui = state;
        mUbkToGui = ubk;
        toGui();
    }
}

void LCR_UBK::toGui() const
{
    IL::getMapper().toGui(mId, ComData(mStateToGui, mUbkToGui));
}
