//  ============================================================
//  interface Ctrl
//  - runtime error logging
//  ============================================================
//  created by Manfred Sorgo

#ifndef I_CTRL_H
#define I_CTRL_H

#include "values.h"

class I_Ctrl
{
public:
    virtual void clear() = 0;
    virtual void log(E_Comp comp, E_Ret ret) = 0;
    virtual E_Ret maxerr() const = 0;
    virtual void stop() = 0;
    virtual bool ok() const = 0;
};
#endif // _H
