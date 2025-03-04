//  ============================================================
//  class TSW implements a track switch element
//  state of implementation:
//  - WU command from GUI
//  - all states from field, forwarding to GUI
//  ============================================================
//  created by Manfred Sorgo

#ifndef TSW_H
#define TSW_H

#include <BAS/BAS_Elem.h>

class TSW : public BAS_Elem<COMP_TSW>
{
public:
    inline TSW(size_t id):
        BAS_Elem<COMP_TSW>(id),
        mState(TSW_STATE_UNDEF)
    {}

    inline void reGui() const
    {
        toGui(mState);
    }

    void fromFld(const ComData& data);
    void fromGui(const ComData& data);

    NOCOPY(TSW)
    NODEF(TSW)
private:
    UINT8 mState;

    void wu();
    void swLeft();
    void swRight();
    void chgState(UINT8 state);
};
#endif // _H
