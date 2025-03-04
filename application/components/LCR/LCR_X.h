//  ============================================================
//  classes LCR_(X) implement level crossing elements
//  ============================================================
//  created by Manfred Sorgo

#ifndef LCR_X_H
#define LCR_X_H

#include <BAS/BAS_Elem.h>

class LCR_X : public BAS_Elem<COMP_LCR>
{
public:

    void fromGui(const ComData& data);

    NOCOPY(LCR_X)
    NODEF(LCR_X)

protected:
    inline LCR_X(size_t id) :
        BAS_Elem<COMP_LCR>(id),
        mState(LCR_STATE_UNDEF)
    {}

    UINT8 mState;

    void open();
    void close();

    static bool validState(UINT8 state);
};

//  ============================================================
//  -   LCR without occupation control
//  ============================================================
class LCR : public LCR_X
{
public:
    inline LCR(size_t id): LCR_X(id) {}

    void fromFld(const ComData& data);
    inline void reGui() const
    {
        toGui(mState);
    }

    NOCOPY(LCR)
    NODEF(LCR)
};

//  ============================================================
//  -   LCR with occupation control
//  ============================================================
class LCR_UBK : public LCR_X
{
public:
    inline LCR_UBK(size_t id):
        LCR_X(id),
        mStateUbk(LCR_UBK_STATE_UNDEF)
    {}

    void fromFld(const ComData& data);
    inline void reGui() const
    {
        toGui(mState, mStateUbk);
    }

    NOCOPY(LCR_UBK)
    NODEF(LCR_UBK)

private:
    UINT8 mStateUbk;
    static bool validUbk(UINT8 ubk);
};
#endif // _H
