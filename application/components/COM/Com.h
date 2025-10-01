//  ============================================================
//  class Com implements I_Com
//  ============================================================
//  created by Manfred Sorgo

#ifndef COM_H
#define COM_H

#include <ifs/I_Com.h>
#include <BAS/coding.h>

class Com : public I_Com
{
public:
    void start();
    void check();
    void stop();
    void toFld(const ComTele& tele) const;
    void toGui(const ComTele& tele) const;

    INSTANCE_DEC(Com)
    NOCOPY(Com)

private:
    inline Com() {}
};
#endif // _H
