#include <TSW/TSW.h>
#include <SYS/IL.h>

void TSW::fromFld(const ComData& data)
{
    const UINT8 state = data.param1;
    switch(state)
    {
    case TSW_STATE_LEFT:
    case TSW_STATE_RIGHT:
    case TSW_STATE_UNDEF:
    case TSW_STATE_DEFECT:
        chgState(state);
        break;
    default:
        logMismatch();
        break;
    }
}

void TSW::fromGui(const ComData& data)
{
    const UINT8 state = data.param1;
    switch(state)
    {
    case TSW_CMD_WU:
        wu();
        break;
    case TSW_CMD_LEFT:
        swLeft();
        break;
    case TSW_CMD_RIGHT:
        swRight();
        break;
    default:
        logMismatch();
        break;
    };
}

void TSW::swLeft()
{
    switch (mState)
    {
    case TSW_STATE_LEFT:
    case TSW_STATE_WAIT_LEFT:
    case TSW_STATE_DEFECT:
        break;
    default:
        chgState(TSW_STATE_WAIT_LEFT);
        toFld(TSW_STATE_LEFT);
        break;
    }
}

void TSW::swRight()
{
    switch (mState)
    {
    case TSW_STATE_RIGHT:
    case TSW_STATE_WAIT_RIGHT:
    case TSW_STATE_DEFECT:
        break;
    default:
        chgState(TSW_STATE_WAIT_RIGHT);
        toFld(TSW_STATE_RIGHT);
        break;
    }
}

void TSW::wu()
{
    switch(mState)
    {
    case TSW_STATE_LEFT:
        chgState(TSW_STATE_WAIT_RIGHT);
        toFld(TSW_STATE_RIGHT);
        break;
    case TSW_STATE_RIGHT:
        chgState(TSW_STATE_WAIT_LEFT);
        toFld(TSW_STATE_LEFT);
        break;
    default:
        break;
    };
}

void TSW::chgState(const UINT8 state)
{
    if (state != mState)
    {
        mState = state;
        reGui();
    }
}
