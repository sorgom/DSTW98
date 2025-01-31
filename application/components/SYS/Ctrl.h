//  ============================================================
//  class Ctrl implements I_Ctrl
//  - currently without functionality
//  ============================================================
//  created by Manfred Sorgo

#ifndef CTRL_H
#define CTRL_H

#include <ifs/I_Ctrl.h>
#include <BAS/coding.h>

class Ctrl : public I_Ctrl
{
public:

    void log(E_Comp comp, E_Ret ret);

    inline E_Ret maxerr() const
    {
        return mErr;
    }

    INSTANCE_DEC(Ctrl)

    NOCOPY(Ctrl)
private:
    E_Ret mErr = RET_NO_ERR;
    inline Ctrl() = default;
};
#endif // _H
