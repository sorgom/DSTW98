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

    void log(E_Comp comp, E_Err ret);

    inline void clear()
    {
        mErr = NO_ERR;
        mRunning = true;
    }

    inline void stop()
    {
        mRunning = false;
    }

    inline bool ok() const
    {
        return mRunning and mErr == NO_ERR;
    }

    inline E_Err maxerr() const
    {
        return mErr;
    }

    INSTANCE_DEC(Ctrl)

    NOCOPY(Ctrl)
private:
    E_Err mErr;
    bool mRunning;
    inline Ctrl() { clear(); }
};
#endif // _H
