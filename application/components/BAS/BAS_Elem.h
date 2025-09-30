//  ============================================================
//  base implementation of I_Elem
//  ============================================================
//  created by Manfred Sorgo

#ifndef BAS_ELEM_H
#define BAS_ELEM_H

#include <ifs/I_Elem.h>
#include <ifs/values.h>
#include <BAS/coding.h>

class X_Elem : public I_Elem
{
protected:
    inline X_Elem(size_t id):
        mId(id)
    {}
    void sndFld(const ComData& data) const;
    void sndGui(const ComData& data) const;

    static void logMismatch(E_Comp comp);

    NODEF(X_Elem)
    NOCOPY(X_Elem)
private:
    const size_t mId;
};

template <E_Comp COMP>
class BAS_Elem : public X_Elem
{
protected:
    inline BAS_Elem(size_t id):
        X_Elem(id)
    {}
    inline static void logMismatch()
    {
        X_Elem::logMismatch(COMP);
    }
    NOCOPY(BAS_Elem)
    NODEF(BAS_Elem)
};


#endif // _H
