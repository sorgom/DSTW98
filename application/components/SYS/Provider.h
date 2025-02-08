//  ============================================================
//  class Provider implements I_Provider
//  ============================================================
//  created by Manfred Sorgo

#ifndef PROVIDER_H
#define PROVIDER_H

#include <BAS/StackArray.h>
#include <ifs/I_Provider.h>
#include <SYS/Capacity.h>

#include <TSW/TSW.h>
#include <SIG/SIG_X.h>
#include <LCR/LCR_X.h>

class Provider : public I_Provider
{
public:
    inline Provider() {}

    inline size_t size() const
    {
        return mElems.size();
    }

    inline const I_Elem& at(size_t pos) const
    {
        return mElems.at(pos);
    }

    inline I_Elem& at(size_t pos)
    {
        return mElems.at(pos);
    }

    inline void clear()
    {
        mElems.clear();
    }

    void add(const ProjItem& data);

    INSTANCE_DEC(Provider)
    NOCOPY(Provider)
private:
    #define ADD_SIZE(CLASS) BYTE m ## CLASS[sizeof(CLASS)];
    union Sizes
    {
        ADD_SIZE(TSW)
        ADD_SIZE(SIG_H)
        ADD_SIZE(SIG_N)
        ADD_SIZE(SIG_H_N)
        ADD_SIZE(LCR)
        ADD_SIZE(LCR_UBK)
    };
    StackArray<I_Elem, CAPACITY, sizeof(Sizes)> mElems;

    template <class T>
    inline void add(size_t pos)
    {
        mElems.add(T(pos));
    }

};

#endif // _H
